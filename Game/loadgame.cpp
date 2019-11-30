#include "loadgame.hh"

LoadGame::LoadGame(std::shared_ptr<GameEventHandler> eventhandler,
                   std::shared_ptr<ObjectManager> objectmanager):
    eventhandler_(eventhandler),
    objectManager_(objectmanager)
{

}

void LoadGame::loadGame(QString fileName)
{
    qDebug()<<"siknaali virraa latinkiin";
}
