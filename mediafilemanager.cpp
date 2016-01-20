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

    QList<FileElement> dirFileList = getAllFileinMediaDir();
    for (int i = 0; i < dirFileList.size(); ++i) {
        if (!xml->getElement(dirFileList.at(i).fileName)) {
            xml->addElement(dirFileList.at(i));
        }
    }

    fileList = xml->getFileList();
    saveTimerId = startTimer(60000);

    lastFileName = xml->getLastFile();
    curFileIndex = fileList.indexOf(lastFileName);
    if(curFileIndex < 0)
        lastFileName = "";
    curFileClass =  0;
    qDebug()<<"lastFileName = "<<lastFileName;
}


MediaFileManager::~MediaFileManager()
{
    delete xml;
}


void MediaFileManager::timerEvent(QTimerEvent *)
{
    //每隔1分钟保存到文件一次
    xml->save();
}

void MediaFileManager::save()
{
    xml->save();
}

QString MediaFileManager::getNextFileName()
{
    if(!lastFileName.isEmpty()) {
        lastFileName = "";
        return lastFileName;
    }
    if(fileList.size() == 0)
        return QString();
    if(++curFileIndex >= fileList.size())
        curFileIndex = 0;

    return fileList.at(curFileIndex);
}

QString MediaFileManager::getPrevFileName()
{
    if(!lastFileName.isEmpty()) {
        lastFileName = "";
        return lastFileName;
    }
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

void MediaFileManager::setFileClass(int fileClass)
{
    if(curFileClass == fileClass)
        return;
    QStringList newList = xml->getFileList(fileClass);
    if(newList.isEmpty())
        return;
    if(curFileIndex >= 0 && curFileIndex < fileList.size()) {
        int newIndex = newList.indexOf(fileList.at(curFileIndex));
        if(newIndex < 0) {
            emit changePlayingFile(newList.at(0),getPlayedTime(newList.at(0)));
            curFileIndex = 0;
        } else {
            curFileIndex = newIndex;
        }
    } else {
        curFileIndex = -1;
    }
    curFileClass = fileClass;
    fileList = newList;
}

/**
 * @brief MediaFileManager::dealPlayedTimeChange 处理播放器播放的时间改变的消息
 * @param fileName  当前播放的文件
 * @param time      播放的时间
 */
void MediaFileManager::dealPlayedTimeChange(QString fileName, qint64 time)
{
    FileElement element;
    xml->getElement(fileName,&element);
    if(element.lastPosition < 0)
        return;
    element.lastPosition = time;
    element.fileName = fileName;
    if(xml->replaceElement(element))
        xml->setLastFile(element);
}

/**
 * @brief MediaFileManager::dealFileError 处理播放器播放文件出错的消息
 * @param fileName  出错的文件名
 */
void MediaFileManager::dealFileError(QString fileName)
{
    FileElement element;
    xml->getElement(fileName,&element);
    element.lastPosition = -1;
    element.fileName = fileName;
    xml->replaceElement(element);
}

QStringList MediaFileManager::getAllFileinDir(QString dir)
{
    QStringList nameFilters;
    nameFilters<<"*.mp4";
    nameFilters<<"*.flv";
    QDir qdir(dir);
    QStringList allFile;

    allFile = qdir.entryList(nameFilters, QDir::Files, QDir::Name);
    for (int i = 0; i < allFile.size(); ++i) {
        allFile.replace(i,dir + "/" + allFile.at(i));
    }

    QStringList dirList = qdir.entryList(QDir::Dirs, QDir::Name);
    for(int i = 0; i < dirList.size(); ++i) {
        if(dirList.at(i) == "." || dirList.at(i) == "..")
            continue;
        allFile.append(getAllFileinDir(dir + "/" + dirList.at(i)));
    }

    return allFile;
}


QList<FileElement> MediaFileManager::getAllFileinMediaDir()
{
    QStringList nameFilters;
    nameFilters<<"*.mp4";
    nameFilters<<"*.flv";
    QDir dir("F:/Media/");
    QList<FileElement> allFileinDir;
    FileElement element;

    QStringList dirFileList = dir.entryList(nameFilters, QDir::Files, QDir::Name);
    for (int i = 0; i < dirFileList.size(); ++i) {
        element.fileName = "F:/Media/"+dirFileList.at(i);
        element.lastPosition = 0;
        element.fileClass = 0;
        allFileinDir.append(element);
    }

    QStringList dirList = dir.entryList(QDir::Dirs, QDir::Name);
    for (int i = 0; i < dirList.size(); ++i) {
        if(dirList.at(i) == "." || dirList.at(i) == "..")
            continue;
        QStringList allFileinClass = getAllFileinDir("F:/Media/" + dirList.at(i));
        for (int j = 0; j < allFileinClass.size(); ++j) {
            element.fileName = allFileinClass.at(j);
            element.lastPosition = 0;
            element.fileClass = dirList.at(i).toInt();
            allFileinDir.append(element);
        }
    }
    return allFileinDir;
}


