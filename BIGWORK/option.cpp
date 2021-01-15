#include "option.h"
#include "ui_option.h"
#include <QDebug>

Option::Option(QDialog* parent):QDialog (parent), ui(new Ui::Option)
{
    qDebug()<<"1";

    ui->setupUi(this);

    ui->lineEdit->setText("0");
    ui->lineEdit_2->setText("0");
    ui->lineEdit_3->setText("0");
    ui->lineEdit_4->setText("0");
    ui->lineEdit_5->setText("0");
    ui->lineEdit_6->setText("0");

    ui->textBrowser->clear();
    ui->textBrowser_2->clear();

    this->setWindowTitle("设置");

    ui->buttonBox->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(shows()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(pushInIn()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(pushInOut()));

    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateButton()));
    connect(ui->lineEdit_2, SIGNAL(textChanged(QString)), this, SLOT(updateButton()));

//    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(generateDot()));

}

void Option::pushInIn()
{
    int p1 = ui->lineEdit_3->text().toInt();
    int p2 = ui->lineEdit_4->text().toInt();

    ui->textBrowser->append(QString::number(p1)+" "+QString::number(p2));
    ui->pushButton_4->setDisabled(false);

    emit sendInput(std::make_pair(p1,p2));
}

void Option::updateButton()
{
    qDebug()<<"here";
    if((ui->lineEdit->text().toInt()>=3||ui->lineEdit_2->text().toInt()>=3)&&(ui->lineEdit->text().toInt()>0&&ui->lineEdit_2->text().toInt()>0))
        ui->buttonBox->setDisabled(false);
    else ui->buttonBox->setDisabled(true);
}

void Option::pushInOut()
{
    qDebug()<<"here";
    int p1 = ui->lineEdit_5->text().toInt();
    int p2 = ui->lineEdit_6->text().toInt();

    ui->pushButton_5->setDisabled(false);
    ui->pushButton_2->setDisabled(true);
    ui->textBrowser_2->append(QString::number(p1)+" "+QString::number(p2));

    emit sendOutput(std::make_pair(p1,p2));
}

void Option::generateDot()
{
 //   int p1 = ui->lineEdit_7->text().toInt();
  //  int p2 = ui->lineEdit_8->text().toInt();

 //   emit sendGenerate(std::make_pair(p1,p2));
}

void Option::shows()
{

    int p1 = ui->lineEdit->text().toInt();
    int p2 = ui->lineEdit_2->text().toInt();

    emit sendSize(p1,p2);
}

void Option::on_pushButton_4_clicked()
{
    ui->textBrowser->clear();
    ui->pushButton_4->setDisabled(true);

    emit clearVector();
}

void Option::on_pushButton_5_clicked()
{
    ui->textBrowser_2->clear();
    ui->pushButton_2->setDisabled(false);
    ui->pushButton_5->setDisabled(true);

    emit clearVectorOut();
}

void Option::processError()
{
    ui->textBrowser->clear();
    ui->textBrowser_2->clear();
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);
    ui->pushButton->setDisabled(false);
    ui->pushButton_2->setDisabled(false);
}
