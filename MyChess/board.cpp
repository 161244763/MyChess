#include "Board.h"
#include <QPainter>
#include <QFile>

Board::Board(QWidget *parent)
    : QWidget{parent}
{
}

void Board::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPixmap boardImg(":/img/board.png");
    //按比例计算棋盘大小
    float imgWidth = boardImg.width();
    float imgHeight = boardImg.height();
    float winWidth = this->width();
    float winHeight = this->height();
    float wScale = winHeight/winWidth;  //窗口长宽比
    float imgScale = imgHeight/imgWidth;//棋盘图片长宽比
    float left = 30,top = 30;           //距左上角距离
    if(wScale>imgScale){
        imgWidth = winWidth - 60;
        imgHeight = imgWidth * imgScale;
        top = (winHeight - imgHeight)/2;
    }else{
        imgHeight = winHeight - 60;
        imgWidth = imgHeight /imgScale;
        left = (winWidth - imgWidth)/2;
    }
    p.drawPixmap(left,top,imgWidth,imgHeight,boardImg);

}

