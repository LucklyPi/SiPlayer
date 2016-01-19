#include "mediafilemanager.h"


#include <QDebug>
#include <QDir>

MediaFileManager::MediaFileManager(QObject *parent) : QObject(parent)
{
    xml = new MyXML("F:/Media/filelist.xml");

    QStringList xmlFileList = xml->getFileList();
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
            element.fileClass = 0;
            element.lastPosition = 0;
            element.fileName = dirFileList.at(i);
            xml->addElement(element);
        }
    }

    fileList = xml->getFileList();
    saveTimerId = startTimer(60000);
    curFileIndex = -1;
}


MediaFileManager::~MediaFileManager()
{
    delete xml;
}


void MediaFileManager::timerEvent(QTimerEvent *)
{
    //每隔1分钟保存到文件一次
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

void MediaFileManager::save()
{
    xml->saveXMLtoFile();
}

void MediaFileManager::dealPlayedTimeChange(QString fileName, qint64 time)
{
    FileElement element;
    xml->getElement(fileName,&element);
    if(element.lastPosition < 0)
        return;
    element.lastPosition = time;
    element.fileName = fileName;
    xml->replaceElement(element);
}

void MediaFileManager::dealFileError(QString fileName)
{
    qDebug()<<"dealFileError fileName = " << fileName;
    FileElement element;
    xml->getElement(fileName,&element);
    element.lastPosition = -1;
    element.fileName = fileName;
    xml->replaceElement(element);
}


