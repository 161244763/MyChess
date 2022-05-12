#include <QApplication>
#include "board.h"

int main(int argc,char* argv[]){
    QApplication app(argc,argv);
    Board board;
    board.resize(590,640);
    board.show();
    return app.exec();
}
