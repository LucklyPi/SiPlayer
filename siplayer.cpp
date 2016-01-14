#include "siplayer.h"

#include <QUrl>
#include <QDebug>
#include <QKeyEvent>
#include <QPalette>

SiPlayer::SiPlayer(const QString &playingFileName)
{
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);

    m_playingFileName = playingFileName;
    player.setMedia(QUrl::fromLocalFile(playingFileName));
    player.setVideoOutput(this);
    player.play();
}

SiPlayer::~SiPlayer()
{

}

void SiPlayer::setPlayFile(const QString &fileNmae)
{
    if(fileNmae == m_playingFileName)
        return;
    m_playingFileName = fileNmae;
    player.setMedia(QUrl::fromLocalFile(fileNmae));
    player.play();
}

void SiPlayer::play()
{
    player.play();
}

void SiPlayer::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"event->key()"<<hex<<event->key();
    switch(event->key())
    {
        case Qt::Key_Right:
            player.setPosition(player.position()+60000);
            break;
        case Qt::Key_Left:
            player.setPosition(player.position()-60000);
            break;
        case Qt::Key_Up:
            setPlayFile("C:/Users/Public/Videos/Sample Videos/Wildlife.wmv");
            break;
        case Qt::Key_Down:
            setPlayFile("F:/Media/11.mp4");
            break;
        case Qt::Key_Q:
            this->close();
            break;
        case Qt::Key_Return:

            if(player.state() == QMediaPlayer::PausedState)
                player.play();
            else if(player.state() == QMediaPlayer::PlayingState)
                player.pause();
        default:
            QVideoWidget::keyPressEvent(event);
            break;
    }
}
