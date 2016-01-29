#ifndef CONFIG_H
#define CONFIG_H

#include <QDebug>

class Config
{
public:
    static Config* Instance()
    {
        if (m_instance)
            m_instance = new Config();
        return m_instance;
    }

private:
    Config();
    ~Config();

    static Config* m_instance;


};

#endif // CONFIG_H
