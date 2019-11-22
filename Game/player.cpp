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
