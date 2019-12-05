#ifndef SAVEGAME_HH
#define SAVEGAME_HH

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


class SaveGame : public QObject
{
    Q_OBJECT
public:
    SaveGame(std::shared_ptr<GameEventHandler> eventhandler,
             std::shared_ptr<ObjectManager> objectmanager);

public slots:
    /**
      * @brief saves current game in a .txt file
      * @param fileName path and filename to .txt file where game will be saved
      */
    void saveCurrentGame(QString fileName);

private:
    std::shared_ptr<GameEventHandler> eventhandler_;
    std::shared_ptr<ObjectManager> objectManager_;
};

#endif // SAVEGAME_HH
