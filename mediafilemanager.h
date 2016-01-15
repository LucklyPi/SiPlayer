#ifndef MEDIAFILEMANAGER_H
#define MEDIAFILEMANAGER_H

#include <QObject>
#include <QList>
#include <QStringList>

#include "myxml.h"

class MediaFileManager : public QObject
{
    Q_OBJECT
public:
    explicit MediaFileManager(QObject *parent = 0);
    ~MediaFileManager();

    QString getNextFileName();
    QString getPrevFileName();

private:

    QStringList fileList;
    int curFileIndex;
    MyXML *xml;


};

#endif // MEDIAFILEMANAGER_H
