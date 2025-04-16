/********************************************************************************
** Form generated from reading UI file 'matrixdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIXDIALOG_H
#define UI_MATRIXDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MatrixDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;

    void setupUi(QDialog *MatrixDialog)
    {
        if (MatrixDialog->objectName().isEmpty())
            MatrixDialog->setObjectName("MatrixDialog");
        MatrixDialog->resize(400, 300);
        layoutWidget = new QWidget(MatrixDialog);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 30, 371, 211));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(layoutWidget);
        tableWidget->setObjectName("tableWidget");

        horizontalLayout->addWidget(tableWidget);


        retranslateUi(MatrixDialog);

        QMetaObject::connectSlotsByName(MatrixDialog);
    } // setupUi

    void retranslateUi(QDialog *MatrixDialog)
    {
        MatrixDialog->setWindowTitle(QCoreApplication::translate("MatrixDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatrixDialog: public Ui_MatrixDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIXDIALOG_H
