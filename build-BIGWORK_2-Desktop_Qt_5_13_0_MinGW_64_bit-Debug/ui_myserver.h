/********************************************************************************
** Form generated from reading UI file 'myserver.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYSERVER_H
#define UI_MYSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_myServer
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;

    void setupUi(QDialog *myServer)
    {
        if (myServer->objectName().isEmpty())
            myServer->setObjectName(QString::fromUtf8("myServer"));
        myServer->resize(400, 300);
        buttonBox = new QDialogButtonBox(myServer);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(myServer);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(70, 110, 271, 31));

        retranslateUi(myServer);
        QObject::connect(buttonBox, SIGNAL(accepted()), myServer, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), myServer, SLOT(reject()));

        QMetaObject::connectSlotsByName(myServer);
    } // setupUi

    void retranslateUi(QDialog *myServer)
    {
        myServer->setWindowTitle(QCoreApplication::translate("myServer", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myServer: public Ui_myServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYSERVER_H
