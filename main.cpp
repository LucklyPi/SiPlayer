#include "siplayer.h"
#include <QApplication>

#include "myxml.h"

//发现一个BUG。当列表中出现一个坏文件，就不能向上翻了
//以现在的逻辑，最后添加的文件将放在后面
//可以简化xml结构
//整理保存xml文件的逻辑

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SiPlayer siplayer;
    siplayer.setFixedSize(800,600);
    siplayer.show();
    return a.exec();
}
