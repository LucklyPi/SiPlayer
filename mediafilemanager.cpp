#include "mediafilemanager.h"


#include <QDebug>
#include <QDir>

MediaFileManager::MediaFileManager(QObject *parent) : QObject(parent)
{
    xml = new MyXML("F:/Media/filelist.xml");

    QStringList xmlFileList;
    xml->getFileList(&xmlFileList);
    for (int i = 0; i < xmlFileList.size(); ++i) {
        QFileInfo checkFile(xmlFileList.at(i));
        if (!checkFile.exists() || !checkFile.isFile()) {
            xml->removeElement(xmlFileList.at(i));
        }
    }

    QDir dir("F:/Media");
    QStringList nameFilters;
    nameFilters<<"*.mp4";
    QStringList dirFileList = dir.entryList(nameFilters, QDir::Files, QDir::Name);
    for (int i = 0; i < dirFileList.size(); ++i) {
        dirFileList.replace(i,"F:/Media/"+dirFileList.at(i));
        if (!xml->getElement(dirFileList.at(i))) {
            FileElement element;
            element.lastPlayTime = 0;
            element.lastPosition = 0;
            element.fileName = dirFileList.at(i);
            xml->addElement(element);
        }
    }

    xml->getFileList(&fileList);
    xml->saveXMLtoFile();
    saveTimerId = startTimer(30000);
    curFileIndex = -1;
}


MediaFileManager::~MediaFileManager()
{
    delete xml;
}


void MediaFileManager::timerEvent(QTimerEvent *)
{
    xml->saveXMLtoFile();
}

QString MediaFileManager::getNextFileName()
{
    if(fileList.size() == 0)
        return QString();
    if(++curFileIndex >= fileList.size())
        curFileIndex = 0;

    return fileList.at(curFileIndex);
}

QString MediaFileManager::getPrevFileName()
{
    if(fileList.size() == 0)
        return QString();
    if(--curFileIndex < 0)
        curFileIndex = fileList.size()-1;
    return fileList.at(curFileIndex);
}

qint64 MediaFileManager::getPlayedTime(QString fileName)
{
    FileElement element;
    if(xml->getElement(fileName,&element))
        return element.lastPosition;
    else
        return 0;
}

void MediaFileManager::dealPlayedTimeChange(QString fileName, qint64 time)
{
    FileElement element;
    element.lastPlayTime = 0;
    element.lastPosition = time;
    element.fileName = fileName;
    xml->replaceElement(element);

    if(time == 0)
        xml->saveXMLtoFile();
}

