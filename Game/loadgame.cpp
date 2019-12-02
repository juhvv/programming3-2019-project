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

    //QString testFileName = "/home/vapola/ohjelmointi3/rojekti/sami-seka-juho/Game/tallennukset/uusukko7.txt";
    QFile loadFile(fileName);
    loadFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&loadFile);



    while (!in.atEnd()){
        QString line = in.readLine();
        std::string stringLine = line.toUtf8().constData();
        std::vector<std::string> stringVector = split(stringLine);
        if(stringVector[0]=="TILE"){
            std::string buildingName = stringVector[5];
            std::string ownerName = stringVector[4];

            std::vector<std::string> unitNameVct;

            if(ownerName!=""){

                for(int i=6; i<stringVector.size(); i++){
                    unitNameVct.push_back(stringVector[i]);
                }


                unsigned int xCoord = atoi(stringVector[2].c_str());
                unsigned int yCoord = atoi(stringVector[3].c_str());
                Course::Coordinate tileCoord = Course::Coordinate(xCoord, yCoord);
                std::shared_ptr<GraphicsTileBase> tile = objectManager_->getGTile(tileCoord);
                std::shared_ptr<Player> ownerPointer = eventhandler_->getPlayerFromName(ownerName);
                eventhandler_->claimTile(tile.get(), ownerPointer);


                if(buildingName!=""){    //Add buildings

                    if(buildingName=="Base"){
                        eventhandler_->addBuilding<Base>(tile, ownerPointer);
                    }
                    if(buildingName=="Gold mine"){
                        eventhandler_->addBuilding<GoldMine>(tile, ownerPointer);
                    }
                    if(buildingName=="Sawmill"){
                        eventhandler_->addBuilding<SawMill>(tile, ownerPointer);
                    }
                    if(buildingName=="Outpost"){
                        eventhandler_->addBuilding<Outpost>(tile, ownerPointer);
                    }
                    if(buildingName=="Farm"){
                        eventhandler_->addBuilding<Farm>(tile, ownerPointer);
                    }

                }
                for(int i=6; i<stringVector.size(); i++){
                    std::string unitName = stringVector[i];
                    if(unitName=="Builder"){
                        eventhandler_->addUnit<Builder>(tile, ownerPointer);
                    }
                    if(unitName=="Scout"){
                        eventhandler_->addUnit<Scout>(tile, ownerPointer);
                    }
                    if(unitName=="Worker"){
                        eventhandler_->addUnit<Worker>(tile, ownerPointer);
                    }

                }
            }
        }
    }
}


void LoadGame::loadGame(QString fileName)
{
    addTileConstructor<MountainTileItem>("Mountain tile");
    addTileConstructor<ForestTileItem>("Forest Tile");
    addTileConstructor<GrassTileItem>("Grass tile");
    addTileConstructor<WaterTileItem>("Lake tile");

    eventhandler_->resetData();

    QString loadFileName = fileName;
    //QString loadFileName = "/home/vapola/ohjelmointi3/rojekti/sami-seka-juho/Game/tallennukset/uusukko7.txt";

    std::vector<std::shared_ptr<Course::TileBase>> tileVector;

    QFile loadFile(loadFileName);
    loadFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&loadFile);

    int index = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        std::string stringLine = line.toUtf8().constData();
        std::vector<std::string> stringVector = split(stringLine);

        if(stringVector[0]=="RESOURCES"){
            std::string playerName = stringVector[1];
            Course::ResourceMap playerResources;

            int moneyAmount = atoi(stringVector[3].c_str());
            int foodAmount = atoi(stringVector[4].c_str());
            int woodAmount = atoi(stringVector[5].c_str());
            int stoneAmount = atoi(stringVector[6].c_str());
            //int oreAmount = atoi(stringVector[7].c_str());
            playerResources.insert(std::pair<Course::BasicResource,int>(Course::MONEY, moneyAmount));
            playerResources.insert(std::pair<Course::BasicResource,int>(Course::FOOD, foodAmount));
            playerResources.insert(std::pair<Course::BasicResource,int>(Course::WOOD, woodAmount));
            playerResources.insert(std::pair<Course::BasicResource,int>(Course::STONE, stoneAmount));
            playerResources.insert(std::pair<Course::BasicResource,int>(Course::ORE, 10));

            std::shared_ptr<Player> playerPtr = std::make_shared<Player>(playerName, playerResources);

            playerPtr->setMarker(index);

            playerVector_.push_back(playerPtr);
            index++;
        }

        eventhandler_->addPlayerVector(playerVector_);

        if(stringVector[0]=="CURRENTPLAYER"){
            eventhandler_->addPlayerVector(playerVector_);
            eventhandler_->setCurrentPlayer(stringVector[1]);
        }


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
            tileVector.push_back(constructorPointer(Course::Coordinate(xCoord, yCoord), eventhandler_, objectManager_));
        }
    }
    objectManager_->addTiles(tileVector);
    addUnitsAndBuildings(fileName);

}
