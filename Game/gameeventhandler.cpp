#include "gameeventhandler.hh"
#include "buildings/base.h"


GameEventHandler::GameEventHandler(std::shared_ptr<ObjectManager> objectMngr,
                                   std::weak_ptr<UnitConstructor> unitConstructor):
    Course::iGameEventHandler(),
    turnNumber_(1),
    maxTurns_(30),
    objectMngr_(objectMngr),
    unitConstructor_(unitConstructor)
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

    for (auto gameObject : currentPlayer_->getPlayerUnits()) {
        GraphicsUnitBase* unit = dynamic_cast<GraphicsUnitBase*>(gameObject.get());
        if (unit != nullptr) {
            unit->switchTurn();
        }
    }
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
    // return totalProduction;
    }
    return totalProduction;
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

std::vector<std::shared_ptr<Player> > GameEventHandler::getPlayerVector()
{
    return playerVector_;
}

void GameEventHandler::addNewPlayers(std::vector<std::pair<std::string, int>> nameVct)
{
    Course::Coordinate startCoord = Course::Coordinate(2,2);

    for(long unsigned int i=0; i<nameVct.size(); i++){
        std::string nameOfPlayer = nameVct[i].first;
        std::shared_ptr<Player> playerPtr = std::make_shared<Player>(nameOfPlayer);
        playerPtr->setMarker(nameVct[i].second);
        playerVector_.push_back(playerPtr);
        currentPlayer_ = playerPtr;

        // add starter bases
        std::shared_ptr<GraphicsTileBase> startTile =
                std::dynamic_pointer_cast<GraphicsTileBase>(objectMngr_->getTile(startCoord));
        // switch start tile if no building can be placed on current start tile
        while (startTile->getType() == "Water tile") {
            qDebug() << "tile type for " << currentPlayer_->getName().c_str() << ": " << startTile->getType().c_str();
            startTile = std::dynamic_pointer_cast<GraphicsTileBase>(objectMngr_->getTile(startTile->ID + 1));
        }
        qDebug() << "Final tile type for " << currentPlayer_->getName().c_str() << ": " << startTile->getType().c_str();
        addBuilding<Base>(startTile);
        claimTile(startTile.get());

        // currentPlayer_ = playerPtr;
        // startTile->addBuilding(startBuilding);
        // claimTile(startTile.get());
        // objectMngr_->setGraphicsObject(gameObject);

        startCoord.set_x(startCoord.x() + 15);
        startCoord.set_y(startCoord.y() + 15);
    }

    currentPlayer_ = playerVector_[0];
}

void GameEventHandler::resetData()
{
    turnNumber_ = 1;
    for (auto player : playerVector_) {
        player->resetData();
        qDebug() << player.use_count();
    }
    playerVector_.clear();
    currentPlayer_ = nullptr;
    objectMngr_->resetData();
}

void GameEventHandler::sendMsg(std::string msg)
{
    emit signalSendMsg(msg);
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

    // test
    for ( auto unit : currentPlayer_->getPlayerUnits()) {
        qDebug() << unit.use_count();
    }
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
