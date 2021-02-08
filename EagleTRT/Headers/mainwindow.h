#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tabViewer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void tabChanged(int index);

private:
    Ui::MainWindow *ui;

    TabViewer* mTabViewer;

    int previousTab;
    QWidget* currentTab;
    QList<QMetaObject::Connection> connections;


};
#endif // MAINWINDOW_H
