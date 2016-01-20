#include "myplayer.h"
#include <Qurl>

MyPlayer::MyPlayer(QObject *parent) : QObject(parent)
{
    curState = MyPlayer::STOP_STATE;
    connect(&player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(setState(QMediaPlayer::State)));
    connect(&player,SIGNAL(positionChanged(qint64)),this,SLOT(setPlayedTime(qint64)));
    connect(&player,SIGNAL(error(QMediaPlayer::Error)),this,SLOT(dealError(QMediaPlayer::Error)));
}

MyPlayer::~MyPlayer()
{

}

void MyPlayer::play()
{
    player.play();
}

void MyPlayer::pause()
{
    player.pause();
}

void MyPlayer::stop()
{
    player.stop();
}

void MyPlayer::replay()
{
    player.setPosition(0);
    player.play();
}

void MyPlayer::setPlayingFile(const QString &fileName, qint64 playedTime)
{
    if(fileName == curPlayingFileName)
        return;
    curPlayingFileName = fileName;
    player.setMedia(QUrl::fromLocalFile(fileName));
    player.setPosition(playedTime);
    player.play();
}

void MyPlayer::forwardOneMinute()
{
    //最后一秒不必快进了，这样可以防止重发curFileFinish消息
    if(player.position()+1000 >= player.duration())
        return;
    //剩余时间不足一分钟，直接停止播放，并发送curFileFinish消息
    if(player.position()+60000 >= player.duration())
    {
        player.stop();
        emit playedTimeChange(curPlayingFileName, 0);
        emit curFileFinish();
    }
    else
        player.setPosition(player.position()+60000);
}

void MyPlayer::backOneMinute()
{
    player.setPosition(player.position()-60000);
}

QString MyPlayer::curPlayFile()
{
    return curPlayingFileName;
}

MyPlayer::State MyPlayer::state()
{
    return curState;
}

void MyPlayer::setVideoOutput(QVideoWidget * output)
{
    player.setVideoOutput(output);
}

void MyPlayer::setState(QMediaPlayer::State state)
{
    switch(state)
    {
    case QMediaPlayer::PlayingState:
        curState = PLAYING_STATE;
        break;
    case QMediaPlayer::PausedState:
        curState = PAUSE_STATE;
        break;
    case QMediaPlayer::StoppedState:
        curState = STOP_STATE;
        if (player.position() >= player.duration()) {
            emit playedTimeChange(curPlayingFileName, 0);
            emit curFileFinish();
        }
        break;
    default:
        break;
    }
}

void MyPlayer::setPlayedTime(qint64 time)
{
    emit playedTimeChange(curPlayingFileName, time);
}

void MyPlayer::dealError(QMediaPlayer::Error error)
{
    qDebug()<<"error = "<<error;
    if(error != QMediaPlayer::NoError)
        emit playFileError(curPlayingFileName);
}


