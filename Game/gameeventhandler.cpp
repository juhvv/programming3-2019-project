#include "gameeventhandler.hh"

GameEventHandler::GameEventHandler(std::shared_ptr<ObjectManager> objectMngr):
    turnNumber_(1),
    maxTurns_(30),
    objectMngr_(objectMngr)
{

}


void GameEventHandler::nextTurn()
{
    calculateAddProduction();
    ++turnNumber_;
    if(currentPlayer_==playerVector_[0]){
        currentPlayer_=playerVector_[1];
    }
    else{
        currentPlayer_=playerVector_[0];
    }
    signalUpdateVisibleResources();
}

Course::ResourceMap GameEventHandler::calculateProduction()
{
    std::vector<std::shared_ptr<Course::TileBase>> tileVector = objectMngr_->getAllTiles();
    Course::ResourceMap totalProduction;
    for(auto tile: tileVector){
        std::shared_ptr<Course::PlayerBase>tileOwner = tile->getOwner();
        if(tileOwner == currentPlayer_){
            qDebug()<<"meil on samat hei...";
            std::shared_ptr<GraphicsTileBase> newerTile = std::dynamic_pointer_cast<GraphicsTileBase>(tile);

            Course::ResourceMap tileProduction = newerTile->generatedResources();

            Course::mergeResourceMaps(totalProduction, tileProduction);
        }
    return totalProduction;
    }
}

void GameEventHandler::calculateAddProduction()
{
    Course::ResourceMap totalProduction = calculateProduction();
    currentPlayer_->modifyResources(totalProduction);
    qDebug()<<"kalkuloidaan...";
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
    currentPlayer_ = nullptr;
}



void GameEventHandler::claimTile(GraphicsTileBase *tile)
{
    tile->setOwner(currentPlayer_);
    QPixmap pixmapDef = QPixmap(":/resources/overlay faction1.PNG");
    QPixmap pixmap;
    currentPlayer_->getIcon(pixmap);
    objectMngr_->setOwnerMarker(tile, &pixmap);

    //Just testing that resources work
    currentPlayer_->modifyResource(Course::MONEY, -10);
    signalUpdateVisibleResources();
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

