#include "mediafilemanager.h"

#include <QDebug>
MediaFileManager::MediaFileManager(QObject *parent) : QObject(parent)
{
    fileList<<"F:/Media/尘__金志文.mp4";
    fileList<<"F:/Media/第一次爱的人_王心凌.mp4";
    fileList<<"F:/Media/蜉蝣_华晨宇.mp4";
    fileList<<"F:/Media/一个人的日子_王心凌.mp4";
    fileList<<"F:/Media/永不放弃_大张伟.mp4";
    curFileIndex = 0;
}

MediaFileManager::~MediaFileManager()
{

}


QString MediaFileManager::getNextFileName()
{
    if(++curFileIndex >= fileList.size())
        curFileIndex = 0;

    return fileList.at(curFileIndex);
}

QString MediaFileManager::getPrevFileName()
{
    if(--curFileIndex < 0)
        curFileIndex = fileList.size()-1;
    return fileList.at(curFileIndex);
}
