#include "stone.h"

Stone::Stone(int id):id(id){
    isDead = false;
    struct POSITION{
        int row;
        int column;
        TYPE type;
    };

    POSITION position[16] = {
        {0,0,JU},
        {0,1,MA},
        {0,2,XIANG},
        {0,3,SHI},
        {0,4,JIANG},
        {0,5,SHI},
        {0,6,XIANG},
        {0,7,MA},
        {0,8,JU},
        {2,1,PAO},
        {2,7,PAO},
        {3,0,BING},
        {3,2,BING},
        {3,4,BING},
        {3,6,BING},
        {3,8,BING}
    };

    if(id<16){
        side = BLACK;
        row = position[id].row;
        column = position[id].column;
        type = position[id].type;
    }else{
        side = RED;
        row = 9 - position[id-16].row;
        column = position[id-16].column;
        type = position[id-16].type;
    }
}

Stone::~Stone(){}

Stone::SIDE Stone::getSide(){
    return side;
}

QString Stone:: getFilePath(){
    switch(this->side){
    case RED:
        switch(this->type){
        case JIANG:
            return ":/img/r_j.png";
        case JU:
            return ":/img/r_c.png";
        case MA:
            return ":/img/r_m.png";
        case XIANG:
            return ":/img/r_x.png";
        case SHI:
            return ":/img/r_s.png";
        case PAO:
            return ":/img/r_p.png";
        case BING:
            return ":/img/r_z.png";
        }
        break;
    case BLACK:
        switch(this->type){
        case JIANG:
            return ":/img/b_j.png";
        case JU:
            return ":/img/b_c.png";
        case MA:
            return ":/img/b_m.png";
        case XIANG:
            return ":/img/b_x.png";
        case SHI:
            return ":/img/b_s.png";
        case PAO:
            return ":/img/b_p.png";
        case BING:
            return ":/img/b_z.png";
        }
        break;
    }
}

float Stone::getRow(){
    return row;
}

float Stone::getColumn(){
    return column;
}
