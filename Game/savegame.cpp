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

    QTextStream out(&failu);

    //Save player's resources on first rows with following syntax: "RESOURCES",player's name,resources
    for(auto player: playerVector){
        QString playername = QString::fromStdString(player->getName());
        out<<"RESOURCES,"<<playername;

        Course::ResourceMap playerresources = player->getResourceMap();
        for(auto resource: playerresources){
            out<<","<<resource.second;
            failu.flush();
        }
        out<<endl;
    }


    //Save name of current player on next row with followinf syntax: "CURRENTPLAYER",player's name
    QString currentPlayerName = QString::fromStdString(currentPlayer->getName());
    out<<"CURRENTPLAYER,"<<currentPlayerName<<endl;
    failu.flush();


    //Save tiles with following syntax: "TILE", tile type, Xcoordinate, Ycoordinate, owner's name, building type, unit type
    std::vector<std::shared_ptr<Course::TileBase>> tiles = objectManager_->getAllTiles();
    for(auto tile: tiles){
        QString tileType = QString::fromStdString(tile->getType());

        std::vector<std::shared_ptr<Course::BuildingBase>> buildings = tile->getBuildings();
        std::vector<std::shared_ptr<Course::WorkerBase>> workers = tile->getWorkers();
        QString ownerName = "";
        QString buildingType = "";
        QString workerType = "";

        int xCoord = tile->getCoordinate().x();
        int yCoord = tile->getCoordinate().y();

        if(tile->getOwner()!=NULL){
            ownerName = QString::fromStdString(tile->getOwner()->getName());
        }
        if(buildings.size()>0){
            buildingType = QString::fromStdString(buildings[0]->getType());
        }
        if(workers.size()>0){
            workerType = QString::fromStdString(workers[0]->getType());
        }

        out<<"TILE,"<<tileType<<","<<xCoord<<","<<yCoord<<","<<ownerName<<","<<buildingType<<","<<workerType<<","<<endl;

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
