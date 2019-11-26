#include "gameeventhandler.hh"

GameEventHandler::GameEventHandler(std::shared_ptr<ObjectManager> objectMngr):
    turnNumber_(1),
    maxTurns_(30),
    objectMngr_(objectMngr)
{

}


void GameEventHandler::nextTurn()
{
    calculateResources();
    ++turnNumber_;
    if(currentPlayer_==playerVector_[0]){
        currentPlayer_=playerVector_[1];
    }
    else{
        currentPlayer_=playerVector_[0];
    }
    //signalUpdateVisibleResources();
}

void GameEventHandler::calculateResources()
{
    std::vector<std::shared_ptr<Course::TileBase>> tileVector = objectMngr_->getAllTiles();
    int lukema = 0;
    QString testeri = "";
    qDebug()<<"calculoidaan...";
    for(auto tile: tileVector){
        lukema++;
        std::shared_ptr<Course::PlayerBase>tileOwner = tile->getOwner();
        //std::string nimi = tileOwner->getName();

        if(tile->getOwner() == NULL){

        }

        else if(tile->getOwner() != NULL){
            qDebug()<<"ei tyhja";
        }

        else{
            QString testeri = "JES";
        }
    }

    qDebug()<<testeri;




        /*
        if(tile->getOwner()==currentPlayer_){
            qDebug()<<"oikeaomistaja!";
            tile->generateResources();
        }



*/


        //std::string tiletype = tile->getType();
        //lukema++;
        //qDebug() << lukema;
       /* if(tile->getOwner()==currentPlayer_){
            int workerAmount = tile->getWorkerCount();
            Course::ConstResourceMaps tileRecourseMap =
            Course::ResourceMapDouble combinedWorkerEfficiency = NULL;
            Course::ResourceMap resourcesToBeAdded = NULL;
            for(int i=0; i<workerAmount; i++){
                combinedWorkerEfficiency = Course::mergeResourceMapDoubles(combinedWorkerEfficiency, Course::ConstResourceMaps::BW_WORKER_EFFICIENCY);
            }
            resourcesToBeAdded = Course::multiplyResourceMap()
        }
        */

}

unsigned int GameEventHandler::getTurnNumber()
{
    return turnNumber_;
}

std::shared_ptr<Player> GameEventHandler::getCurrentPlayer()
{
    return currentPlayer_;
}

void GameEventHandler::addNewPlayers(std::vector<std::pair<std::string, int>> nameVct)
{
    for(long unsigned int i=0; i<nameVct.size(); i++){
        std::string nameOfPlayer = nameVct[i].first;
        std::shared_ptr<Player> playerPtr = std::make_shared<Player>(nameOfPlayer);
        playerPtr->setMarker(nameVct[i].second);
        playerVector_.push_back(playerPtr);
    }
        currentPlayer_ = playerVector_[0];


}

void GameEventHandler::resetData()
{
    turnNumber_ = 1;
    playerVector_.clear();
    currentPlayer_ = NULL;
}



void GameEventHandler::claimTile(GraphicsTileBase *tile)
{
    tile->setOwner(currentPlayer_);
    QPixmap pixmapDef = QPixmap(":/resources/overlay faction1.PNG");
    QPixmap pixmap;
    currentPlayer_->getIcon(pixmap);
    objectMngr_->setOwnerMarker(tile, &pixmap);
}

//Empty implementations, not used
bool GameEventHandler::modifyResource(std::shared_ptr<Course::PlayerBase> player, Course::BasicResource resource, int amount)
{
    return true;
}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> player, Course::ResourceMap resources)
{
    return true;
}


void signalUpdateVisibleResources()
{

}

