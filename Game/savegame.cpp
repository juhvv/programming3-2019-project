#include "savegame.hh"

SaveGame::SaveGame(std::shared_ptr<GameEventHandler> eventhandler,
                   std::shared_ptr<ObjectManager> objectmanager):
    eventhandler_(eventhandler),
    objectManager_(objectmanager)
{

}


void SaveGame::saveCurrentGame(QString fileName)
{
    qDebug()<<fileName;
    QFile failu(fileName);
    failu.open(QIODevice::ReadWrite);
    qDebug()<<QDir::currentPath();

    std::vector<std::shared_ptr<Player>> playerVector = eventhandler_->getPlayerVector();
    std::shared_ptr<Player> currentPlayer = eventhandler_->getCurrentPlayer();

    //Save playernames in the first row, and current player on second
    QString player1 = QString::fromStdString(playerVector[0]->getName());
    QString player2 = QString::fromStdString(playerVector[1]->getName());
    QString currentPlayerName = QString::fromStdString(currentPlayer->getName());
    QTextStream out(&failu);
    out<<"PLAYERNAMES,"<<player1<<","<<player2<<endl;
    out<<"CURRENTPLAYER,"<<currentPlayerName<<endl;
    failu.flush();

    //Save player's resources on the third and fourth row with following syntax:
    for(auto player: playerVector){
        QString playername = QString::fromStdString(player->getName());
        out<<"RESOURCES,"<<playername;

        Course::ResourceMap playerresources = player->getResourceMap();
        for(auto resource: playerresources){
            out<<","<<resource.first<<","<<resource.second;
            failu.flush();
        }
        out<<endl;
    }


    //Save tiles with following syntax: "TILE", tile type, owner's name, building type, unit type
    std::vector<std::shared_ptr<Course::TileBase>> tiles = objectManager_->getAllTiles();
    for(auto tile: tiles){
        QString tileType = QString::fromStdString(tile->getType());

        std::vector<std::shared_ptr<Course::BuildingBase>> buildings = tile->getBuildings();
        std::vector<std::shared_ptr<Course::WorkerBase>> workers = tile->getWorkers();
        QString ownerName = "";
        QString buildingType = "";
        QString workerType = "";

        if(tile->getOwner()!=NULL){
            ownerName = QString::fromStdString(tile->getOwner()->getName());
        }
        if(buildings.size()>0){
            buildingType = QString::fromStdString(buildings[0]->getType());
            qDebug()<<buildingType<<"rakennus";
        }
        if(workers.size()>0){
            workerType = QString::fromStdString(workers[0]->getType());
        }

        out<<"TILE,"<<tileType<<","<<ownerName<<","<<buildingType<<","<<workerType<<endl;

    }



    failu.flush();
    failu.close();



    /*
    if(failu.isOpen()){
        qDebug()<<"ONAUKI!!" << fileName;
        QTextStream out(&failu);
        QString ekarivi = "eka rivi!";
        QString tokarivi = "toka rivi!";
        QString kolmes = "hmm...";
        out << ekarivi <<endl;
        failu.flush();
        out << tokarivi<<endl;
        out << kolmes<<endl;
        failu.flush();
        failu.close();
    }
    */


}
