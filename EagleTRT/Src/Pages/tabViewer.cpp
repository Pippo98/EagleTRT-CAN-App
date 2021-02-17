#include "tabViewer.h"

#include <QtConcurrent/QtConcurrent>
#include <QApplication>
#include <QColumnView>
#include <QDateTime>
#include <QFuture>
#include <QMessageBox>
#include <QTableWidget>
#include <QTimer>
#include <random>
#include <thread>

TabViewer::TabViewer(QWidget* tab)
{
    this->mTab = tab;
    mParser = new Parser();

    mChimera = new Chimera();

    mWorker = new Worker(mParser, mChimera);
    th1 = new QThread;

    colors = QVector<QString>{
        "rgb(49, 201, 113)",
        "rgb(208, 9, 95)",
        "rgb(187, 79, 130)",
        "rgb(136, 172, 226)",
        "rgb(189, 235, 49)",
        "rgb(222, 113, 23)",
        "rgb(170, 124, 180)",
        "rgb(247, 176, 45)",
        "rgb(33, 48, 194)",
        "rgb(25, 190, 117)",
        "rgb(56, 127, 194)",
    };
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
//    auto dataText = mTab->findChild<QTextEdit*>("Data");
//    if(rawDataList == 0)
//        failValue = 5;
    auto table = mTab->findChild<QTableWidget*>("tableWidget");
    if(table == 0)
        failValue = 5;

    if(failValue != -1){
        print("failed on making connection of " + QString(failValue));
        qDebug() << ("failed on making connection of " + QString(failValue));
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


    // Worker, used to parse the selected log file
    connections << connect(mWorker, &Worker::updated, this, &TabViewer::chimeraUpdated);
    connections << connect(this, &TabViewer::kill, mWorker, &Worker::stop);
    connections << connect(this, &TabViewer::pause, mWorker, &Worker::pause);
    connections << connect(this, &TabViewer::togglePause, mWorker, &Worker::togglePause);

    connections << connect(mWorker, &Worker::rawDataUpdated, this, &TabViewer::rawDataUpdated);

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

    int colored = 1;

    string separator = "\t";
    vector<string> sensorLines;
    vector<int> sensorLinesColors;

    auto textField = mTab->findChild<QTextEdit *>("Data");
    if(textField == 0)
        return;

    auto table = mTab->findChild<QTableWidget*>("tableWidget");
    if(table == 0)
        return;

    sensorLines.push_back(mChimera->accel->getString(separator));
    sensorLines.push_back(mChimera->gyro->getString(separator));
    sensorLines.push_back(mChimera->invl->getString(separator));
    sensorLines.push_back(mChimera->invr->getString(separator));
    sensorLines.push_back(mChimera->BMSHV->getString(separator));
    sensorLines.push_back(mChimera->BMSLV->getString(separator));
    sensorLines.push_back(mChimera->pedals->getString(separator));
    sensorLines.push_back(mChimera->steer->getString(separator));
    sensorLines.push_back(mChimera->encl->getString(separator));
    sensorLines.push_back(mChimera->encr->getString(separator));
    sensorLines.push_back(mChimera->ecu->getString(separator));

    separator = "\n";

    table->setColumnCount(11);
    table->setRowCount(1);
    table->setItem(0, 0, new QTableWidgetItem(mChimera->accel->getString(separator).c_str()));
    table->setItem(0, 1, new QTableWidgetItem(mChimera->gyro->getString(separator).c_str()));
    table->setItem(0, 2, new QTableWidgetItem(mChimera->invl->getString(separator).c_str()));
    table->setItem(0, 3, new QTableWidgetItem(mChimera->invr->getString(separator).c_str()));
    table->setItem(0, 4, new QTableWidgetItem(mChimera->BMSHV->getString(separator).c_str()));
    table->setItem(0, 5, new QTableWidgetItem(mChimera->BMSLV->getString(separator).c_str()));
    table->setItem(0, 6, new QTableWidgetItem(mChimera->pedals->getString(separator).c_str()));
    table->setItem(0, 7, new QTableWidgetItem(mChimera->steer->getString(separator).c_str()));
    table->setItem(0, 8, new QTableWidgetItem(mChimera->encl->getString(separator).c_str()));
    table->setItem(0, 9, new QTableWidgetItem(mChimera->encr->getString(separator).c_str()));
    table->setItem(0, 10, new QTableWidgetItem(mChimera->ecu->getString(separator).c_str()));

    table->resizeRowsToContents();


    if(colored == 1){

        sensorLinesColors.push_back(mChimera->accel->id);
        sensorLinesColors.push_back(mChimera->gyro->id);
        sensorLinesColors.push_back(mChimera->invl->id);
        sensorLinesColors.push_back(mChimera->invr->id);
        sensorLinesColors.push_back(mChimera->BMSHV->id);
        sensorLinesColors.push_back(mChimera->BMSLV->id);
        sensorLinesColors.push_back(mChimera->pedals->id);
        sensorLinesColors.push_back(mChimera->steer->id);
        sensorLinesColors.push_back(mChimera->encl->id);
        sensorLinesColors.push_back(mChimera->encr->id);
        sensorLinesColors.push_back(mChimera->ecu->id);

        QString fontTagStart = "<font style=\"color:";
        QString fontTagEnd = ";\">";
        QString fontClose = "</font>";
        for(uint8_t i(0); i < sensorLines.size();i++){
            QString s(sensorLines[i].c_str());
            QString color = colors.at(sensorLinesColors[i]%colors.size());
            s = fontTagStart + color + fontTagEnd + s + fontClose + "<br>";
            sensorLines[i] = s.toStdString();
        }
    }


    string joined = boost::algorithm::join(sensorLines, "\n");
    joined = "<p style=\"font-size:17px\">" + joined + "</p>";
    textField->setHtml(QString(joined.c_str()));
}

void TabViewer::rawDataUpdated(QStringList data){
    auto listView = mTab->findChild<QListWidget *>("rawData");
    if(listView == 0)
        return;

    listView->clear();
    listView->addItems(data);
}
/*
 * get the detail of the message from the list of raw messages
 * display the full message descriprion in case the message is known
*/
void TabViewer::rawItemClicked(QListWidgetItem* item){
    qDebug() << item->text();
    double timestamp;
    int id;
    vector<int> payload;
    payload = mParser->splitMessage(&timestamp, &id, item->text().toStdString().c_str());

    Chimera* tempChimera = new Chimera();
    int modified = mParser->parseChimeraMessage(timestamp, id, payload, tempChimera);
    QMessageBox* msg = new QMessageBox();
    msg->setWindowTitle("Message Detail");
    if(modified == -1){
        msg->setText("Message Unknown");
        msg->open();
    }else{
        string separator = "\n";
        string ret = tempChimera->getFullStringOfID(modified, separator);
        ret = "Shown the whole structure, is possible that some fields are shown but are not contained in the message\n\n" + ret;
        msg->setText(QString(ret.c_str()));
        msg->setStyleSheet("background-color: " + colors[modified] + ";");
        msg->open();
    }

    stringstream s = mChimera->serialize(Text);
    cout << s.str() << endl;

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
    if(currentLine < 0)
        currentLine = 0;
    if(currentLine > lineCount-1)
        currentLine = lineCount -1;
}

void Worker::run(){

    runState = 1;

    auto lines = getFileLines(mFileName);

    // used to check if emitting an update is neccessary
    chrono::_V2::steady_clock::time_point timer1;   // updated()
    chrono::_V2::steady_clock::time_point timer2;   // rawDataUpdated()
    chrono::_V2::steady_clock::time_point cycleTimer;

    int HEADER_LINES = 20;
    for (int i = 0; i < HEADER_LINES; i++)
        lines.removeFirst();

    // to show percentage
    lineCount = lines.count();
    // to send line parsed from the prevuois update
    QStringList rawData;
    double prevLogTimestamp = -1;
    startT(&timer1);
    startT(&timer2);
    startT(&cycleTimer);
    for(currentLine = 0; currentLine < lineCount && runState != -1; currentLine++){
        while(runState == 0){
            // Wait for 10ms, increment the current time
            usleep(10000);
            startT(&cycleTimer);
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

        if(currentLine == 0){
            prevLogTimestamp = timestamp;
        }
        else{
            mParser->getTimestamp(&prevLogTimestamp, lines[currentLine-1].toStdString());
        }
        double DT = timestamp - prevLogTimestamp;
        DT = DT - endT(&cycleTimer);

        if(DT < 0){
            // fuck
        }
        else {
            usleep(DT*10e5);
        }
        startT(&cycleTimer);

        if(modified == -1)
            continue;

        if(endT(&timer1) > 0.02){
            emit updated();
            emit percentageUpdated(((float)currentLine/lineCount)*100);
        }
        if(endT(&timer2) > 0.5){
            emit rawDataUpdated(rawData);
            rawData.clear();
            startT(&timer2);
        }
    }
    runState = -1;
    emit finished();
}

