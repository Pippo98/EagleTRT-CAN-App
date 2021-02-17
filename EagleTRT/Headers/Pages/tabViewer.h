#ifndef TABVIEWER_H
#define TABVIEWER_H

#include <QObject>
#include <QWidget>
#include <QTabWidget>
#include <QDebug>

#include <QSlider>
#include <QComboBox>
#include <QTextEdit>
#include <QTreeView>
#include <QListView>
#include <QScrollBar>
#include <QPushButton>
#include <QFileDialog>
#include <QProgressBar>
#include <QFileSystemModel>
#include <QRunnable>
#include <QThread>
#include <QListWidget>

#include "thread"

#include <time.h>
#include <string>
#include <vector>

#include <boost/algorithm/string/join.hpp>

#include "Devices.h"
#include "Parser.h"

using namespace std;

class Worker : public QThread{
    Q_OBJECT
public:
    Worker(Parser* parser, Chimera* chimera);
    void setFileName(QString fileName);

    void run() override;

public slots:
    void stop();
    void pause();
    void togglePause();
    void resume();

    void changePercentage(float value);
    //void start();

signals:
    void updated();
    void finished();
    void rawDataUpdated(QStringList data);
    void percentageUpdated(float value);

private:
    // -1 to kill, 0 to pause, 1 to run
    int runState;
    int lineCount;
    int currentLine;

    QString mFileName;

    Parser* mParser;
    Chimera* mChimera;
};

class TabViewer : public QObject
{
    Q_OBJECT
public:
    TabViewer(QWidget*);
    ~TabViewer();

    // Initalize values of ui elements
    void init();
    // Make connections beween ui and backend
    void makeConnections();
    // Free all ui connections
    void freeConnections();

public slots:
    void submitAction();

    void pathSelected(QString folder);
    void treeClicked(const QModelIndex& index);

    void pauseBtnClicked();

    void percentageUpdated(float value);
    void userChangedSlider();

    void chimeraUpdated();
    void rawDataUpdated(QStringList data);

    void rawItemClicked(QListWidgetItem* index);

signals:
    void kill();
    void start();
    void pause();
    void togglePause();

    void setPercentage(float value);

private:

    QVector<QString> colors;

    void print(QString message);
    void clearDebug();

    // My veichle datastruct
    Fenice mFenice;
    Chimera* mChimera;

    Parser* mParser;
    Worker* mWorker;

    QThread* th1;
    std::thread* mThread;

    // Current Log file
    FILE* mFile;
    QString mFileName;

    // My Tab and My TreeView Model
    QWidget* mTab;
    QFileSystemModel* mModel;

    // List of all current connections
    QList<QMetaObject::Connection> connections;

    // Actions displayed in ComboBox
    QStringList* actions;
};

double getNowSec();
double endT(chrono::_V2::steady_clock::time_point *);
void startT(chrono::_V2::steady_clock::time_point *);

QStringList getFileLines(QString fName);

#endif // TABVIEWER_H
