#ifndef SAVEGAME_HH
#define SAVEGAME_HH

#include <QObject>
#include <QDebug>
#include <string>
#include "interfaces/iobjectmanager.h"
#include "interfaces/igameeventhandler.h"

class SaveGame : public QObject
{
    Q_OBJECT
public:
    SaveGame(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
             const std::shared_ptr<Course::iObjectManager>& objectmanager);

public slots:
    void saveCurrentGame(QString fileName);
};

#endif // SAVEGAME_HH
