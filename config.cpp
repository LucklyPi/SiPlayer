#include "config.h"

#include "QSettings"


Config::Config()
{

}

Config::~Config()
{
    QSettings *config = new QSettings("hahaya.ini", QSettings::IniFormat);
}

Config* Config::m_instance = 0;
