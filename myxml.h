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

//查找方法还可以再做一些优化，记录上一次查到的结果，先于上一次的结果对比。

class MyXML
{
public:
    MyXML(QString fileNmae);
    ~MyXML();

    //文件操作接口
    void save();

    //内容操作接口
    void addElement(FileElement element);
    bool getElement(QString fileName, FileElement *element = 0);
    void removeElement(QString fileName);
    void replaceElement(FileElement element);
    QStringList getFileList(int fileCalss = 0);

private:
    void creatXML();
    void loadXML();
    QString saveFileName;
    QDomDocument doc;
};

#endif // MYXML_H
