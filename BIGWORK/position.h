#ifndef POSITION_H
#define POSITION_H

#include <cstdio>
#include <vector>
#include <QPainter>

class position
{
public:
    int R=0;
    int G=0;
    int B=0;
    int countTime=0;
    int direction=0;
    bool occupied=false;
    bool isMerge=false;
    bool isSplit=false;
    bool isBlocked=false;
    std::vector<QColor> pollu;
};

class washPosit
{
public:
    bool blocked=false;
    bool polluted=false;
    bool isVisited=false;
    QString path="";
    int aStar=0;
};

#endif // POSITION_H
