#ifndef MEDIAFILEMANAGER_H
#define MEDIAFILEMANAGER_H

#include <QObject>
#include <QList>

class MediaFileManager : public QObject
{
    Q_OBJECT
public:
    explicit MediaFileManager(QObject *parent = 0);
    ~MediaFileManager();

    QString getNextFileName();
    QString getPrevFileName();

private:

    QList<QString> fileList;
    int curFileIndex;


};

#endif // MEDIAFILEMANAGER_H
