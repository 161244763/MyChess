#include <QApplication>
#include "HomePage.h"

int main(int argc,char* argv[]){
    QApplication app(argc,argv);
    HomePage HmPage;
    HmPage.resize(590,640);
    HmPage.show();
    return app.exec();
}
