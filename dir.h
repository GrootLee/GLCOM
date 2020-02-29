
//保存配置文件
//designer:geootLee

#ifndef DIR_H
#define DIR_H
#include"serialunion.h"
#include <QObject>
#include <QSettings>


#define CONFIGFILE "config.ini"

class Dir : public QObject
{
    Q_OBJECT
public:
    static Dir *GetDirIns();
    Dir();

public:
    void saveParam();
    void loadParam();
};

#endif // DIR_H
