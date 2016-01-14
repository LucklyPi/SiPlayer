#include "myplayer.h"

MyPlayer::MyPlayer(QObject *parent) : QObject(parent)
{
    curState = MyPlayer::STOP_STATE;
}

MyPlayer::~MyPlayer()
{

}

