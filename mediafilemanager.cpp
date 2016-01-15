#include "mediafilemanager.h"

#include <QDebug>
#include <QDir>

MediaFileManager::MediaFileManager(QObject *parent) : QObject(parent)
{
    QDir dir("F:/Media");
    fileList = dir.entryList(QDir::Files,QDir::Name);
    for(int i = 0; i < fileList.size(); i++)
    {
        fileList.replace(i,"F:/Media/"+fileList.at(i));
        qDebug()<<fileList.at(i);
    }
    curFileIndex = -1;
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
