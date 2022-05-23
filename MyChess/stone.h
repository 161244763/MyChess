#ifndef STONE_H
#define STONE_H
#include <QString>

extern int board[15][15];//全局共用棋盘,默认color为0的row从1-5，color为1的row在6-10
extern int last_board[15][15];//全局共用历史上一棋盘

class Stone
{
public:
    enum TYPE {JIANG,JU,MA,XIANG,SHI,PAO,BING,KONG};
    enum SIDE {RED,BLACK,ZHONG};

    Stone();
    Stone(int id);
    ~Stone();

    TYPE getType();

    SIDE getSide();

    int getId();

    bool getDead();
    void setDead(bool situation);

    bool getRiver();
    void setRiver(bool situation);

    int getRow();
    void setRow(int X);

    int getColumn();
    void setColumn(int Y);

    //移动棋子位置
    void move_to(int X, int Y);

    //确定该位置是否属于棋盘
    bool check_pos(int X, int Y);

    //确定棋盘上的某位置是否可以行棋
    int get_move(int X, int Y) ;
    //改变棋盘上可行棋的位置
    void set_move(int X, int Y);

    //各类型棋子的行棋方式
    void build_move();

    //获取各棋子的图片路径
    QString getFilePath();

private:

    int id;
    SIDE side;
    TYPE type;
    bool is_dead;
    bool over_river;
    int row;
    int column;
    int move[15][15];//当前棋子可访问位置，0为不可移动,1为可移动，2为可吃
};

#endif // STONE_H

