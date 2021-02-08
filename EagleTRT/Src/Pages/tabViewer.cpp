#include "tabViewer.h"

#include <QtConcurrent/QtConcurrent>
#include <QApplication>
#include <QDateTime>
#include <QFuture>
#include <QMessageBox>
#include <QTimer>
#include <random>
#include <thread>

TabViewer::TabViewer(QWidget* tab)
{
    this->mTab = tab;
    mParser = new Parser();

    mWorker = new Worker(mParser, &mChimera);
    th1 = new QThread;
}

TabViewer::~TabViewer(){
    delete mTab;
    delete mParser;
}

void TabViewer::init(){
    print("Initialiing...");

    actions = new QStringList{
        "Read Log",
        "Real Time"
    };

    // accessing to the current widget (tab)
    QComboBox* actionCombo = mTab->findChild<QComboBox*>("actionType");
    actionCombo->addItems(*actions);

    auto pBar = mTab->findChild<QProgressBar *>("progressBar");
    auto dataText = mTab->findChild<QTextEdit *>("Data");
    if(pBar != 0 && dataText != 0){
        pBar->setVisible(false);
        dataText->setVisible(false);
    }

    print("Done");
}

void TabViewer::makeConnections(){
    print("Making connections");
    int failValue = -1;

    // accessing to the push buttons inside the tabwidget
    auto button = mTab->findChild<QPushButton *>("submitAction");
    if(button == 0)
        failValue = 0;
    auto tree = mTab->findChild<QTreeView *>("treeView");
    if(tree == 0)
        failValue = 1;
    auto slider = mTab->findChild<QSlider*>("logSlider");
    if(slider == 0)
        failValue = 2;
    auto pauseButton = mTab->findChild<QPushButton*>("pauseButton");
    if(pauseButton == 0)
        failValue = 3;
    auto rawDataList = mTab->findChild<QListWidget*>("rawData");
    if(rawDataList == 0)
        failValue = 4;

    if(failValue != -1){
        print("failed on making connection of " + QString(failValue));
    }

    // push button to select action
    connections << connect(button, &QPushButton::pressed, this, &TabViewer::submitAction);

    // treeView to select log file
    connections << connect(tree, &QTreeView::clicked, this, &TabViewer::treeClicked);

    // Pause Button clocked
    connections << connect(pauseButton, &QPushButton::pressed, this, &TabViewer::pauseBtnClicked);

    connections << connect(rawDataList, &QListWidget::itemClicked, this, &TabViewer::rawItemClicked);

    // Slider to show/set the log percentage
    connections << connect(mWorker, &Worker::percentageUpdated, this, &TabViewer::percentageUpdated);
    connections << connect(slider, &QSlider::sliderMoved, this, &TabViewer::userChangedSlider);
    connections << connect(slider, &QSlider::sliderPressed, mWorker, &Worker::pause);
    connections << connect(slider, &QSlider::sliderReleased, mWorker, &Worker::resume);
    connections << connect(slider, &QSlider::sliderMoved, this, &TabViewer::userChangedSlider);
    connections << connect(this, &TabViewer::setPercentage, mWorker, &Worker::changePercentage);

    connections << connect(mWorker, &Worker::rawDataUpdated, this, &TabViewer::rawDataUpdated);

    // Worker, used to parse the selected log file
    connections << connect(mWorker, &Worker::updated, this, &TabViewer::chimeraUpdated);
    connections << connect(this, &TabViewer::kill, mWorker, &Worker::stop);
    connections << connect(this, &TabViewer::pause, mWorker, &Worker::pause);
    connections << connect(this, &TabViewer::togglePause, mWorker, &Worker::togglePause);

    print("Done");
}

void TabViewer::freeConnections(){
    print("Clean Connection");

    emit pause();

    foreach (QMetaObject::Connection connection, connections)
        disconnect(connection);
    print("Done");
}

void TabViewer::submitAction(){
    QComboBox* actionCombo = mTab->findChild<QComboBox*>("actionType");
    if(actionCombo == 0)
        return;

    // Execute the action chosen from comboBox
    if(actionCombo->currentIndex() == 0){
        QFileDialog* dial = new QFileDialog(mTab);

        QString folder = dial->getExistingDirectory(mTab, "Select a folder containing log files");

        if(folder != ""){
            print(folder);
            pathSelected(folder);
        }
    }
}

