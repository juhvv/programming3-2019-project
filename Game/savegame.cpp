#include "savegame.hh"

SaveGame::SaveGame(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                   const std::shared_ptr<Course::iObjectManager>& objectmanager)
{

}

void SaveGame::saveCurrentGame(QString fileName)
{
    qDebug()<<fileName;
}


