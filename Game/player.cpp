#include "player.hh"
#include "core/playerbase.h"




Player::Player(const std::string &name,
               const std::vector<std::shared_ptr<Course::GameObject> > objects
               ):
    Course::PlayerBase(name,
                       objects)
{
    m_name = name;

    //Start values for resources
    m_playerResources.insert(std::pair<Course::BasicResource,int>(Course::MONEY, 1500));
    m_playerResources.insert(std::pair<Course::BasicResource,int>(Course::FOOD, 100));
    m_playerResources.insert(std::pair<Course::BasicResource,int>(Course::WOOD, 200));
    m_playerResources.insert(std::pair<Course::BasicResource,int>(Course::STONE, 250));
    m_playerResources.insert(std::pair<Course::BasicResource,int>(Course::ORE, 300));
}

std::string Player::getName(){
    return m_name;
}
