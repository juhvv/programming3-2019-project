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
}

unsigned int GameEventHandler::getTurnNumber()
{
    return turnNumber_;
}
