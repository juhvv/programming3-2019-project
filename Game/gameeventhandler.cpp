#include "gameeventhandler.hh"
#include "buildings/base.h"


GameEventHandler::GameEventHandler(std::shared_ptr<ObjectManager> objectMngr,
                                   std::weak_ptr<UnitConstructor> unitConstructor):
    Course::iGameEventHandler(),
    turnNumber_(1),
    maxTurns_(100),
    objectMngr_(objectMngr),
    unitConstructor_(unitConstructor)
{

}

void GameEventHandler::nextTurn()
{
    for (auto gameObject : currentPlayer_->getPlayerUnits()) {
        GraphicsUnitBase* unit = dynamic_cast<GraphicsUnitBase*>(gameObject.get());
        if (unit != nullptr) {
            unit->switchTurn();
        }
    }
    calculateAddProduction();
    isGameOver();
    ++turnNumber_;
    if(currentPlayer_==playerVector_[0]){
        currentPlayer_=playerVector_[1];
    }
    else{
        currentPlayer_=playerVector_[0];
    }

    emit signalUpdateVisibleResources();

}

Course::ResourceMap GameEventHandler::calculateProduction()
{
    std::vector<std::shared_ptr<Course::TileBase>> tileVector = objectMngr_->getAllTiles();
    Course::ResourceMap totalNetProduction;
    for(auto tile: tileVector){
        if(tile->getWorkers().size()!=0){
            if(tile->getWorkers()[0]->getOwner()==currentPlayer_){
                std::shared_ptr<GraphicsTileBase> newerTile = std::dynamic_pointer_cast<GraphicsTileBase>(tile);
                Course::ResourceMap tileProduction = newerTile->generatedResources(currentPlayer_);
                totalNetProduction = Course::mergeResourceMaps(totalNetProduction, tileProduction);
            }
        }
    }
    return totalNetProduction;
}

void GameEventHandler::calculateAddProduction()
{
    Course::ResourceMap totalNetProduction = calculateProduction();
    currentPlayer_->modifyResources(totalNetProduction);
    std::string currentPlayer = currentPlayer_->getName();
    if((currentPlayer_->getResourceMap()[Course::FOOD]+totalNetProduction[Course::FOOD])<0){
        isGameOver(currentPlayer+" run out of food, all units died and you lost!");
    }
}

unsigned int GameEventHandler::getTurnNumber()
{
    return turnNumber_;
}

void GameEventHandler::setCurrentPlayer(std::string currentPlayer)
{
    for(long unsigned int i=0; i<playerVector_.size(); i++){
        if(playerVector_[i]->getName()==currentPlayer){
            currentPlayer_=playerVector_[i];
        }
    }
}

void GameEventHandler::setTurnNumber(unsigned int turn)
{
    turnNumber_=turn;
}

std::shared_ptr<Player> GameEventHandler::getPlayerFromName(std::string playerName)
{
    for(long unsigned int i=0; i<playerVector_.size(); i++){
        if(playerVector_[i]->getName()==playerName){
            return playerVector_[i];
        }
    }
    return nullptr;
}

void GameEventHandler::nextTurnButtonMode(bool buttonMode){
    emit signalNextButtonMode(buttonMode);
}

void GameEventHandler::addPlayerVector(std::vector<std::shared_ptr<Player> > playerVector)
{
    playerVector_=playerVector;
}


std::shared_ptr<Player> GameEventHandler::getCurrentPlayer()
{
    return currentPlayer_;
}

std::vector<std::shared_ptr<Player> > GameEventHandler::getPlayerVector()
{
    return playerVector_;
}

