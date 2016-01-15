#include "siplayer.h"
#include <QApplication>

#include "myxml.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SiPlayer siplayer;
    siplayer.setFixedSize(80,60);
    siplayer.show();
    return a.exec();
}
