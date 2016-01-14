#include "mediafilemanager.h"

MediaFileManager::MediaFileManager(QObject *parent) : QObject(parent)
{
    fileList<<"C:/Users/Public/Videos/Sample Videos/Wildlife.wmv";
    fileList<<"C:/Users/Public/Videos/Sample Videos/testPlayer1.mp4";
    fileList<<"C:/Users/Public/Videos/Sample Videos/testPlayer2.mp4";
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

}
