#ifndef SIPLAYER_H
#define SIPLAYER_H

#include <QWidget>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QString>

class SiPlayer : public QVideoWidget
{
    Q_OBJECT

public:
    SiPlayer(const QString &playingFileName);
    ~SiPlayer();

public slots:
    void setPlayFile(const QString &fileNmae);
    void play();


private:
    QMediaPlayer player;        //播放器
    QString m_playingFileName;      //正在播放的文件

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

};

#endif // SIPLAYER_H
