#include <QApplication>
#include "HomePage.h"

int main(int argc,char* argv[]){
    QApplication app(argc,argv);
    HomePage HmPage;
    HmPage.resize(600,650);
    HmPage.show();
    return app.exec();
}
