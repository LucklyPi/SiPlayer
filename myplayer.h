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
    void pause();
    void stop();
    void setPlayingFile(const QString &fileName);
    void forwardOneMinute();
    void backOneMinute();
    QString curPlayFile();
    MyPlayer::State state();

    void setVideoOutput(QVideoWidget * output);

public slots:
    void setState(QMediaPlayer::State state);

signals:
    void curFileFinish();
    void playedTimeChange(qint64 time);

private:
    QMediaPlayer player;
    MyPlayer::State curState;
    QString curPlayingFileName;

};

#endif // MYPLAYER_H
