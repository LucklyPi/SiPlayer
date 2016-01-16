#include "siplayer.h"

#include <QUrl>
#include <QDebug>
#include <QKeyEvent>
#include <QPalette>

SiPlayer::SiPlayer(QVideoWidget *parent)
    :QVideoWidget(parent)
{
    //设置窗口背景色为黑色
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);

    //设置播放器属性
    player.setVideoOutput(this);
    player.setPlayingFile("C:/Users/Public/Videos/Sample Videos/Wildlife.wmv");

    //信号连接
    connect(&player, SIGNAL(curFileFinish()),this,SLOT(playNextFile()));
    connect(&player,SIGNAL(playedTimeChange(QString,qint64)),&fileManager,SLOT(dealPlayedTimeChange(QString,qint64)));
}

SiPlayer::~SiPlayer()
{

}

void SiPlayer::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Right:
            player.forwardOneMinute();
            break;
        case Qt::Key_Left:
            player.backOneMinute();
            break;
        case Qt::Key_Up:
            playPrevFile();
            break;
        case Qt::Key_Down:
            playNextFile();
            break;
        case Qt::Key_Q:
            this->close();
            break;
        case Qt::Key_Return:
            if(player.state() == MyPlayer::PAUSE_STATE)
                player.play();
            else if(player.state() == MyPlayer::PLAYING_STATE)
                player.pause();
        default:
            QVideoWidget::keyPressEvent(event);
            break;
    }
}

void SiPlayer::playNextFile()
{
    QString fileName = fileManager.getNextFileName();
    qint64  playedTime = fileManager.getPlayedTime(fileName);
    if (fileName.isEmpty())
        player.play();
    else
        player.setPlayingFile(fileName, playedTime);
}

void SiPlayer::playPrevFile()
{
    QString fileName = fileManager.getPrevFileName();
    qint64  playedTime = fileManager.getPlayedTime(fileName);
    if (fileName.isEmpty())
        player.play();
    else
        player.setPlayingFile(fileName, playedTime);
}


