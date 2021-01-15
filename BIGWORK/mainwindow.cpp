#include "mainwindow.h"
#include "option.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <stack>
#include <QUrl>

static std::vector<std::vector<position>> storage;
static std::vector<std::vector<std::queue<std::pair<int,int>>>> mix;

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    op = new Option;
    t = new QTimer(this);

    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_10->setDisabled(true);

    ui->spinBox->hide();
    ui->spinBox_2->hide();
    ui->spinBox_3->hide();
    ui->spinBox_4->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();

    ui->pushButton->setDisabled(true);

    srand(std::time(NULL));
    connect(op, SIGNAL(sendSize(int, int)), this, SLOT(modifiyValue(int, int)));
    connect(op, SIGNAL(sendInput(std::pair<int, int>)), this, SLOT(pushIn(std::pair<int,int>)));
    connect(op, SIGNAL(sendOutput(std::pair<int, int>)), this, SLOT(pushOut(std::pair<int,int>)));
    connect(op, SIGNAL(clearVector()), this, SLOT(clearInput()));
    connect(op, SIGNAL(sendGenerate(std::pair<int, int>)), this, SLOT(pushGenerate(std::pair<int,int>)));
    connect(op, SIGNAL(clearVectorOut()), this, SLOT(clearOutput()));
    connect(t, SIGNAL(timeout()), this, SLOT(autoPlay()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::modifiyValue(int a, int b)
{
    bool flgI=true, flgO=true, flgC=true;
    for(int i=0;i<input.size();i++)
    {
        if(input[i].first!=1&&input[i].first!=a)
            if(input[i].second!=1&&input[i].second!=b)
                flgI=false;
        if(input[i].first<1||input[i].first>a)
            flgI=false;
        if(input[i].second<1||input[i].second>b)
            flgI=false;
        if(input[i]==output)  flgC=false;
    }
    if(output.first!=1&&output.first!=a)
        if(output.second!=1&&output.second!=b)
            flgO=false;
    if(output.first<1||output.first>a)
        flgO=false;
    if(output.second<1||output.second>b)
        flgO=false;
    if(!flgI||!flgC||!flgO)
    {
        if(!flgI) QMessageBox::warning(NULL,"警告","无效的输入端口");
        if(!flgO) QMessageBox::warning(NULL,"警告","无效的输出端口");
        if(!flgC) QMessageBox::warning(NULL,"警告","输入和输出端口重合");
        a=0;
        b=0;
        input.clear();
        output=std::make_pair(-1,-1);
        op->processError();
    }
    this->mainwidth = a;
    this->mainheight = b;
    this->update();
    this->table = new position* [a];
    for(int i=0;i<a;i++)
        this->table [i] = new position[b];
}

void MainWindow::clearInput()
{
    this->input.clear();
}

void MainWindow::autoPlay()
{
    ui->pushButton_6->click();
}

void MainWindow::on_actionSetting_triggered()
{
    time=0;
    m_time=0x3f3f3f;
    start = false;
    end=false;
    retrieved=false;
    block=0;
    QStringList instruction[1000];
    ins.clear();
    toMix.clear();
    drop.clear();
    operation.clear();
    storage.clear();
    mix.clear();
    op->show();
    ui->lcdNumber->display(0);

}

void MainWindow::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);

    if(time>1)  ui->pushButton_3->setDisabled(false);
    else ui->pushButton_3->setDisabled(true);

    if(time>=1)
    {
        ui->pushButton->setDisabled(false);
        ui->pushButton_10->setDisabled(false);
    }

    if(mainwidth==0||mainheight==0) return;

    int center_x = (width()-ui->groupBox->width())/2+ui->groupBox->width();
    int center_y = (height()-ui->menuBar->height())/2+ui->menuBar->height();

    p.setPen(QPen(Qt::black,2));

    int left = center_x-(mainwidth*40)/2;
    int right = center_x+(mainwidth*40)/2;
    int top = center_y-(mainheight*40)/2;
    int bottom = center_y+(mainheight*40)/2;

    for(int i=left;i<=right;i+=40)
        p.drawLine(i, top, i, bottom);
    for(int i=top;i<=bottom;i+=40)
        p.drawLine(left, i, right, i);

    p.setBrush(Qt::blue);

    if(this->input.size()!=0)
    {
        for(auto i: this->input)
        {
            if(i.first==1)
                p.drawRect(left-60, bottom-i.second*40, 60, 40);
            else if(i.second==1)
                p.drawRect(left+(i.first-1)*40, bottom, 40, 60);
            else if(i.first==mainwidth)
                p.drawRect(right, bottom-i.second*40, 60, 40);
            else if(i.second==mainheight)
                p.drawRect(left+(i.first-1)*40, top-60, 40, 60);
        }
    }

    p.setBrush(Qt::green);

    if(this->output!=std::make_pair(-1, -1))
    {
        if(output.first==1)
            p.drawRect(left-60, bottom-output.second*40, 60, 40);
        else if(output.second==1)
            p.drawRect(left+(output.first-1)*40, bottom, 40, 60);
        else if(output.first==mainwidth)
            p.drawRect(right, bottom-output.second*40, 60, 40);
        else
            p.drawRect(left+(output.first-1)*40, top-60, 40, 60);
    }

    p.setBrush(Qt::yellow);
    if(ui->radioButton->isChecked())
    {
        if(mainwidth>0&&mainheight>0)
        {
            for(int i=0;i<mainwidth;i++)
                for(int j=0;j<mainheight;j++)
                    if(table[i][j].isBlocked)
                        p.drawRect(left+i*40, bottom-40-j*40, 40, 40);
        }
    }

    if(block>0){Sleep(block*700);block=0;}

    p.setBrush(QColor(128,0,0));

    if(this->washInput!=std::make_pair(-1, -1))
    {
        if(washInput.first==1)
            p.drawRect(left-60, bottom-washInput.second*40, 60, 40);
        else if(washInput.second==1)
            p.drawRect(left+(washInput.first-1)*40, bottom, 40, 60);
        else if(washInput.first==mainwidth)
            p.drawRect(right, bottom-washInput.second*40, 60, 40);
        else
            p.drawRect(left+(washInput.first-1)*40, top-60, 40, 60);
    }

    p.setBrush(QColor(255,0,0));

    if(this->washOutput!=std::make_pair(-1, -1))
    {
        if(washOutput.first==1)
            p.drawRect(left-60, bottom-washInput.second*40, 60, 40);
        else if(washOutput.second==1)
            p.drawRect(left+(washOutput.first-1)*40, bottom, 40, 60);
        else if(washOutput.first==mainwidth)
            p.drawRect(right, bottom-washOutput.second*40, 60, 40);
        else
            p.drawRect(left+(washOutput.first-1)*40, top-60, 40, 60);
    }

    p.setBrush(Qt::white);

    if(washCur!='E')
    {
        int i=washDrop.first;
        int j=washDrop.second;
        if(washCur=='Q')
        {
            p.drawEllipse(left+i*40, bottom-40-j*40, 40, 40);
        }
        else if(washCur=='W')
        {
            washDrop.second+=1;
            j+=1;
            p.drawEllipse(left+i*40, bottom-40-j*40, 40, 40);
        }
        else if(washCur=='A')
        {
            washDrop.first-=1;
            i-=1;
            p.drawEllipse(left+i*40, bottom-40-j*40, 40, 40);
        }
        else if(washCur=='S')
        {
            washDrop.second-=1;
            j-=1;
            p.drawEllipse(left+i*40, bottom-40-j*40, 40, 40);
        }
        else if(washCur=='D')
        {
            washDrop.first+=1;
            i+=1;
            p.drawEllipse(left+i*40, bottom-40-j*40, 40, 40);
        }
        table[i][j].pollu.clear();
        table[i][j].countTime=0;
    }
    if(start)
    {
        for(int i=0;i<mainwidth;i++)
            for(int j=0;j<mainheight;j++)
            {
                if(table[i][j].B||table[i][j].R||table[i][j].G)
                {
                    p.setBrush(QColor(table[i][j].R,table[i][j].G,table[i][j].B));
                    if(table[i][j].isMerge)
                    {
                        if(table[i][j].direction==1)  p.drawEllipse(left+i*40-40, bottom-40-j*40, 120, 40);
                        else  p.drawEllipse(left+i*40, bottom-80-j*40, 40, 120);
                    }
                    else if(table[i][j].isSplit)
                    {
                        if(table[i][j].direction==1)  p.drawEllipse(left+i*40-40, bottom-40-j*40, 120, 40);
                        else  {
                            p.drawEllipse(left+i*40, bottom-80-j*40, 40, 120);
                        qDebug()<<"Drawing!";
                        }

                    }
                    else  p.drawEllipse(left+i*40, bottom-40-j*40, 40, 40);
                }
                if(table[i][j].pollu.size()&&!table[i][j].occupied&&!end)
                {
                    for(int k=0;k<table[i][j].pollu.size();k++)
                    {
                        p.setBrush(table[i][j].pollu[k]);
                        for(int l=0;l<3;l++)
                        {
                            int deltaX=rand()%29+1;
                            int deltaY=rand()%29+1;
                            p.drawEllipse(left+i*40+deltaX, bottom-40-j*40+deltaY, 10, 10);
                        }
                    }
                }
            }
        if(time<m_time)  end=false;
        if(end)
        {
            ui->pushButton_6->setDisabled(true);
            QFont font("宋体",15,QFont::Bold);
            qDebug()<<"Endl";
            for(int i=0;i<mainwidth;i++)
                for(int j=0;j<mainheight;j++)
                {
                    qDebug()<<table[i][j].countTime;
                    p.setFont(font);
                    p.setPen(Qt::black);
                    p.drawText(left+i*40+5, bottom-j*40-5,QString::number(table[i][j].countTime));
                }
        }
    }
}

