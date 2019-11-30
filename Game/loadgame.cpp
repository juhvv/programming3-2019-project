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


void LoadGame::loadGame(QString fileName)
{
    addConstructor<MountainTileItem>("Mountain tile");
    addConstructor<ForestTileItem>("Forest Tile");
    addConstructor<GrassTileItem>("Grass tile");
    addConstructor<WaterTileItem>("Water tile");

    eventhandler_->resetData();

    QString testFileName = "/home/vapola/ohjelmointi3/projekti/sami-seka-juho/Game/tallennukset/testitallennus.txt";

    std::vector<std::shared_ptr<Course::TileBase>> tileVector;

    QFile loadFile(testFileName);
    loadFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&loadFile);



    while (!in.atEnd()) {
        QString line = in.readLine();
        std::string stringLine = line.toUtf8().constData();
        std::vector<std::string> stringVector = split(stringLine);


        if(stringVector[0]=="PLAYERNAMES"){
        }

        if(stringVector[0]=="CURRENTPLAYER"){

        }

        if(stringVector[0]=="RESOURCES"){

        }

        if(stringVector[0]=="TILE"){

            std::string tileType = stringVector[1];
            unsigned int xCoord = atoi(stringVector[2].c_str());
            unsigned int yCoord = atoi(stringVector[3].c_str());
            std::string ownerName = stringVector[4];
            std::string buildingType = stringVector[5];
            std::string unitType = stringVector[6];

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




    /*
       for(std::string element: stringVector){
            QString Qelement = QString::fromStdString(element);
            qDebug()<<Qelement;
        }
        qDebug()<<"rivinvaihto";
    */


  //  qDebug()<<QString::fromStdString(tileConctructorNames_.begin()->first);

}
