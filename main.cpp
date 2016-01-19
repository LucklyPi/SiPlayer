#include "siplayer.h"
#include <QApplication>

#include "myxml.h"

//实现返回键重新播放
//实现分类机制
//以现在的逻辑，后添加的文件将放在后面
//支持便于电视剧播放的机制，即按上下间切换整个文件夹内容
//在视频暂停，和快进快退时，刚刚开始播放时显示文件名和播放进度。

//xml文件的保存策略
//1、每隔一分钟保存一次 验证一下按关机键关机的时候是否调用了closeEvent，如果调用了，每分钟保存也去掉
//2、退出时保存

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SiPlayer siplayer;
    siplayer.setFixedSize(200,160);
    siplayer.show();
    return a.exec();
}
