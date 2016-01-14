#include "myplayer.h"

#include <Qurl>

MyPlayer::MyPlayer(QObject *parent) : QObject(parent)
{
    curState = MyPlayer::STOP_STATE;
    connect(&player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(setState(QMediaPlayer::State)));
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

void MyPlayer::setPlayingFile(const QString &fileName)
{
    if(fileName == curPlayingFileName)
        return;
    curPlayingFileName = fileName;
    player.setMedia(QUrl::fromLocalFile(fileName));
    player.play();
}

void MyPlayer::forwardOneMinute()
{
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
        emit curFileFinish();
        break;
    default:
        break;
    }
}


