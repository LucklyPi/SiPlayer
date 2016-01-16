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
    qint64  getPlayedTime(QString fileName);

public slots:
    void dealPlayedTimeChange(QString fileName, qint64 time);

private:

    //是否真的需要一个fileList,可不可以由xml中的doc代替
    QStringList fileList;
    int curFileIndex;
    MyXML *xml;
    int saveTimerId;

protected:
    void timerEvent(QTimerEvent *) Q_DECL_OVERRIDE;


};

#endif // MEDIAFILEMANAGER_H
