#ifndef MYXML_H
#define MYXML_H

#include <QDomDocument>
#include <QString>
#include <QList>


class MyXML
{
public:
    MyXML();
    MyXML(const QString fileNmae);
    ~MyXML();


private:
    void creatXML();
    void loadXML();


    QString saveFileName;
    QDomDocument doc;


};

#endif // MYXML_H
