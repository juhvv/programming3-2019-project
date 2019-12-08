#include "savegame.hh"

SaveGame::SaveGame(std::shared_ptr<GameEventHandler> eventhandler,
                   std::shared_ptr<ObjectManager> objectmanager):
    eventhandler_(eventhandler),
    objectManager_(objectmanager)
{

}


void SaveGame::saveCurrentGame(QString fileName)
{
    QFile saveFileName(fileName);
    saveFileName.open(QIODevice::ReadWrite);

    std::vector<std::shared_ptr<Player>> playerVector = eventhandler_->getPlayerVector();
    QString turnNumber = QString::number(eventhandler_->getTurnNumber());
    std::shared_ptr<Player> currentPlayer = eventhandler_->getCurrentPlayer();

    QTextStream out(&saveFileName);

    //Save turn number with following syntax: "TURN", turn number
    out<<"TURN,"<<turnNumber<<endl;

    //Save player's resources with following syntax: "RESOURCES",player's name,resources
    for(auto player: playerVector){
        QString playername = QString::fromStdString(player->getName());
        out<<"RESOURCES,"<<playername;
        Course::ResourceMap playerresources = player->getResourceMap();

        for(auto resource: playerresources){
            out<<","<<resource.second;
        }
        out<<endl;
    }


    //Save name of current player on next row with following syntax: "CURRENTPLAYER",player's name
    QString currentPlayerName = QString::fromStdString(currentPlayer->getName());
    out<<"CURRENTPLAYER,"<<currentPlayerName<<endl;


    //Save tiles with following syntax: "TILE", tile type, Xcoordinate, Ycoordinate, is tile owned,owner's name,
    //building type, type of first unit, type of second unit...
    std::vector<std::shared_ptr<Course::TileBase>> tiles = objectManager_->getAllTiles();
    for(auto tile: tiles){

        QString tileType = QString::fromStdString(tile->getType());
        std::vector<std::shared_ptr<Course::BuildingBase>> buildings = tile->getBuildings();
        std::vector<std::shared_ptr<Course::WorkerBase>> units = tile->getWorkers();
        std::shared_ptr<Player> tileOwner = std::dynamic_pointer_cast<Player>(tile->getOwner());

        QString ownerName = "";
        QString tileOwned = "NO";
        QString buildingType = "";

        int xCoord = tile->getCoordinate().x();
        int yCoord = tile->getCoordinate().y();

        if(units.size()>0){           //Change owner name of units if there are units
            ownerName = QString::fromStdString(units[0]->getOwner()->getName());
        }
                                      //Tile could have units without the tile being owned.
        if(tile->getOwner()!=NULL){   //tileOwned tells if tile need to be claimed when game is loaded
            ownerName = QString::fromStdString(tile->getOwner()->getName());
            tileOwned = "YES";
        }
        if(buildings.size()>0){       //Tile can only have one building
            buildingType = QString::fromStdString(buildings[0]->getType());
        }

        out<<"TILE,"<<tileType<<","<<xCoord<<","<<yCoord<<","<<tileOwned<<","<<ownerName<<","<<buildingType<<",";

        for(auto unit: units){      //Tile can have multiple units of different types
            QString unitType = QString::fromStdString(unit->getType());
            out<<unitType<<",";
        }
        out<<endl;
    }
    saveFileName.flush();
    saveFileName.close();
}
