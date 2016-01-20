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
    connect(&player,SIGNAL(playFileError(QString)),&fileManager,SLOT(dealFileError(QString)));
    connect(&fileManager,SIGNAL(changePlayingFile(QString,qint64)),&player,SLOT(setPlayingFile(QString,qint64)));
}

SiPlayer::~SiPlayer()
{

}

void SiPlayer::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"event->key() = " <<hex<<event->key();

    switch(event->key())
    {
        case Qt::Key_Right:
            player.forwardOneMinute();
            break;
        case Qt::Key_Left:
            player.backOneMinute();
            break;
        case Qt::Key_Escape:
            player.replay();
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
            break;
        case Qt::Key_0:
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9:
            fileManager.setFileClass(event->key() - 0x30);
            break;
        default:
            QVideoWidget::keyPressEvent(event);
            break;
    }
}

void SiPlayer::playNextFile()
{
    QString fileName;
    qint64  playedTime = 0;
    do {
        fileName = fileManager.getNextFileName();
        playedTime = fileManager.getPlayedTime(fileName);
    }while(playedTime < 0);
    if (fileName.isEmpty())
        player.play();
    else
        player.setPlayingFile(fileName, playedTime);
}

void SiPlayer::playPrevFile()
{
    QString fileName;
    qint64  playedTime = 0;
    do {
        fileName = fileManager.getPrevFileName();
        playedTime = fileManager.getPlayedTime(fileName);
    }while(playedTime < 0);
    if (fileName.isEmpty())
        player.play();
    else
        player.setPlayingFile(fileName, playedTime);
}

void SiPlayer::closeEvent(QCloseEvent *event)
{
    fileManager.save();
    QVideoWidget::closeEvent(event);
}


