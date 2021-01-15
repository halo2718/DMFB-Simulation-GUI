/********************************************************************************
** Form generated from reading UI file 'myclient.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCLIENT_H
#define UI_MYCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myClient
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_8;
    QPushButton *pushButton_12;
    QPushButton *pushButton_2;
    QPushButton *pushButton_10;
    QPushButton *pushButton;
    QPushButton *pushButton_7;
    QPushButton *pushButton_9;
    QPushButton *pushButton_11;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QLineEdit *lineEdit;

    void setupUi(QDialog *myClient)
    {
        if (myClient->objectName().isEmpty())
            myClient->setObjectName(QString::fromUtf8("myClient"));
        myClient->resize(740, 254);
        myClient->setMaximumSize(QSize(16777215, 254));
        buttonBox = new QDialogButtonBox(myClient);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(370, 200, 341, 32));
        buttonBox->setMaximumSize(QSize(341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        gridLayoutWidget = new QWidget(myClient);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(40, 100, 667, 80));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_8 = new QPushButton(gridLayoutWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));

        gridLayout->addWidget(pushButton_8, 1, 1, 1, 1);

        pushButton_12 = new QPushButton(gridLayoutWidget);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));

        gridLayout->addWidget(pushButton_12, 1, 5, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton_10 = new QPushButton(gridLayoutWidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));

        gridLayout->addWidget(pushButton_10, 1, 3, 1, 1);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_7 = new QPushButton(gridLayoutWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        gridLayout->addWidget(pushButton_7, 1, 0, 1, 1);

        pushButton_9 = new QPushButton(gridLayoutWidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));

        gridLayout->addWidget(pushButton_9, 1, 2, 1, 1);

        pushButton_11 = new QPushButton(gridLayoutWidget);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));

        gridLayout->addWidget(pushButton_11, 1, 4, 1, 1);

        pushButton_5 = new QPushButton(gridLayoutWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 0, 4, 1, 1);

        pushButton_6 = new QPushButton(gridLayoutWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        gridLayout->addWidget(pushButton_6, 0, 5, 1, 1);

        pushButton_4 = new QPushButton(gridLayoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 0, 3, 1, 1);

        pushButton_3 = new QPushButton(gridLayoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 0, 2, 1, 1);

        lineEdit = new QLineEdit(myClient);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(40, 40, 661, 23));

        retranslateUi(myClient);
        QObject::connect(buttonBox, SIGNAL(accepted()), myClient, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), myClient, SLOT(reject()));

        QMetaObject::connectSlotsByName(myClient);
    } // setupUi

    void retranslateUi(QDialog *myClient)
    {
        myClient->setWindowTitle(QCoreApplication::translate("myClient", "Dialog", nullptr));
        pushButton_8->setText(QCoreApplication::translate("myClient", "7", nullptr));
        pushButton_12->setText(QCoreApplication::translate("myClient", "clear", nullptr));
        pushButton_2->setText(QCoreApplication::translate("myClient", "1", nullptr));
        pushButton_10->setText(QCoreApplication::translate("myClient", "9", nullptr));
        pushButton->setText(QCoreApplication::translate("myClient", "0", nullptr));
        pushButton_7->setText(QCoreApplication::translate("myClient", "6", nullptr));
        pushButton_9->setText(QCoreApplication::translate("myClient", "8", nullptr));
        pushButton_11->setText(QCoreApplication::translate("myClient", ".", nullptr));
        pushButton_5->setText(QCoreApplication::translate("myClient", "4", nullptr));
        pushButton_6->setText(QCoreApplication::translate("myClient", "5", nullptr));
        pushButton_4->setText(QCoreApplication::translate("myClient", "3", nullptr));
        pushButton_3->setText(QCoreApplication::translate("myClient", "2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myClient: public Ui_myClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCLIENT_H
