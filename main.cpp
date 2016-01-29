#include "siplayer.h"
#include <QApplication>


//添加配置类，使用INI文件记录配置
//在视频暂停，和快进快退时，刚刚开始播放时显示文件名和播放进度。
//全屏时隐藏鼠标，音量加减间无效
//以现在的逻辑，后添加的文件将放在后面，没有分类的文件排在前面
//支持多个媒体文件夹

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SiPlayer siplayer;
    siplayer.setFixedSize(800,560);
    siplayer.show();
    return a.exec();
}