void GameEventHandler::addNewPlayers(std::vector<std::pair<std::string, int>> nameVct, MapSize::Size mapSize)
{
    Course::Coordinate startCoord = Course::Coordinate(mapSize * 0.1, mapSize * 0.1);

    for(long unsigned int i=0; i<nameVct.size(); i++){
        std::string nameOfPlayer = nameVct[i].first;
        std::shared_ptr<Player> playerPtr = std::make_shared<Player>(nameOfPlayer, GameConstResourceMaps::STARTING_RESOURCES);
        // sets marker
        playerPtr->setMarker(nameVct[i].second);
        playerVector_.push_back(playerPtr);
        currentPlayer_ = playerPtr;

        // add starter bases
        std::shared_ptr<GraphicsTileBase> startTile =
                std::dynamic_pointer_cast<GraphicsTileBase>(objectMngr_->getTile(startCoord));
        // switch start tile if no building can be placed on current start tile
        while (startTile->hasTag(objectTags::NO_BUILD)) {
            startTile = std::dynamic_pointer_cast<GraphicsTileBase>(objectMngr_->getTile(startTile->ID + 1));
        }
        qDebug() << "GameEventHandler::addNewPlayers :"
                    "Final tile type for " << currentPlayer_->getName().c_str() << ": "
                 << startTile->getType().c_str();
        addBuilding<Base>(startTile, currentPlayer_, true);
        claimTile(startTile.get());

        startCoord.set_x(mapSize * 0.87);
        startCoord.set_y(mapSize * 0.87);
    }

    currentPlayer_ = playerVector_[0];
}

void GameEventHandler::resetData()
{
    turnNumber_ = 1;
    for (auto player : playerVector_) {
        player->resetData();
        //qDebug() << player.use_count();
    }
    playerVector_.clear();
    currentPlayer_ = nullptr;
    objectMngr_->resetData();
}

void GameEventHandler::isGameOver(std::string endMessage)
{
    std::string emptyString = "";
    qDebug()<<"loppuviesti: "<<endMessage.length()<<QString::fromStdString(endMessage);
    if(endMessage!=emptyString){
            qDebug()<<"endmessage liipalaapa";
        emit signalSendMsg(endMessage);
        nextTurnButtonMode(false);
    }

    else if (currentPlayer_->getResourceMap()[Course::BasicResource::MONEY] > 1000) {
        qDebug() << currentPlayer_->getName().c_str() << " won!";
        std::string winnerMsg = "<<"+currentPlayer_->getName()+" WON! With a huge pile of money!>>";
        signalSendMsg(winnerMsg);
        nextTurnButtonMode(false);
    }

    else if (turnNumber_ == maxTurns_) {
        std::string endMsg = "<<NO MORE TURNS, GAME OVER>>";
        signalSendMsg(endMsg);
        nextTurnButtonMode(false);
    }
}

void GameEventHandler::sendMsg(std::string msg)
{
    emit signalSendMsg(msg);
}

void GameEventHandler::updateVisibleResources()
{
    emit signalUpdateVisibleResources();
}

void GameEventHandler::claimTile(GraphicsTileBase *tile, std::shared_ptr<Player> player)
{
    if(player==nullptr){
        player=currentPlayer_;
    }

    if (tile->getOwner() == nullptr) {
        tile->setOwner(player);
        QPixmap pixmapDef = QPixmap(":/resources/overlay faction1.PNG");
        QPixmap pixmap;
        player->getIcon(pixmap);
        objectMngr_->setOwnerMarker(tile, &pixmap);
    }
}



//Empty implementations, not used
bool GameEventHandler::modifyResource(std::shared_ptr<Player> player,
                                      Course::BasicResource resource,
                                      int amount)
{
    return player->modifyResource(resource, amount);
}

bool GameEventHandler::modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                      Course::BasicResource resource, int amount)
{
    return modifyResource(std::dynamic_pointer_cast<Player>(player), resource, amount);
}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> player, Course::ResourceMap resources)
{
    return modifyResources(std::dynamic_pointer_cast<Player>(player), resources);
}

bool GameEventHandler::modifyResources(std::shared_ptr<Player> player,
                                       Course::ResourceMap resources)
{
    return player->modifyResources(resources);
}
