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

    player.setVideoOutput(this);
    player.setPlayingFile("C:/Users/Public/Videos/Sample Videos/Wildlife.wmv");
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
            player.setPlayingFile("C:/Users/Public/Videos/Sample Videos/testPlayer1.mp4");
            break;
        case Qt::Key_Down:
            player.setPlayingFile("C:/Users/Public/Videos/Sample Videos/testPlayer2.mp4");
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
