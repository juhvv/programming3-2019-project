#ifndef LOADGAME_HH
#define LOADGAME_HH

#include <QObject>
#include <QDebug>
#include <string>
#include "interfaces/iobjectmanager.h"
#include "interfaces/igameeventhandler.h"
#include "gameeventhandler.hh"
#include "objectmanager.hh"


#include "QDir"
#include "QTextStream"
#include "QFile"

class LoadGame : public QObject
{
    Q_OBJECT
public:
    LoadGame(std::shared_ptr<GameEventHandler> eventhandler,
             std::shared_ptr<ObjectManager> objectmanager);

public slots:
    void loadGame(QString fileName);

private:
    std::shared_ptr<GameEventHandler> eventhandler_;
    std::shared_ptr<ObjectManager> objectManager_;
};

#endif // LOADGAME_HH
