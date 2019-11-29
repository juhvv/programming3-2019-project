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

int Player::getResourceValue(Course::BasicResource resource)
{
    return m_playerResources[resource];
}

Course::ResourceMap Player::getResourceMap()
{
    return m_playerResources;
}

void Player::addGameObject(CustomGraphicsItem *newItem)
{
    // playerObjects_.push_back(newItem);
}

void Player::addNewBuilding(std::shared_ptr<GameBuildingBase> newBuilding)
{
    playerBuildings_.push_back(newBuilding);
}

void Player::setMarker(int index)
{
    if (index == 0) {
        marker_ = QPixmap(":/resources/overlay faction1.PNG");
    } else {
        marker_ = QPixmap(":/resources/overlay faction2.PNG");
    }
}

void Player::getIcon(QPixmap &icon)
{
    icon = marker_;
}
bool Player::modifyResources(Course::ResourceMap resources)
{
    Course::ResourceMap resourceSum = Course::mergeResourceMaps(resources, m_playerResources);
    for(auto it = resourceSum.begin(); it != resourceSum.end(); it++)
        if(it->second < 0){
            return false;
        }
    m_playerResources = resourceSum;
    return true;
}

bool Player::modifyResource(Course::BasicResource resource, int amount)
{
    if(m_playerResources[resource]+amount > 0){
        m_playerResources[resource]=m_playerResources[resource]+amount;
        return true;
    }
    else{
        return false;
    }
}

