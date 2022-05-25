#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPushButton>
#include "board.h"

//绘制主菜单
class HomePage : public QWidget
{
    Q_OBJECT
public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();
    void paintEvent(QPaintEvent *event);   // 绘制界面
    void on_ButtonStart_Click();           // 开始游戏
    void on_ButtonQuit_Click();            // 退出游戏

private:
    QPushButton btStart;    // 开始游戏按钮
    QPushButton btQuit;     // 退出游戏按钮
    Board board;            // 游戏棋盘界面
signals:

};

#endif // HOMEPAGE_H
