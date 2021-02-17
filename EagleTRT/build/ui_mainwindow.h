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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *viewer;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *actionType;
    QPushButton *submitAction;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *Data;
    QListWidget *rawData;
    QHBoxLayout *horizontalLayout;
    QPushButton *pauseButton;
    QSlider *logSlider;
    QTreeView *treeView;
    QTextEdit *logOutput;
    QWidget *parser;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(944, 602);
        QFont font;
        font.setFamily(QString::fromUtf8("Waree"));
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8("font: 11pt \"Waree\";"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        viewer = new QWidget();
        viewer->setObjectName(QString::fromUtf8("viewer"));
        layoutWidget = new QWidget(viewer);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 901, 531));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        actionType = new QComboBox(layoutWidget);
        actionType->setObjectName(QString::fromUtf8("actionType"));
        actionType->setMaximumSize(QSize(400, 16777215));

        horizontalLayout_2->addWidget(actionType);

        submitAction = new QPushButton(layoutWidget);
        submitAction->setObjectName(QString::fromUtf8("submitAction"));
        submitAction->setMaximumSize(QSize(400, 16777215));

        horizontalLayout_2->addWidget(submitAction);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableWidget = new QTableWidget(layoutWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout_2->addWidget(tableWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        Data = new QTextEdit(layoutWidget);
        Data->setObjectName(QString::fromUtf8("Data"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Data->sizePolicy().hasHeightForWidth());
        Data->setSizePolicy(sizePolicy);
        Data->setMouseTracking(false);
        Data->setReadOnly(true);

        verticalLayout->addWidget(Data);

        rawData = new QListWidget(layoutWidget);
        rawData->setObjectName(QString::fromUtf8("rawData"));
        sizePolicy.setHeightForWidth(rawData->sizePolicy().hasHeightForWidth());
        rawData->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(rawData);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pauseButton = new QPushButton(layoutWidget);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        pauseButton->setMaximumSize(QSize(32, 32));

        horizontalLayout->addWidget(pauseButton);

        logSlider = new QSlider(layoutWidget);
        logSlider->setObjectName(QString::fromUtf8("logSlider"));
        logSlider->setMaximum(100000);
        logSlider->setSingleStep(1);
        logSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(logSlider);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout_2, 0, 1, 2, 1);

        treeView = new QTreeView(layoutWidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy1);
        treeView->setAutoFillBackground(false);
        treeView->setDragEnabled(false);

        gridLayout_2->addWidget(treeView, 1, 0, 1, 1);

        logOutput = new QTextEdit(layoutWidget);
        logOutput->setObjectName(QString::fromUtf8("logOutput"));
        logOutput->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(logOutput->sizePolicy().hasHeightForWidth());
        logOutput->setSizePolicy(sizePolicy2);
        logOutput->setReadOnly(true);

        gridLayout_2->addWidget(logOutput, 2, 0, 1, 2);

        gridLayout_2->setColumnStretch(1, 3);
        tabWidget->addTab(viewer, QString());
        parser = new QWidget();
        parser->setObjectName(QString::fromUtf8("parser"));
        tabWidget->addTab(parser, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        QWidget::setTabOrder(actionType, submitAction);
        QWidget::setTabOrder(submitAction, treeView);
        QWidget::setTabOrder(treeView, Data);
        QWidget::setTabOrder(Data, rawData);
        QWidget::setTabOrder(rawData, pauseButton);
        QWidget::setTabOrder(pauseButton, logSlider);
        QWidget::setTabOrder(logSlider, logOutput);

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
