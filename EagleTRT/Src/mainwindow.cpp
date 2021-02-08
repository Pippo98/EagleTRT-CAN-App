#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::tabChanged);

    QWidget* tab = this->ui->tabWidget->widget(0);
    if(tab != 0){
        this->mTabViewer = new TabViewer(tab);
        this->mTabViewer->init();
    }

    previousTab = -1;
    tabChanged(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// handles the tabs changes, connects disconnnects suff
void MainWindow::tabChanged(int index){
    if(index == -1)
        return;

    currentTab = this->ui->tabWidget->widget(index);

    if(previousTab != -1)
    {
        mTabViewer->freeConnections();
    }

    previousTab = index;

    // switch between tabs containing widgets
    if(index == 0){
        mTabViewer->makeConnections();
    }
}
