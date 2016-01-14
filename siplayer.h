#ifndef SIPLAYER_H
#define SIPLAYER_H

#include <QWidget>
#include <QVideoWidget>
#include <QString>

#include "myplayer.h"

class SiPlayer : public QVideoWidget
{
    Q_OBJECT

public:
    explicit SiPlayer(QVideoWidget *parent = 0);
    ~SiPlayer();


private:
    MyPlayer player;                //播放器

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

};

#endif // SIPLAYER_H
