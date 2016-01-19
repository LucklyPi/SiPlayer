#ifndef SIPLAYER_H
#define SIPLAYER_H

#include <QWidget>
#include <QVideoWidget>
#include <QString>

#include "myplayer.h"
#include "mediafilemanager.h"

class SiPlayer : public QVideoWidget
{
    Q_OBJECT

public:
    explicit SiPlayer(QVideoWidget *parent = 0);
    ~SiPlayer();

public slots:
    void playNextFile();
    void playPrevFile();


private:
    MyPlayer player;                //播放器
    MediaFileManager fileManager;   //文件管理

protected:
    void closeEvent(QCloseEvent * event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

};

#endif // SIPLAYER_H
