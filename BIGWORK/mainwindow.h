#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QTimer>
#include <queue>
#include "option.h"
#include "position.h"
#include <QtMultimedia/QMediaPlayer>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Option* op;
    int time=0;
    int m_time=0x3f3f3f;
    int mainwidth = 0;
    int mainheight = 0;
    bool start = false;
    bool end=false;
    bool retrieved=false;
    int block=0;
    QMediaPlayer* player=new QMediaPlayer;
    QStringList instruction[1000];
    QString pathIns;
    QChar washCur='E';
    QTimer* t;
    std::vector<std::pair<int, std::pair<QString, std::vector<int>>>> ins;
    std::vector<std::queue<std::pair<int,int>>> toMix;
    std::vector<std::pair<int,int>> drop;
    std::vector<std::pair<int, int>> input;
    std::pair<int, int> output = std::make_pair(-1,-1);
    std::pair<int, int> washInput = std::make_pair(-1,-1);
    std::pair<int, int> washOutput = std::make_pair(-1,-1);
    std::pair<int, int> washDrop = std::make_pair(-1,-1);
    std::vector<std::vector<int>> operation;
    position** table;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSetting_triggered();
    void modifiyValue(int, int);
    void pushIn(std::pair<int, int>);
    void pushOut(std::pair<int, int>);
    void pushGenerate(std::pair<int, int>);
    void on_pushButton_5_clicked();
    void analyze();
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void autoPlay();
    void clearInput();
    void clearOutput(){output=std::make_pair(-1,-1);}
/*signals:
    void errorCalled(){}*/
    void on_pushButton_7_clicked();

    void on_radioButton_clicked(bool checked);

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *ev);
    void mousePressEvent(QMouseEvent* ev);
    bool staticCheck();
    bool dynamicCheck();
};

#endif // MAINWINDOW_H
