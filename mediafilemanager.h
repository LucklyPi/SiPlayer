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

signals:
    /**
     * @brief changePlayingFile 正在播放的文件需要改变
     * @param fileName          变更后的播放文件
     * @param time              开始播放的时间
     */
    void changePlayingFile(QString fileName, qint64 time);

private:
    QList<FileElement> getAllFileinMediaDir();
    QStringList getAllFileinDir(QString dir);

    QStringList fileList;
    QString lastFileName;
    int curFileIndex;
    int curFileClass;
    MyXML *xml;
    int saveTimerId;

protected:
    void timerEvent(QTimerEvent *) Q_DECL_OVERRIDE;


};

#endif // MEDIAFILEMANAGER_H
