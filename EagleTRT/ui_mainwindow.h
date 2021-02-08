/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *viewer;
    QGridLayout *gridLayout_2;
    QTextEdit *logOutput;
    QTreeView *treeView;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *actionType;
    QPushButton *submitAction;
    QTextEdit *Data;
    QHBoxLayout *horizontalLayout;
    QPushButton *pauseButton;
    QSlider *logSlider;
    QListWidget *rawData;
    QWidget *parser;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(944, 602);
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu"));
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        viewer = new QWidget();
        viewer->setObjectName(QString::fromUtf8("viewer"));
        gridLayout_2 = new QGridLayout(viewer);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        logOutput = new QTextEdit(viewer);
        logOutput->setObjectName(QString::fromUtf8("logOutput"));
        logOutput->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(logOutput->sizePolicy().hasHeightForWidth());
        logOutput->setSizePolicy(sizePolicy);
        logOutput->setReadOnly(true);

        gridLayout_2->addWidget(logOutput, 11, 0, 1, 4);

        treeView = new QTreeView(viewer);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(treeView, 3, 0, 6, 3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        actionType = new QComboBox(viewer);
        actionType->setObjectName(QString::fromUtf8("actionType"));
        actionType->setMaximumSize(QSize(400, 16777215));

        horizontalLayout_2->addWidget(actionType);

        submitAction = new QPushButton(viewer);
        submitAction->setObjectName(QString::fromUtf8("submitAction"));
        submitAction->setMaximumSize(QSize(400, 16777215));

        horizontalLayout_2->addWidget(submitAction);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 3);

        Data = new QTextEdit(viewer);
        Data->setObjectName(QString::fromUtf8("Data"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(13);
        sizePolicy2.setHeightForWidth(Data->sizePolicy().hasHeightForWidth());
        Data->setSizePolicy(sizePolicy2);
        Data->setReadOnly(true);

        gridLayout_2->addWidget(Data, 3, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pauseButton = new QPushButton(viewer);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        pauseButton->setMaximumSize(QSize(32, 32));

        horizontalLayout->addWidget(pauseButton);

        logSlider = new QSlider(viewer);
        logSlider->setObjectName(QString::fromUtf8("logSlider"));
        logSlider->setMaximum(100000);
        logSlider->setSingleStep(1);
        logSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(logSlider);


        gridLayout_2->addLayout(horizontalLayout, 8, 3, 1, 1);

        rawData = new QListWidget(viewer);
        rawData->setObjectName(QString::fromUtf8("rawData"));
        sizePolicy.setHeightForWidth(rawData->sizePolicy().hasHeightForWidth());
        rawData->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(rawData, 7, 3, 1, 1);

        gridLayout_2->setColumnStretch(3, 9);
        tabWidget->addTab(viewer, QString());
        parser = new QWidget();
        parser->setObjectName(QString::fromUtf8("parser"));
        tabWidget->addTab(parser, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        submitAction->setText(QApplication::translate("MainWindow", "OK", nullptr));
        pauseButton->setText(QApplication::translate("MainWindow", "||", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(viewer), QApplication::translate("MainWindow", "Viewer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(parser), QApplication::translate("MainWindow", "Parser", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
