#ifndef STONE_H
#define STONE_H
#include <QString>


class Stone
{
public:
    Stone(int id);
    ~Stone();
    enum TYPE {JIANG,JU,MA,XIANG,SHI,PAO,BING};
    enum SIDE {RED,BLACK};
    QString getFilePath();
    SIDE getSide();
    float getRow();
    float getColumn();

private:

    float row;
    float column;
    int id;
    SIDE side;
    bool isDead;
    TYPE type;
};

#endif // STONE_H
