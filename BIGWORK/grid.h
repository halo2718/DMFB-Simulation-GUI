#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include <QPainter>

class Grid: public QWidget
{
    Q_OBJECT
public:
    int hei;
    int wid;
    Grid(int wid, int hei, QWidget* parent=0);
    void paintEvent(QPaintEvent *ev);
};

#endif // GRID_H
