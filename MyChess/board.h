#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPaintEvent>
#include "stone.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);
    ~Board();
    void drawStone(QPainter &p);
    void drawStone(QPainter& painter,int id);
    void paintEvent(QPaintEvent *event);
//    void drawStone(QPainter& p,int id);

    //返回棋盘行列对应的像素坐标
    QPoint center(int id);
    QPoint center(int row,int col);

    //调整下棋轮次
    void set_redTurn();

    void click(QPoint pt);
    void click(int id, int row, int col);
    bool getClickRowCol(QPoint pt,int& row ,int& col);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Stone* stones[32];
    int _selectedID = -1;
    int _clickedID = -1;
    bool _redTurn = true;
    float left;
    float top;
    float bWidth ;
    float bHeight;
    float wWidth ;
    float wHeight;
    float wScale ;
    float bScale ;
    float gHeight;
    float gbHeight;
    float gbWidth;
signals:

};

#endif // BOARD_H
