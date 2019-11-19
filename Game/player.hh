#ifndef PLAYER_HH
#define PLAYER_HH

#include "core/playerbase.h"
#include "core/gameobject.h"


class Player : public Course::PlayerBase
{
public:


    Player(const std::string& name,
           const std::vector<std::shared_ptr<Course::GameObject> > objects ={});

    std::string getName();

private:
    std::string m_name;
};

#endif // PLAYER_HH