void MainWindow::pushIn(std::pair<int, int> pos)
{
    this->input.push_back(pos);
}

void MainWindow::pushOut(std::pair<int, int> pos)
{
    this->output = pos;
}

void MainWindow::pushGenerate(std::pair<int, int> pos)
{
    this->drop.push_back(pos);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->textBrowser->clear();
    time=0;
    m_time=0x3f3f3f;
    start = false;
    end=false;
    retrieved=false;
    block=0;
    instruction->clear();
    ins.clear();
    toMix.clear();
    drop.clear();
    operation.clear();
    storage.clear();
    mix.clear();
    ui->lcdNumber->display(0);
    for(int i=0;i<mainwidth;i++)
        for(int j;j<mainheight;j++)
        {
            table[i][j].isBlocked=false;
            table[i][j].occupied=false;
            table[i][j].countTime=0;
            table[i][j].pollu.clear();
        }

    QString fileName = QFileDialog::getOpenFileName(
                        this, tr("open image file"),
                        "./", tr("List files(*.txt *.php *.dpl *.m3u *.m3u8 *.xspf );;All files (*.*)"));
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->textBrowser->setText("Fail！！");
        return;
    }
    QTextStream txtInput(&file);
    txtInput.setCodec("gb18030");
    QString lineStr;
    while(!txtInput.atEnd())
    {
        lineStr = lineStr + txtInput.readLine() + "\n";
    }
    ui->textBrowser->setText(lineStr);//显示txt文件内容
    ui->pushButton_4->setDisabled(false);
    file.close();
}

