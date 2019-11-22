#ifndef PLAYER_HH
#define PLAYER_HH

#include "core/playerbase.h"
#include "core/gameobject.h"
#include <QPixmap>


class Player : public Course::PlayerBase
{
public:


    Player(const std::string& name,
           const std::vector<std::shared_ptr<Course::GameObject> > objects ={});

    std::string getName();
    void setMarker(int index);
    void getIcon(QPixmap &icon);

private:
    std::string m_name;
    QPixmap marker_;
};

#endif // PLAYER_HH
