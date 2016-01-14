#include "siplayer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SiPlayer siplayer;

    siplayer.setFixedSize(800,600);

    siplayer.show();

    return a.exec();
}