void MainWindow::analyze()
{
    QStringList an =ui->textBrowser->toPlainText().split("\n");
}

void MainWindow::on_pushButton_4_clicked()
{
    QStringList an =ui->textBrowser->toPlainText().split(";\n");

    for(int i=0;i<an.size()-1;i++)
    {
        QStringList instruct;
        instruct=an[i].split(",");
        QStringList tmp = instruct[0].split(" ");
        std::vector<int> tt;
        for(int j=1;j<instruct.size();j++)
        {
            tt.push_back(instruct[j].toInt());
        }

        ins.push_back(std::make_pair(tmp[1].toInt(),std::make_pair(tmp[0],tt)));
    }
    bool flg=false,FLG=false;
    for(int i=0;i<ins.size();i++)
    {
        int mark=0;
        if(ins[i].second.first=="Input")
            for(int j=0;j<input.size();j++)
            {
                if(input[j].first==ins[i].second.second[0]&&input[j].second==ins[i].second.second[1])
                {
                    flg=false;
                    break;
                }
                if(j==input.size()-1)  mark=1;
            }
        if(mark)
        {
            flg=true;
            break;
        }
    }
    for(int i=0;i<ins.size();i++)
    {
        if(ins[i].second.first=="Output")
        {
            if(output.first==ins[i].second.second[0]&&output.second==ins[i].second.second[1])
                continue;
            else
            {
                FLG=true;
                break;
            }
        }

    }
    qDebug() <<flg<<FLG;
    if(flg||FLG)
    {
        if(flg)  QMessageBox::warning(NULL,"Warning","输入液滴应当位于输入端口处!");
        if(FLG)  QMessageBox::warning(NULL,"Warning","输出液滴应当位于输出端口处!");
        ui->pushButton_4->setDisabled(true);
    }
    else
    {
        ui->pushButton_2->setDisabled(false);
        ui->pushButton_6->setDisabled(false);
        ui->pushButton_4->setDisabled(true);
    }
}

