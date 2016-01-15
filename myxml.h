#ifndef MYXML_H
#define MYXML_H

#include <QDomDocument>
#include <QString>
#include <QList>
#include <QStringList>


struct FileElement
{
    QString fileName;
    qint64    lastPosition;
    qint64    lastPlayTime;
};


class MyXML
{
public:
    MyXML();
    MyXML(QString fileNmae);
    ~MyXML();

    void saveXMLtoFile();
    void addElement(FileElement element);
    FileElement getElement(QString fileName);
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
