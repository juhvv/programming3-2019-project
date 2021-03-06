#include "loadgame.hh"

LoadGame::LoadGame(std::shared_ptr<GameEventHandler>& eventhandler,
                   std::shared_ptr<ObjectManager>& objectmanager):
    eventhandler_(eventhandler),
    objectManager_(objectmanager)
{

}



std::vector<std::string> LoadGame::split(const std::string &stringToBeSplitted)
{
    char delim = ',';
    std::vector<std::string> result;
    std::stringstream ss (stringToBeSplitted);
    std::string item;

    while (std::getline (ss, item, delim)) {
        result.push_back (item);
    }
    return result;
}

void LoadGame::addUnitsAndBuildings(QString fileName)
{
    //Load the file
    QFile loadFile(fileName);
    loadFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&loadFile);
    eventhandler_->nextTurnButtonMode(true);

    while (!in.atEnd()){        //Iterate through the file
        QString line = in.readLine();
        std::string stringLine = line.toUtf8().constData();
        std::vector<std::string> stringVector = split(stringLine);

        if(stringVector[0]=="TILE"){        //We only care about "TILE" lines of save file in this method
            std::string buildingName = stringVector[6];
            std::string ownerName = stringVector[5];
            std::string isTileOwned = stringVector[4];
            unsigned int xCoord = atoi(stringVector[2].c_str());
            unsigned int yCoord = atoi(stringVector[3].c_str());
            Course::Coordinate tileCoord = Course::Coordinate(xCoord, yCoord);
            std::shared_ptr<GraphicsTileBase> tile = objectManager_->getGTile(tileCoord);
            std::shared_ptr<Player> ownerPointer = eventhandler_->getPlayerFromName(ownerName);

            //Claim the tile. This "if" because ownerName can be name of the player
            //even when the tile is not owned, then ownerName means owner of units on the tile
            if(isTileOwned=="YES"){
                eventhandler_->claimTile(tile.get(), ownerPointer);
            }

            if(buildingName!=""){    //Creates and adds buildings to eventhandler

                if(buildingName=="Base"){
                    eventhandler_->addBuilding<Base>(tile, ownerPointer, true);
                }
                if(buildingName=="Gold mine"){
                    eventhandler_->addBuilding<GoldMine>(tile, ownerPointer, true);
                }
                if(buildingName=="Sawmill"){
                    eventhandler_->addBuilding<SawMill>(tile, ownerPointer, true);
                }
                if(buildingName=="Outpost"){
                    eventhandler_->addBuilding<Outpost>(tile, ownerPointer, true);
                }
                if(buildingName=="Farm"){
                    eventhandler_->addBuilding<Farm>(tile, ownerPointer, true);
                }
            }

            for(long unsigned int i=6; i<stringVector.size(); i++){   //Creates and adds units to eventhandler
                std::string unitName = stringVector[i];
                if(unitName=="Builder"){
                    eventhandler_->addUnit<Builder>(tile, ownerPointer, true);
                }
                if(unitName=="Scout"){
                    eventhandler_->addUnit<Scout>(tile, ownerPointer, true);
                }
                if(unitName=="Worker"){
                    eventhandler_->addUnit<Worker>(tile, ownerPointer, true);
                }
            }
        }
    }
    emit updateVisibleLabels();
    std::string msg = "<<<GAME LOADED>>>";
    emit sendMsg(msg);
}


void LoadGame::loadGame(QString fileName)
{
    //Add constructors of tiles to multimap, because in the save file they are referred with tile names
    addTileConstructor<MountainTileItem>("Mountain tile");
    addTileConstructor<ForestTileItem>("Forest Tile");
    addTileConstructor<GrassTileItem>("Grass tile");
    addTileConstructor<WaterTileItem>("Lake tile");
    addTileConstructor<SwampTileItem>("Swamp tile");

    eventhandler_->resetData();     //Delete data of currently loaded game: tiles, players...

    QString loadFileName = fileName;
    std::vector<std::shared_ptr<Course::TileBase>> tileVector;

    QFile loadFile(loadFileName);
    loadFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&loadFile);

    int index = 0;

    while (!in.atEnd()) {       //Iterate through the file
        QString line = in.readLine();
        std::string stringLine = line.toUtf8().constData();
        std::vector<std::string> stringVector = split(stringLine);

        if(stringVector[0]=="TURN"){         //Load current turn number
            std::string stringTurn = stringVector[1];
            unsigned int turn=atoi(stringTurn.c_str());
            eventhandler_->setTurnNumber(turn);
        }

        if(stringVector[0]=="RESOURCES"){   //Load and make player objects, their names and resources
            std::string playerName = stringVector[1];
            Course::ResourceMap playerResources;

            int moneyAmount = atoi(stringVector[2].c_str());
            int foodAmount = atoi(stringVector[3].c_str());
            int woodAmount = atoi(stringVector[4].c_str());
            playerResources.insert(std::pair<Course::BasicResource,int>(Course::MONEY, moneyAmount));
            playerResources.insert(std::pair<Course::BasicResource,int>(Course::FOOD, foodAmount));
            playerResources.insert(std::pair<Course::BasicResource,int>(Course::WOOD, woodAmount));

            std::shared_ptr<Player> playerPtr = std::make_shared<Player>(playerName, playerResources);

            playerPtr->setMarker(index);    //This sets player's marker, which is the coloured box around player's owned tiles

            playerVector_.push_back(playerPtr);
            index++;    //Increase index value for setMarker selection: if it would be the same, the box would be same colour for both players
        }

        eventhandler_->addPlayerVector(playerVector_);      //Add generated player vector to eventhandler

        //Set current player to eventhandler
        if(stringVector[0]=="CURRENTPLAYER"){
            eventhandler_->addPlayerVector(playerVector_);
            eventhandler_->setCurrentPlayer(stringVector[1]);
        }

        //Add tile and push it to tilevector
        if(stringVector[0]=="TILE"){

            std::string tileType = stringVector[1];
            unsigned int xCoord = atoi(stringVector[2].c_str());
            unsigned int yCoord = atoi(stringVector[3].c_str());

            TileConstructorPointer constructorPointer;
            for(auto it: tileConctructorNames_) {
                if(it.first==tileType){
                    constructorPointer = it.second;
                }
            }
            //Create and push tile to tileVector
            tileVector.push_back(constructorPointer(Course::Coordinate(xCoord, yCoord), eventhandler_, objectManager_));
        }
    }
    objectManager_->addTiles(tileVector);  //Add generated tiles to eventhandler
    addUnitsAndBuildings(fileName);        //Adds units, buildings and claim tiles

}