void TabViewer::pauseBtnClicked(){
    print("Toggling pause");
    emit togglePause();
}


void TabViewer::pathSelected(QString folder){
    print("Creating file tree");

    auto tree = mTab->findChild<QTreeView *>("treeView");
    if(tree == 0)
        return;

    // Create a dir model to set data to treeView
    mModel = new QFileSystemModel();
    mModel->setRootPath(folder);

    tree->setModel(mModel);
    tree->setRootIndex(mModel->index(folder));
    tree->hideColumn(2);

    print("Done");
}

void TabViewer::treeClicked(const QModelIndex& idx){
    print("Tree Clicked");
    QString path = mModel->filePath(idx);
    QFileInfo info(path);

    auto pBar = mTab->findChild<QSlider *>("logSlider");
    auto dataText = mTab->findChild<QTextEdit *>("Data");
    if(pBar == 0 || dataText == 0){
        print("pBar & textEdit not found in treeClicked");
        return;
    }

    if(info.isFile()){
        pBar->setVisible(true);
        dataText->setVisible(true);
    }
    else{
        pBar->setVisible(false);
        dataText->setVisible(false);
        return;
    }

    mFileName = path;

    QStringList lines = getFileLines(mFileName);

    // check if the current selected file is a valid log
    // pick 10 random lines and parse them, if succes for all, the log is valid
    bool validLog = true;
    for(int i = 0; i < 10; i++){
        int index = rand() % (lines.count());
        double timestamp;
        int id;
        vector<int> payload = mParser->splitMessage(&timestamp, &id, lines[index].toStdString());
        if(timestamp == 0 || id == 0 || payload.size() <= 0)
            validLog = false;
    }

    if(!validLog)
    {
        print("Log file not valid");
        return;
    }

    // Killing previous threads
    emit kill();
    usleep(1000);

    // starting new Thread
    mWorker->setFileName(path);
    mWorker->start();

    print("Started");
}

void TabViewer::chimeraUpdated(){

    string separator = "\t";
    vector<string> sensorLines;
    vector<int> sensorLinesColors;

    auto textField = mTab->findChild<QTextEdit *>("Data");
    if(textField == 0)
        return;

    sensorLines.push_back(mChimera.accel->getString(separator));
    sensorLines.push_back(mChimera.gyro->getString(separator));
    sensorLines.push_back(mChimera.invl->getString(separator));
    sensorLines.push_back(mChimera.invr->getString(separator));
    sensorLines.push_back(mChimera.BMSHV->getString(separator));
    sensorLines.push_back(mChimera.BMSLV->getString(separator));
    sensorLines.push_back(mChimera.pedals->getString(separator));
    sensorLines.push_back(mChimera.steer->getString(separator));
    sensorLines.push_back(mChimera.encl->getString(separator));
    sensorLines.push_back(mChimera.encr->getString(separator));
    sensorLines.push_back(mChimera.ecu->getString(separator));

    string joined = boost::algorithm::join(sensorLines, "\n");
    textField->setText(QString(joined.c_str()));
}

void TabViewer::rawDataUpdated(QStringList data){
    auto listView = mTab->findChild<QListWidget *>("rawData");
    if(listView == 0)
        return;

    listView->clear();
    listView->addItems(data);
}

void TabViewer::rawItemClicked(QListWidgetItem* item){
    qDebug() << item->text();
    double timestamp;
    int id;
    vector<int> payload;
    payload = mParser->splitMessage(&timestamp, &id, item->text().toStdString().c_str());

    Chimera tempChimera;
    int modified = mParser->parseChimeraMessage(timestamp, id, payload, &tempChimera);
    QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("Message Detail");
    if(modified == -1){
        msg->setText("ID unknown");
        msg->open();
    }else{

    }

}
void TabViewer::percentageUpdated(float value){
    QSlider* slider = mTab->findChild<QSlider*>("logSlider");
    if(slider == 0)
        return;
    slider->setValue(value*1000);
}

