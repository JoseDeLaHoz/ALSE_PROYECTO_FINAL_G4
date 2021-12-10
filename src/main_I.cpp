
#include "dialoglogin.h"
#include "mainw_datos.h"
#include <QApplication>
#include <ctime>


void delay(int secs) {
    for(int i = (time(NULL) + secs); time(NULL) != i; time(NULL));}


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    //DialogLogin w;
    //w.show();
    MainW_datos Ppal;
    Ppal.hide();
    //connect( &w, &DialogLogin::usuarioCorrecto, &Ppal, &MainW_datos::ingresoUsurio);

    return a.exec();
}
