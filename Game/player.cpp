#include "player.hh"
#include "core/playerbase.h"




Player::Player(const std::string &name,
               const std::vector<std::shared_ptr<Course::GameObject> > objects):
    Course::PlayerBase(name,
                       objects)
{
    m_name = name;
}

std::string Player::getName(){
    return m_name;
}
