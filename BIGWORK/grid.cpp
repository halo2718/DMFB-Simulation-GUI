#include "grid.h"
#include <QDebug>

Grid::Grid(int x, int y, QWidget* parent)
{
    this->hei = x;
    this->wid = y;
    QWidget* window = new QWidget;
}

void Grid::paintEvent(QPaintEvent *ev)
{
    QPainter paint(this);
    int center_x = width();
    int top = 0.1*height();
    int bottom =0.9*height();
    int left=0.1*width();
    int right=0.9*width();

    paint.setPen(QPen(Qt::black,4));

    qDebug()<<top<<' '<<bottom<<' '<<left<<' '<<right<<" "<<hei<<' '<<wid;

    for(int i=0;i<=hei;i++)
        paint.drawLine(left, top+i*(bottom-top)/hei, right, top+i*(bottom-top)/hei);
    for(int i=0;i<=wid;i++)
        paint.drawLine(left+i*(right-left)/wid, top, left+i*(right-left)/wid, bottom);
}
