#ifndef MYPLAYER_H
#define MYPLAYER_H

#include <QObject>
#include <QString>
#include <QMediaPlayer>

class MyPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MyPlayer(QObject *parent = 0);
    ~MyPlayer();

    enum State
    {
        PLAYING_STATE,
        PAUSE_STATE,
        STOP_STATE,
    };

    void play();
    void replay();
    void pause();
    void stop();
    void forwardOneMinute();
    void backOneMinute();
    QString curPlayFile();
    MyPlayer::State state();

    void setVideoOutput(QVideoWidget * output);

public slots:
    void setState(QMediaPlayer::State state);
    void setPlayedTime(qint64 time);
    void dealError(QMediaPlayer::Error error);

    void setPlayingFile(const QString &fileName, qint64 playedTime = 0);

signals:
    void curFileFinish();
    void playedTimeChange(QString fileName, qint64 time);
    void playFileError(QString fileName);

private:
    QMediaPlayer player;
    MyPlayer::State curState;
    QString curPlayingFileName;

};

#endif // MYPLAYER_H