void TabViewer::userChangedSlider(){
    auto slider = mTab->findChild<QSlider*>("logSlider");
    if(slider == 0)
        return;
    emit setPercentage(slider->value()/1000);
}


void TabViewer::print(QString message){
    auto textField = mTab->findChild<QTextEdit *>("logOutput");
    if(textField == 0)
        return;
    textField->append(message);

    QScrollBar* scrollBar = textField->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
}

void TabViewer::clearDebug(){
    auto textField = mTab->findChild<QTextEdit *>("logOutput");
    if(textField == 0)
        return;
    textField->clear();
}

//////////////////////
void startT(chrono::_V2::steady_clock::time_point * t){
  *t = std::chrono::steady_clock::now();
}
double endT(chrono::_V2::steady_clock::time_point * t){
  std::chrono::duration<double> diff = std::chrono::steady_clock::now() - *t;
  return diff.count();
}
double getNowSec(){
  auto current_time = chrono::system_clock::now();
  auto duration_in_seconds = chrono::duration<double>(current_time.time_since_epoch());
  return duration_in_seconds.count();
}
QStringList getFileLines(QString fName){
  QStringList lines;

  FILE* fp = fopen(fName.toStdString().c_str(), "r");
  if (fp == NULL)
    return lines;

  char* line = NULL;
  size_t len = 0;
  while ((getline(&line, &len, fp)) != -1) {
    lines.push_back(line);
  }

  fclose(fp);
  if (line)
    free(line);

  return lines;
}

//////////////////////



Worker::Worker(Parser* parser, Chimera* chimera){
    mParser = parser;
    mChimera = chimera;
}

void Worker::setFileName(QString fileName){
    mFileName = fileName;
}

void Worker::stop(){
    runState = -1;
}

void Worker::pause(){
    runState = 0;
}

void Worker::resume(){
    runState = 1;
}

void Worker::togglePause(){
    if(runState == 0)
        runState = 1;
    else if (runState == 1)
        runState = 0;
}

void Worker::changePercentage(float value){
    currentLine = (int)((value/100)*(lineCount-1));
}

void Worker::run(){

    runState = 1;

    auto lines = getFileLines(mFileName);

    chrono::_V2::steady_clock::time_point sTime;

    // times to playback the log with right speed
    double currentTime = getNowSec();
    double logTime = -1;

    int startLine = 20;

    // to show percentage
    lineCount = lines.count();
    // to send line parsed from the prevuois update
    QStringList rawData;
    double prevLogTimestamp = -1;
    startT(&sTime);
    for(currentLine = startLine; currentLine < lineCount && runState != -1; currentLine++){
        while(runState == 0){
            // Wait for 10ms, increment the current time
            usleep(10000);
            currentTime += 0.01;
        }

        QString line = lines[currentLine];

        double timestamp;
        int id;
        vector<int> payload;

        line = line.remove('\n');
        string message = line.toStdString();

        payload = mParser->splitMessage(&timestamp, &id, message);
        int modified = mParser->parseChimeraMessage(timestamp, id, payload, mChimera);

        rawData.push_back(line);

        if(currentLine > startLine){
            mParser->getTimestamp(&prevLogTimestamp, lines[currentLine-1].toStdString());
        }
        else{
            prevLogTimestamp = timestamp;
        }
        qDebug() << prevLogTimestamp << timestamp;
        double DT = timestamp - prevLogTimestamp;
        qDebug() << DT;

        usleep(DT*10e5);

        // setting the initial time
        if(logTime == -1)
          logTime = timestamp;

//        // check the current time with te log time
//        // wait if faster
//        // jump lines if slower
//        double currentDT = getNowSec() - currentTime;
//        double logDT = (double)timestamp - (double)logTime;
//        if(currentDT > logDT)
//          usleep(0);    // should jump some lines because of slow cycles
//        else
//          usleep((logDT - currentDT )*1000000);

        if(modified == -1)
            continue;

        if(endT(&sTime) > 0.02){

            emit updated();
            emit rawDataUpdated(rawData);
            emit percentageUpdated(((float)currentLine/lineCount)*100);

            rawData.clear();
            startT(&sTime);
        }
    }
    runState = -1;
    emit finished();
}

