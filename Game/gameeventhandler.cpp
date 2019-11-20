#include "gameeventhandler.hh"

GameEventHandler::GameEventHandler():
    turnNumber_(1),
    maxTurns_(30)
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
    ++turnNumber_;
    if(currentPlayer_==playerVector_[0]){
        currentPlayer_=playerVector_[1];
    }
    else{
        currentPlayer_=playerVector_[0];
    }
}

unsigned int GameEventHandler::getTurnNumber()
{
    return turnNumber_;
}

std::shared_ptr<Player> GameEventHandler::getCurrentPlayer()
{
    return currentPlayer_;
}

void GameEventHandler::addNewPlayers(std::vector<std::string> nameVct)
{
    for(long unsigned int i=0; i<nameVct.size(); i++){
        std::string nameOfPlayer = nameVct[i];
        std::shared_ptr<Player> playerPtr = std::make_shared<Player>(nameOfPlayer);
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

