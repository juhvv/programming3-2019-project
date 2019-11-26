#include "gameeventhandler.hh"

GameEventHandler::GameEventHandler(std::shared_ptr<ObjectManager> objectMngr):
    turnNumber_(1),
    maxTurns_(30),
    objectMngr_(objectMngr)
{

}

bool GameEventHandler::modifyResource(std::shared_ptr<Course::PlayerBase> player, Course::BasicResource resource, int amount)
{
    return true;
}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> player, Course::ResourceMap resources)
{
    return true;
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
    std::vector<std::shared_ptr<Course::TileBase>> tiles = objectMngr_->getAllTiles();

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

void signalUpdateVisibleResources()
{

}

