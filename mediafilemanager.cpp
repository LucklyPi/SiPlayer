#include "mediafilemanager.h"


#include <QDebug>
#include <QDir>

MediaFileManager::MediaFileManager(QObject *parent) : QObject(parent)
{
    //QDir dir("F:/Media");
    //fileList = dir.entryList(QDir::Files,QDir::Name);
    xml = new MyXML("F:/Media/filelist.xml");
    xml->getFileList(&fileList);
    /*FileElement element = {0};
    for(int i = 0; i < fileList.size(); i++)
    {
        fileList.replace(i,"F:/Media/"+fileList.at(i));
        qDebug()<<fileList.at(i);
        element.fileName = fileList.at(i);
        xml->addElement(element);
    }
    xml->saveXMLtoFile();
    if (xml->getElement(fileList.at(3),&element)) {
        qDebug()<<element.fileName;
        qDebug()<<element.lastPosition;
        qDebug()<<element.lastPlayTime;
    }*/

    //发现一个BUG。当列表中出现一个坏文件，就不能向上翻了

    curFileIndex = -1;
}

MediaFileManager::~MediaFileManager()
{
    delete xml;
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
