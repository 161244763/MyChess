#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPaintEvent>

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
signals:

};

#endif // BOARD_H