bool MainWindow::staticCheck()
{
    for(int i=0;i<mainwidth;i++)
        for(int j=0;j<mainheight;j++)
        {
            if(table[i][j].occupied)
            {
                if(i+1<mainwidth)
                {
                    if(j+1<mainheight)
                    {
                        if(table[i+1][j+1].occupied)
                            return false;
                    }
                    if(j-1>=0)
                    {
                        if(table[i+1][j-1].occupied)
                            return false;
                    }
                    if(table[i+1][j].occupied)
                        return false;
                }
                if(i-1>=0)
                {
                    if(j+1<mainheight)
                    {
                        if(table[i-1][j+1].occupied)
                            return false;
                    }
                    if(j-1>=0)
                    {
                        if(table[i-1][j-1].occupied)
                            return false;
                    }
                    if(table[i-1][j].occupied)
                        return false;
                }
                if(j+1<mainheight)
                {
                    if(table[i][j+1].occupied)
                        return false;
                }
                if(j-1>=0)
                {
                    if(table[i][j-1].occupied)
                        return false;
                }
            }
        }
    ui->pushButton_6->setEnabled(true);
    return true;
}

bool MainWindow::dynamicCheck()
{
    position ref[mainwidth][mainheight];
    for(int i=0;i<mainwidth;i++)
        for(int j=0;j<mainheight;j++)
        {
            ref[i][j]=storage[time-1][i*mainheight+j];
        }
    for(int i=0;i<mainwidth;i++)
        for(int j=0;j<mainheight;j++)
        {
            if(table[i][j].occupied)
            {
                if(i+1<mainwidth)
                {
                    if(j+1<mainheight)
                    {
                        if(ref[i+1][j+1].occupied)
                            return false;
                    }
                    if(j-1>=0)
                    {
                        if(ref[i+1][j-1].occupied)
                            return false;
                    }
                    if(ref[i+1][j].occupied)
                        return false;
                }
                if(i-1>=0)
                {
                    if(j+1<mainheight)
                    {
                        if(ref[i-1][j+1].occupied)
                            return false;
                    }
                    if(j-1>=0)
                    {
                        if(ref[i-1][j-1].occupied)
                            return false;
                    }
                    if(ref[i-1][j].occupied)
                        return false;
                }
                if(j+1<mainheight)
                {
                    if(ref[i][j+1].occupied)
                        return false;
                }
                if(j-1>=0)
                {
                    if(ref[i][j-1].occupied)
                        return false;
                }
            }
        }
    ui->pushButton_6->setEnabled(true);
    return true;
}

