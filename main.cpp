#include "siplayer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SiPlayer siplayer("F:/Media/11.mp4");
    siplayer.setFixedSize(800,600);
    siplayer.show();
    return a.exec();
}
