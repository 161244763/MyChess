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
    void paintEvent(QPaintEvent *event);
//    void drawStone(QPainter& p,int id);

private:
    Stone* stones[32];
signals:

};

#endif // BOARD_H
