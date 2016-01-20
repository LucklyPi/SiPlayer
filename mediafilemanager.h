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

    void    save();
    QString getNextFileName();
    QString getPrevFileName();
    qint64  getPlayedTime(QString fileName);
    void    setFileClass(int fileclass);


public slots:
    void dealPlayedTimeChange(QString fileName, qint64 time);
    void dealFileError(QString fileName);

private:
    QStringList fileList;
    int curFileIndex;
    MyXML *xml;
    int saveTimerId;

protected:
    void timerEvent(QTimerEvent *) Q_DECL_OVERRIDE;


};

#endif // MEDIAFILEMANAGER_H
