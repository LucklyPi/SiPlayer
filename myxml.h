#ifndef MYXML_H
#define MYXML_H

#include <QDomDocument>
#include <QString>
#include <QList>
#include <QStringList>


struct FileElement
{
    QString fileName;       //文件名
    qint64  lastPosition;   //上一次播放的位置
    int     fileClass;      //文件的类别
};


class MyXML
{
public:
    MyXML(QString fileNmae);
    ~MyXML();

    void saveXMLtoFile();
    void addElement(FileElement element);
    bool getElement(QString fileName, FileElement *element = 0);
    void removeElement(QString fileName);
    void replaceElement(FileElement element);
    QStringList getFileList();

private:
    void creatXML();
    void loadXML();
    QString saveFileName;
    QDomDocument doc;
};

#endif // MYXML_H
