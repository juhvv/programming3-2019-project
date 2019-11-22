#ifndef PLAYER_HH
#define PLAYER_HH

#include "core/playerbase.h"
#include "core/gameobject.h"
#include <QPixmap>
#include "core/basicresources.h"


class Player : public Course::PlayerBase
{
public:

    Player(const std::string& name,
           const std::vector<std::shared_ptr<Course::GameObject> > objects ={}
           );

    std::string getName();
    void setMarker(int index);
    void getIcon(QPixmap &icon);

    int getResourceValue(Course::BasicResource resource);

private:
    std::string m_name;
    QPixmap marker_;
    Course::ResourceMap m_playerResources;
};

#endif // PLAYER_HH
