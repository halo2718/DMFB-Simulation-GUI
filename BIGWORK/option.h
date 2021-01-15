#ifndef OPTION_H
#define OPTION_H

#include<QDialog>
#include"grid.h"

namespace Ui {

    class Option;

}

class Option: public QDialog
{
    Q_OBJECT
public:
    Option(QDialog* parent=nullptr);
signals:
    void sendSize(int, int);
    void sendInput(std::pair<int,int>);
    void sendOutput(std::pair<int,int>);
    void sendGenerate(std::pair<int,int>);
    void clearVector();
    void clearVectorOut();
public:
    void processError();
private slots:
    void shows();
    void pushInIn();
    void pushInOut();
    void generateDot();
    void updateButton();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::Option *ui;
};

#endif // OPTION_H
