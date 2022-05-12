#include "board.h"
#include <QPainter>
#include <QFile>

Board::Board(QWidget *parent)
    : QWidget{parent}
{
    for(int i = 0;i<32;i++){
        stones[i] = new Stone(i);
    }
}

Board::~Board(){}

void Board::paintEvent(QPaintEvent *event)
{
    //绘制棋盘
    QPainter p(this);
    QPixmap boardImg(":/img/board.png");
    //按比例计算棋盘大小
    float bWidth = boardImg.width();
    float bHeight = boardImg.height();
    float wWidth = this->width();
    float wHeight = this->height();
    float wScale = wHeight / wWidth;      //窗口长宽比
    float bScale = bHeight / bWidth;      //棋盘图片长宽比
    float left = 30,top = 30;           //距左上角距离
    if(wScale>bScale){
        bWidth = wWidth - 60;
        bHeight = bWidth * bScale;
        top = (wHeight - bHeight)/2;
    }else{
        bHeight = wHeight - 60;
        bWidth = bHeight / bScale;
        left = (wWidth - bWidth)/2;
    }
    p.drawPixmap(left, top, bWidth, bHeight, boardImg);


    //绘制棋子
    float sScale = bWidth / boardImg.width();     //棋子缩放比例
    float space = 57 * sScale;
    for(int i=0;i<32;i++){
        float sLeft = left + 10 * sScale + space * stones[i]->getColumn();
        float sTop = top + 10 * sScale + space * stones[i]->getRow();
        p.drawPixmap(sLeft, sTop, 60 * sScale, 60 * sScale, QPixmap(stones[i]->getFilePath()));
    }
}



