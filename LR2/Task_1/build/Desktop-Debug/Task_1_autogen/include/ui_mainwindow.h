/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTableWidget *tableWidget;
    QPushButton *openFileButton;
    QLineEdit *inputDateEdit;
    QLabel *label_7;
    QLabel *label_8;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *nextDayButton;
    QPushButton *prevDayButton;
    QPushButton *isLeapButton;
    QPushButton *weekNumberButton;
    QPushButton *birthdayButton;
    QPushButton *durationButton;
    QPushButton *addDateButton;
    QPushButton *editDateButton;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(20, 40, 491, 341));
        openFileButton = new QPushButton(centralwidget);
        openFileButton->setObjectName("openFileButton");
        openFileButton->setGeometry(QRect(160, 390, 171, 26));
        inputDateEdit = new QLineEdit(centralwidget);
        inputDateEdit->setObjectName("inputDateEdit");
        inputDateEdit->setGeometry(QRect(640, 10, 141, 26));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(210, 10, 121, 18));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(530, 10, 111, 18));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(530, 40, 141, 261));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        nextDayButton = new QPushButton(layoutWidget);
        nextDayButton->setObjectName("nextDayButton");

        verticalLayout->addWidget(nextDayButton);

        prevDayButton = new QPushButton(layoutWidget);
        prevDayButton->setObjectName("prevDayButton");

        verticalLayout->addWidget(prevDayButton);

        isLeapButton = new QPushButton(layoutWidget);
        isLeapButton->setObjectName("isLeapButton");

        verticalLayout->addWidget(isLeapButton);

        weekNumberButton = new QPushButton(layoutWidget);
        weekNumberButton->setObjectName("weekNumberButton");

        verticalLayout->addWidget(weekNumberButton);

        birthdayButton = new QPushButton(layoutWidget);
        birthdayButton->setObjectName("birthdayButton");

        verticalLayout->addWidget(birthdayButton);

        durationButton = new QPushButton(layoutWidget);
        durationButton->setObjectName("durationButton");

        verticalLayout->addWidget(durationButton);

        addDateButton = new QPushButton(layoutWidget);
        addDateButton->setObjectName("addDateButton");

        verticalLayout->addWidget(addDateButton);

        editDateButton = new QPushButton(layoutWidget);
        editDateButton->setObjectName("editDateButton");

        verticalLayout->addWidget(editDateButton);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(680, 40, 111, 191));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName("label_5");

        verticalLayout_2->addWidget(label_5);

        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName("label_6");

        verticalLayout_2->addWidget(label_6);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        openFileButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        label_7->setText(QString());
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\264\320\260\321\202\321\203 :", nullptr));
        nextDayButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\273\320\265\320\264\321\203\321\216\321\211\320\270\320\271 \320\264\320\265\320\275\321\214", nullptr));
        prevDayButton->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\265\320\264\321\213\320\264\321\203\321\211\320\270\320\271 \320\264\320\265\320\275\321\214", nullptr));
        isLeapButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\270\321\201\320\276\320\272\320\276\321\201\320\275\321\213\320\271?", nullptr));
        weekNumberButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\274\320\265\321\200 \320\275\320\265\320\264\320\265\320\273\320\270", nullptr));
        birthdayButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\320\275\321\214 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\320\265", nullptr));
        durationButton->setText(QCoreApplication::translate("MainWindow", "\320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\264\320\275\320\265\320\271", nullptr));
        addDateButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\264\320\260\321\202\321\203", nullptr));
        editDateButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\264\320\260\321\202\321\203", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
        label_5->setText(QString());
        label_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
