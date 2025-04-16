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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *labelVector;
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *resizePB;
    QLineEdit *lineEdit;
    QPushButton *sizePB;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *atPB;
    QPushButton *capacityPB;
    QPushButton *clearPB;
    QPushButton *dataPB;
    QPushButton *emptyPB;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *erasePB;
    QPushButton *maxSizePB;
    QPushButton *popBackPB;
    QPushButton *pushBackPB;
    QPushButton *reservePB;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        labelVector = new QLabel(centralwidget);
        labelVector->setObjectName("labelVector");
        labelVector->setGeometry(QRect(140, 170, 511, 20));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(330, 140, 141, 18));
        QFont font;
        font.setBold(true);
        font.setItalic(true);
        label->setFont(font);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(230, 290, 332, 28));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        resizePB = new QPushButton(layoutWidget);
        resizePB->setObjectName("resizePB");

        horizontalLayout_3->addWidget(resizePB);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_3->addWidget(lineEdit);

        sizePB = new QPushButton(layoutWidget);
        sizePB->setObjectName("sizePB");

        horizontalLayout_3->addWidget(sizePB);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(160, 200, 481, 71));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        atPB = new QPushButton(layoutWidget1);
        atPB->setObjectName("atPB");

        horizontalLayout->addWidget(atPB);

        capacityPB = new QPushButton(layoutWidget1);
        capacityPB->setObjectName("capacityPB");

        horizontalLayout->addWidget(capacityPB);

        clearPB = new QPushButton(layoutWidget1);
        clearPB->setObjectName("clearPB");

        horizontalLayout->addWidget(clearPB);

        dataPB = new QPushButton(layoutWidget1);
        dataPB->setObjectName("dataPB");

        horizontalLayout->addWidget(dataPB);

        emptyPB = new QPushButton(layoutWidget1);
        emptyPB->setObjectName("emptyPB");

        horizontalLayout->addWidget(emptyPB);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        erasePB = new QPushButton(layoutWidget1);
        erasePB->setObjectName("erasePB");

        horizontalLayout_2->addWidget(erasePB);

        maxSizePB = new QPushButton(layoutWidget1);
        maxSizePB->setObjectName("maxSizePB");

        horizontalLayout_2->addWidget(maxSizePB);

        popBackPB = new QPushButton(layoutWidget1);
        popBackPB->setObjectName("popBackPB");

        horizontalLayout_2->addWidget(popBackPB);

        pushBackPB = new QPushButton(layoutWidget1);
        pushBackPB->setObjectName("pushBackPB");

        horizontalLayout_2->addWidget(pushBackPB);

        reservePB = new QPushButton(layoutWidget1);
        reservePB->setObjectName("reservePB");

        horizontalLayout_2->addWidget(reservePB);


        verticalLayout->addLayout(horizontalLayout_2);

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
        labelVector->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\272\321\203\321\211\320\270\320\271 \320\262\320\265\320\272\321\202\320\276\321\200 : ", nullptr));
        resizePB->setText(QCoreApplication::translate("MainWindow", "resize", nullptr));
        sizePB->setText(QCoreApplication::translate("MainWindow", "size", nullptr));
        atPB->setText(QCoreApplication::translate("MainWindow", "at", nullptr));
        capacityPB->setText(QCoreApplication::translate("MainWindow", "capacity", nullptr));
        clearPB->setText(QCoreApplication::translate("MainWindow", "clear", nullptr));
        dataPB->setText(QCoreApplication::translate("MainWindow", "data", nullptr));
        emptyPB->setText(QCoreApplication::translate("MainWindow", "empty", nullptr));
        erasePB->setText(QCoreApplication::translate("MainWindow", "erase", nullptr));
        maxSizePB->setText(QCoreApplication::translate("MainWindow", "maxSize", nullptr));
        popBackPB->setText(QCoreApplication::translate("MainWindow", "popBack", nullptr));
        pushBackPB->setText(QCoreApplication::translate("MainWindow", "pushBack", nullptr));
        reservePB->setText(QCoreApplication::translate("MainWindow", "reserve", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
