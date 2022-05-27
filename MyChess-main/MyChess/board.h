#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPaintEvent>
#include <QPushButton>
#include "stone.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);
    ~Board();
    
    //绘制棋子
    void drawStone(QPainter &p);

    //绘制事件
    void paintEvent(QPaintEvent *event);

    //返回棋盘行列对应的像素坐标
    QPoint center(int id);
    QPoint center(int row,int col);

    //调整下棋轮次
    void set_redTurn();

    //鼠标点击位置
    void click(QPoint pt);
    void click(int id, int row, int col);

    //根据鼠标点击位置确认所在点是否有棋子
    bool getClickRowCol(QPoint pt,int& row ,int& col);

    //鼠标点击事件
    void mouseReleaseEvent(QMouseEvent *);

    // 保存上一步信息
    void saveStep();

    // 重置棋盘
    void resetBoard();

    // 悔棋按钮
    void On_ButtonClick_btRevert();

    // 重启游戏按钮
    void On_ButtonClick_btRestart();

private:
    //上一步棋盘点击位置
    int last_row = -1;
    int last_col = -1;

    //上一步棋子移动前的位置
    int pre_row = -1;
    int pre_col = -1;

    //储存棋盘上棋子对象
    Stone* stones[32];

    //上一步被选中的棋子
    int last_selectedID = -1;

    //上一步被吃掉的棋子
    int last_clickedID = -1;

    //被鼠标选中（第一次鼠标事件）的棋子id
    int _selectedID = -1;

    //被鼠标选中（第二次鼠标事件）的棋子id
    int _clickedID = -1;

    //bool类型储存下棋轮次
    bool _redTurn = true;

    QPushButton btRevert;    // 悔棋按钮
    QPushButton btRestart;   // 重启游戏按钮

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
    float btTop;
    float btLeft;
signals:

};

#endif // BOARD_H
