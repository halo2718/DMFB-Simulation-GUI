/********************************************************************************
** Form generated from reading UI file 'upgrade.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPGRADE_H
#define UI_UPGRADE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Upgrade
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QWidget *Upgrade)
    {
        if (Upgrade->objectName().isEmpty())
            Upgrade->setObjectName(QString::fromUtf8("Upgrade"));
        Upgrade->resize(400, 300);
        pushButton = new QPushButton(Upgrade);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(70, 50, 89, 24));
        pushButton_2 = new QPushButton(Upgrade);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 50, 89, 24));
        pushButton_3 = new QPushButton(Upgrade);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(70, 110, 89, 24));
        pushButton_4 = new QPushButton(Upgrade);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(220, 110, 89, 24));

        retranslateUi(Upgrade);

        QMetaObject::connectSlotsByName(Upgrade);
    } // setupUi

    void retranslateUi(QWidget *Upgrade)
    {
        Upgrade->setWindowTitle(QCoreApplication::translate("Upgrade", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("Upgrade", "Queen", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Upgrade", "Bishop", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Upgrade", "Knight", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Upgrade", "Castle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Upgrade: public Ui_Upgrade {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPGRADE_H
