#ifndef PLAYER_HH
#define PLAYER_HH

#include "core/playerbase.h"
#include "core/gameobject.h"
#include <QPixmap>
#include "core/basicresources.h"
#include "ui/customgraphicsitem.h"
#include "buildings/gamebuildingbase.h"


class Player : public Course::PlayerBase
{
public:

    Player(const std::string& name,
           const std::vector<std::shared_ptr<Course::GameObject> > objects ={}
           );

    virtual ~Player() = default;

    std::string getName();
    void setMarker(int index);
    void getIcon(QPixmap &icon);

    /**
     * @brief Modify Player's resource. Can be used to both sum or subtract.
     * @param player Pointer to the Player whose resource is being modified.
     * @param resource Defines the modified resource.
     * @param amount Defines the amount of change.
     * @post Exception guarantee: Basic
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    bool modifyResource(Course::BasicResource resource, int amount);

    bool modifyResources(Course::ResourceMap resources);

    int getResourceValue(Course::BasicResource resource);

    Course::ResourceMap getResourceMap();

    void addGameObject(CustomGraphicsItem *newItem);

    void addNewBuilding(std::shared_ptr<GameBuildingBase> newBuilding);

private:
    std::string m_name;
    QPixmap marker_;
    Course::ResourceMap m_playerResources;
    std::vector<std::shared_ptr<GameObjectBase>> playerObjects_ = {};
    std::vector<std::shared_ptr<GameBuildingBase>> playerBuildings_ =  {};
};

#endif // PLAYER_HH