void MainWindow::on_pushButton_6_clicked()
{
    start = true;
    bool stat=true, dyna=true;
    int isEnd=1;
    std::queue<std::pair<int,int>>que;
    ui->lcdNumber->display(time);
    for(int i=0;i<toMix.size();i++)
        if(toMix[i].size()!=0)
            isEnd=0;
    for(int i=0;i<ins.size();i++)
        if(time<=ins[i].first)
            isEnd=0;
    for(int i=0;i<mainwidth;i++)
         for(int j=0;j<mainheight;j++)
             if(table[i][j].isMerge==1)
                 isEnd=0;
    this->end=isEnd;
    for(int i=0;i<mainwidth;i++)
        for(int j=0;j<mainheight;j++)
            if(table[i][j].isMerge)
            {
                table[i][j].isMerge=0;
                table[i][j].direction=0;
                this->update();
            }
    for(int i=0;i<mainwidth;i++)
        for(int j=0;j<mainheight;j++)
            if(table[i][j].isSplit)
            {
                player=new QMediaPlayer;
                player->setMedia(QUrl::fromLocalFile("G5.mp3"));
                player->setVolume(50);
                player->play();
                this->repaint();
                table[i][j].isSplit=0;
                table[i][j].direction=0;
            }
    if(!isEnd)
    {
        for(int i=0;i<ins.size();i++)
            if(ins[i].first==time)
            {
                if(ins[i].second.first=="Input")
                {
                    int r = rand()%256;
                    int g = rand()%256;
                    int b = rand()%256;
                    this->table[ins[i].second.second[0]-1][ins[i].second.second[1]-1].R=r;
                    this->table[ins[i].second.second[0]-1][ins[i].second.second[1]-1].G=g;
                    this->table[ins[i].second.second[0]-1][ins[i].second.second[1]-1].B=b;
                    this->table[ins[i].second.second[0]-1][ins[i].second.second[1]-1].occupied=true;
                    this->table[ins[i].second.second[0]-1][ins[i].second.second[1]-1].countTime+=1;
                    this->table[ins[i].second.second[0]-1][ins[i].second.second[1]-1].pollu.push_back(QColor(r,g,b));
                }
                else if(ins[i].second.first=="Move")
                {

                    int x1=ins[i].second.second[0]-1;
                    int y1=ins[i].second.second[1]-1;
                    int x2=ins[i].second.second[2]-1;
                    int y2=ins[i].second.second[3]-1;

                    if(!table[x1][y1].occupied)
                    {
                        QMessageBox::warning(NULL,"警告","无效移动");
                        ui->pushButton_2->setDisabled(true);
                        ui->pushButton_6->setDisabled(true);
                        t->stop();
                        break;
                    }
                    else
                    {
                        table[x2][y2].R=table[x1][y1].R;
                        table[x2][y2].G=table[x1][y1].G;
                        table[x2][y2].B=table[x1][y1].B;

                        table[x2][y2].occupied=true;
                        table[x1][y1].occupied=false;
                        table[x1][y1].R=0;
                        table[x1][y1].G=0;
                        table[x1][y1].B=0;
                        table[x2][y2].countTime++;

                        player=new QMediaPlayer;
                        player->setMedia(QUrl::fromLocalFile("C5.mp3"));
                        player->setVolume(50);
                        player->play();

                        table[x2][y2].pollu.push_back(QColor(table[x2][y2].R,table[x2][y2].G,table[x2][y2].B));
                    }

                }
                else if(ins[i].second.first=="Merge")
                {
                    int x1=ins[i].second.second[0]-1;
                    int y1=ins[i].second.second[1]-1;
                    int x2=ins[i].second.second[2]-1;
                    int y2=ins[i].second.second[3]-1;
                    int m1=(x1+x2)/2;
                    int m2=(y1+y2)/2;

                    if(table[x1][y1].occupied&&table[x2][y2].occupied)
                    {
                        table[m1][m2].R= (table[x1][y1].R+table[x2][y2].R)/2;
                        table[m1][m2].G= (table[x1][y1].G+table[x2][y2].G)/2;
                        table[m1][m2].B= (table[x1][y1].B+table[x2][y2].B)/2;
                        table[x1][y1].occupied=false;
                        table[x2][y2].occupied=false;
                        table[m1][m2].occupied=true;
                        table[m1][m2].isMerge=true;

                        table[x1][y1].R=0;
                        table[x1][y1].G=0;
                        table[x1][y1].B=0;
                        table[x2][y2].R=0;
                        table[x2][y2].G=0;
                        table[x2][y2].B=0;

                        table[m1][m2].countTime+=1;
                        table[m1][m2].pollu.push_back(QColor(table[m1][m2].R,table[m1][m2].G,table[m1][m2].B));

                        player=new QMediaPlayer;
                        player->setMedia(QUrl::fromLocalFile("D5.mp3"));
                        player->setVolume(50);
                        player->play();

                        (x1==x2)?table[m1][m2].direction=2:table[m1][m2].direction=1;
                    }

                    else
                    {
                        QMessageBox::warning(NULL,"警告","无效移动");
                        ui->pushButton_2->setDisabled(true);
                        ui->pushButton_6->setDisabled(true);
                        t->stop();
                        break;
                    }
                }
                else if(ins[i].second.first=="Mix")
                {
                    player=new QMediaPlayer;
                    player->setMedia(QUrl::fromLocalFile("C5.mp3"));
                    player->setVolume(50);
                    player->play();
                    for(int j=0;j<ins[i].second.second.size();j+=2)
                        que.push(std::make_pair(ins[i].second.second[j],ins[i].second.second[j+1]));
                    this->toMix.push_back(que);
                }
                else if(ins[i].second.first=="Output")
                {
                    int x=ins[i].second.second[0]-1;
                    int y=ins[i].second.second[1]-1;

                    if(!table[x][y].occupied)
                    {
                        QMessageBox::warning(NULL,"警告","无效移动");
                        ui->pushButton_2->setDisabled(true);
                        ui->pushButton_6->setDisabled(true);
                        t->stop();
                        break;
                    }
                    else
                    {
                        table[x][y].R=0;
                        table[x][y].G=0;
                        table[x][y].B=0;
                        table[x][y].occupied=false;
                    }
                }
                else if(ins[i].second.first=="Split")
                {
                    int x1=ins[i].second.second[0]-1;
                    int y1=ins[i].second.second[1]-1;
                    int x2=ins[i].second.second[2]-1;
                    int y2=ins[i].second.second[3]-1;
                    int x3=ins[i].second.second[4]-1;
                    int y3=ins[i].second.second[5]-1;

                    if(!table[x1][y1].occupied)
                    {
                        QMessageBox::warning(NULL,"警告","无效移动");
                        ui->pushButton_2->setDisabled(true);
                        ui->pushButton_6->setDisabled(true);
                        t->stop();
                        break;
                    }
                    else
                    {
                        int r1 = rand()%256;
                        int r2 = rand()%256;
                        int g1 = rand()%256;
                        int g2 = rand()%256;
                        int b1 = rand()%256;
                        int b2 = rand()%256;

                        table[x1][y1].isSplit=true;

                        player=new QMediaPlayer;
                        player->setMedia(QUrl::fromLocalFile("A5.mp3"));
                        player->setVolume(50);
                        player->play();

                        (x2==x3)?table[x1][y1].direction=2:table[x1][y1].direction=1;

                        if(time>=0)
                        {
                            std::vector<position> tmp;
                            for(int i=0;i<mainwidth;i++)
                                for(int j=0;j<mainheight;j++)
                                    tmp.push_back(table[i][j]);
                            storage.push_back(tmp);
                            mix.push_back(this->toMix);
                        }

                        this->repaint();

                        table[x1][y1].R=0;
                        table[x1][y1].G=0;
                        table[x1][y1].B=0;
                        table[x1][y1].occupied=false;

                        table[x2][y2].R=r1;
                        table[x2][y2].G=g1;
                        table[x2][y2].B=b1;
                        table[x2][y2].occupied=true;

                        table[x3][y3].R=r2;
                        table[x3][y3].G=g2;
                        table[x3][y3].B=b2;
                        table[x3][y3].occupied=true;

                        table[x2][y2].pollu.push_back(QColor(table[x2][y2].R,table[x2][y2].G,table[x2][y2].B));
                        table[x3][y3].pollu.push_back(QColor(table[x3][y3].R,table[x3][y3].G,table[x3][y3].B));

                        table[x2][y2].countTime++;
                        table[x3][y3].countTime++;

                        stat=staticCheck();
                        dyna=dynamicCheck();

                        time++;
                        return;
                    }
                }
            }
        for(int j=0;j<toMix.size();j++)
        {
            if(toMix[j].size()>=2)
            {
                int x1 = toMix[j].front().first-1;
                int y1 = toMix[j].front().second-1;
                toMix[j].pop();
                int x2 = toMix[j].front().first-1;
                int y2 = toMix[j].front().second-1;

                if(!table[x1][y1].occupied)
                {
                    QMessageBox::warning(NULL,"警告","无效移动");
                    ui->pushButton_2->setDisabled(true);
                    ui->pushButton_6->setDisabled(true);
                    t->stop();
                    break;
                }

                else
                {
                    table[x2][y2].R=table[x1][y1].R;
                    table[x2][y2].G=table[x1][y1].G;
                    table[x2][y2].B=table[x1][y1].B;

                    table[x2][y2].occupied=true;
                    table[x1][y1].occupied=false;
                    table[x1][y1].R=0;
                    table[x1][y1].G=0;
                    table[x1][y1].B=0;
                    table[x2][y2].countTime++;
                    table[x2][y2].pollu.push_back(QColor(table[x2][y2].R,table[x2][y2].G,table[x2][y2].B));

                    player=new QMediaPlayer;
                    player->setMedia(QUrl::fromLocalFile("C5.mp3"));
                    player->setVolume(50);
                    player->play();
                }

                if(toMix[j].size()==1)
                    toMix[j].pop();
            }
        }
        if(time>=0)
        {
            std::vector<position> tmp;
            for(int i=0;i<mainwidth;i++)
                for(int j=0;j<mainheight;j++)
                    tmp.push_back(table[i][j]);
            storage.push_back(tmp);
            mix.push_back(this->toMix);
        }
        this->update();
        stat=staticCheck();
        time++;
    }
    else
    {
        m_time=time;
        qDebug()<<"End";
        for(int i=0;i<mainwidth;i++)
            for(int j=0;j<mainheight;j++)
            {
                table[i][j].R=0;
                table[i][j].G=0;
                table[i][j].B=0;
            }
        ui->pushButton_6->setDisabled(true);
        t->stop();
        this->repaint();
    }
    if(!stat||!dyna)
    {
        QMessageBox::about(NULL,"error","wrong");
        ui->pushButton_6->setEnabled(false);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    this->retrieved=true;
    this->time--;
    storage.pop_back();
    mix.pop_back();
    for(int i=0;i<mainwidth;i++)
        for(int j=0;j<mainheight;j++)
        {
            table[i][j]=storage[this->time-1][i*mainheight+j];
//            qDebug()<<this->time<<storage[this->time-1][i*mainheight+j].R<<storage[this->time-1][i*mainwidth+j].G<<storage[this->time][i*mainwidth+j].B;
        }
    if(!this->toMix.empty())
        this->toMix.clear();
    if(!mix.empty())
        for(int i=0;i<mix[this->time-1].size();i++)
            this->toMix.push_back(mix[this->time-1][i]);
    ui->pushButton_6->setDisabled(false);
    ui->pushButton_2->setDisabled(false);
    this->repaint();
}

void MainWindow::on_pushButton_2_clicked()
{
    block = 1;
    t->start(1000);
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::RightButton&&ui->radioButton->isChecked()&&mainwidth>0&&mainheight>0)
    {
        int x = ev->x();
        int y = ev->y();
        int center_x = (width()-ui->groupBox->width())/2+ui->groupBox->width();
        int center_y = (height()-ui->menuBar->height())/2+ui->menuBar->height();
        int left = center_x-(mainwidth*40)/2;
        int right = center_x+(mainwidth*40)/2;
        int top = center_y-(mainheight*40)/2;
        int bottom = center_y+(mainheight*40)/2;

        int wi=(x-left)/40;
        int yi=(bottom-y)/40;

        if(wi>=0&&wi<mainwidth&&yi>=0&&yi<mainheight)
            table[wi][yi].isBlocked=!table[wi][yi].isBlocked;

        this->repaint();
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    t->stop();
}

void MainWindow::on_radioButton_clicked(bool checked)
{
    if(checked)
    {
        ui->spinBox->show();
        ui->spinBox_2->show();
        ui->spinBox_3->show();
        ui->spinBox_4->show();
        ui->pushButton_8->show();
        ui->pushButton_9->show();
        ui->spinBox->setMaximum(mainwidth);
        ui->spinBox_2->setMaximum(mainheight);
        ui->spinBox_3->setMaximum(mainwidth);
        ui->spinBox_4->setMaximum(mainheight);
        ui->spinBox->setMinimum(1);
        ui->spinBox_2->setMinimum(1);
        ui->spinBox_3->setMinimum(1);
        ui->spinBox_4->setMinimum(1);
        washInput = std::make_pair(-1,-1);
        washOutput = std::make_pair(-1,-1);
    }
    else
    {
        ui->spinBox->hide();
        ui->spinBox_2->hide();
        ui->spinBox_3->hide();
        ui->spinBox_4->hide();
        ui->pushButton_8->hide();
        ui->pushButton_9->hide();
    }
    this->update();
}

void MainWindow::on_pushButton_8_clicked()
{
    int x = ui->spinBox->value();
    int y = ui->spinBox_2->value();

    washInput=std::make_pair(x,y);

    this->update();
}

void MainWindow::on_pushButton_9_clicked()
{
    int x = ui->spinBox_3->value();
    int y = ui->spinBox_4->value();

    washOutput=std::make_pair(x,y);

    this->update();
}

void MainWindow::on_pushButton_clicked()
{
    t->stop();
    QTimer *tmp = new QTimer(this);
    washPosit process[mainwidth][mainheight];
    for(int i=0;i<mainwidth;i++)
        for(int j=0;j<mainheight;j++)
            if(table[i][j].occupied)
                for(int k=i-1;k<=i+1;k++)
                    for(int l=j-1;l<=j+1;l++)
                        if(k>=0&&k<mainwidth&&l>=0&&l<mainheight)
                            process[k][l].blocked=true;
    for(int i=0;i<mainwidth;i++)
        for(int j=0;j<mainheight;j++)
            if(table[i][j].isBlocked)
                process[i][j].blocked=true;
    for(int i=0;i<mainwidth;i++)
        for(int j=0;j<mainheight;j++)
            if(table[i][j].pollu.size()>0)
                process[i][j].polluted=true;
    if(process[washInput.first-1][washInput.second-1].blocked)
    {
        QMessageBox::warning(NULL,"警告","无法加入清洗液滴");
        return;
    }
    std::stack<std::pair<int,int>> test;
    test.push(std::make_pair(washInput.first-1, washInput.second-1));
    bool access=false;
    while(!test.empty())
    {
        std::pair<int,int> focus=test.top();
        test.pop();
        int x = focus.first;
        int y = focus.second;
        qDebug()<<x<<y;
        process[x][y].isVisited=true;
        if(focus.first==washOutput.first-1&&focus.second==washOutput.second-1)
        {
            qDebug()<<"Accessible!";
            access=true;
            break;
        }
        else
        {
            if(x-1>=0&&!process[x-1][y].isVisited&&!process[x-1][y].blocked)
            {
                test.push(std::make_pair(x-1,y));
//                process[x-1][y].path=process[x][y].path+"A";
            }
            if(y-1>=0&&!process[x][y-1].isVisited&&!process[x][y-1].blocked)
            {
                test.push(std::make_pair(x,y-1));
//                process[x][y-1].path=process[x][y].path+"S";

            }
            if(x+1<mainwidth&&!process[x+1][y].isVisited&&!process[x+1][y].blocked)
            {
                test.push(std::make_pair(x+1,y));
//                process[x+1][y].path=process[x][y].path+"D";
                qDebug()<<"path"<<process[x+1][y].path;
            }
            if(y+1<mainheight&&!process[x][y+1].isVisited&&!process[x][y+1].blocked)
            {
                test.push(std::make_pair(x,y+1));
//                process[x][y+1].path=process[x][y].path+"W";
            }
        }
    }
    if(access)
    {
        QString movePath;
        for(int i=0;i<mainwidth;i++)
            for(int j=0;j<mainheight;j++)
            {
                process[i][j].isVisited=false;
                process[i][j].path="";
            }
        std::pair<int,int> cur=std::make_pair(washInput.first-1, washInput.second-1);
        int cnt=0;
        for(int i=0;i<mainwidth;i++)
            for(int j=0;j<mainheight;j++)
                if(!process[i][j].blocked&&process[i][j].polluted)
                    cnt++;
        while(cnt>=0)
        {
            int min=0x3f3f3f;
            std::pair<int,int> aim;
            if(cnt>0)
            {
                for(int i=0;i<mainwidth;i++)
                    for(int j=0;j<mainheight;j++)
                        if(!process[i][j].blocked&&process[i][j].polluted)
                        {
                            int dis=abs(cur.first-i)+abs(cur.second-j);
                            qDebug()<<dis;
                            if(dis<min)
                            {
                                min=dis;
                                aim.first=i;
                                aim.second=j;
                            }
                        }
            }
            else
            {
                aim.first=washOutput.first-1;
                aim.second=washOutput.second-1;
            }
            std::queue<std::pair<int,int>> findPath;
            findPath.push(cur);
            while(!findPath.empty())
            {
                std::pair<int,int> focus=findPath.front();
                findPath.pop();
                int x = focus.first;
                int y = focus.second;
                qDebug()<<x<<y;
                process[x][y].isVisited=true;
                if(focus.first==aim.first&&focus.second==aim.second)
                {
                    qDebug()<<"Accessible!";
                    access=true;
                    break;
                }
                else
                {
                    if(x+1<mainwidth&&!process[x+1][y].isVisited&&!process[x+1][y].blocked)
                    {
                        findPath.push(std::make_pair(x+1,y));
                        process[x+1][y].path=process[x][y].path+"D";
                        qDebug()<<"path"<<process[x+1][y].path;
                    }
                    if(y+1<mainheight&&!process[x][y+1].isVisited&&!process[x][y+1].blocked)
                    {
                        findPath.push(std::make_pair(x,y+1));
                        process[x][y+1].path=process[x][y].path+"W";
                    }
                    if(x-1>=0&&!process[x-1][y].isVisited&&!process[x-1][y].blocked)
                    {
                        findPath.push(std::make_pair(x-1,y));
                        process[x-1][y].path=process[x][y].path+"A";
                    }
                    if(y-1>=0&&!process[x][y-1].isVisited&&!process[x][y-1].blocked)
                    {
                        findPath.push(std::make_pair(x,y-1));
                        process[x][y-1].path=process[x][y].path+"S";

                    }
                }
            }
            for(int i=0;i<mainwidth;i++)
                for(int j=0;j<mainheight;j++)
                    if(!(aim.first==i&&aim.second==j))
                    {
                        process[i][j].isVisited=false;
                        process[i][j].path="";
                    }
            qDebug()<<"intermediate path"<<process[aim.first][aim.second].path;
            movePath=process[aim.first][aim.second].path;
            process[aim.first][aim.second].polluted=false;
            cur.first=aim.first;
            cur.second=aim.second;
            cnt--;
        }
        pathIns=movePath;
        for(int i=-1;i<=pathIns.size();i++)
        {
            if(i==-1)
            {
                washDrop.first=washInput.first-1;
                washDrop.second=washInput.second-1;
                washCur='Q';
            }
            if(i>=0)
            {
                washCur=pathIns[i];
            }
            if(i==pathIns.size())
                washCur='E';
            Sleep(200);
            this->repaint();
        }
    }
    else
    {
        QMessageBox::warning(NULL,"警告","Waste端口不可达");
        return;
    }
    this->repaint();
}

void MainWindow::on_pushButton_10_clicked()
{
    this->retrieved=true;
    this->time=1;
    for(int i=0;i<mainwidth;i++)
        for(int j=0;j<mainheight;j++)
        {
            table[i][j]=storage[0][i*mainheight+j];
//            qDebug()<<this->time<<storage[this->time-1][i*mainheight+j].R<<storage[this->time-1][i*mainwidth+j].G<<storage[this->time][i*mainwidth+j].B;
        }
    storage.clear();
    mix.clear();
    if(!this->toMix.empty())
        this->toMix.clear();
    ui->pushButton_6->setDisabled(false);
    ui->pushButton_2->setDisabled(false);
    this->repaint();
}
