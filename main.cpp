#include "siplayer.h"
#include <QApplication>

#include "myxml.h"

//发现一个BUG。当列表中出现一个坏文件，就不能向上翻了
//以现在的逻辑，最后添加的文件将放在后面
//整理保存xml文件的逻辑
//支持便于电视剧播放的机制，即按上下间切换整个文件夹内容
//在视频暂停，和快进快退时，刚刚开始播放时显示文件名和播放进度。

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SiPlayer siplayer;
    siplayer.setFixedSize(200,160);
    siplayer.showFullScreen();
    return a.exec();
}
