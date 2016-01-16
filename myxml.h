#ifndef MYXML_H
#define MYXML_H

#include <QDomDocument>
#include <QString>
#include <QList>
#include <QStringList>


struct FileElement
{
    QString fileName;
    long    lastPosition;
    long    lastPlayTime;
};


class MyXML
{
public:
    MyXML();
    MyXML(QString fileNmae);
    ~MyXML();

    void saveXMLtoFile();
    void addElement(FileElement element);
    bool getElement(QString fileName, FileElement *element = 0);
    void removeElement(QString fileName);
    void replaceElement(FileElement element);
    void getFileList(QStringList *fileList);

private:
    void creatXML();
    void loadXML();
    QString saveFileName;
    QDomDocument doc;
};

#endif // MYXML_H
