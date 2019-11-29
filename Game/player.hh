#ifndef PLAYER_HH
#define PLAYER_HH

#include "core/playerbase.h"
#include "core/gameobject.h"
#include <QPixmap>
#include "core/basicresources.h"
#include "ui/customgraphicsitem.h"
#include "buildings/gamebuildingbase.h"
#include <units/graphicsunitbase.h>


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

    void resetData();

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

    void addGameObject(CustomGraphicsItem *newItem);

    void addUnit(std::shared_ptr<GraphicsUnitBase> newUnit);

    void addNewBuilding(std::shared_ptr<GameBuildingBase> newBuilding);

    std::vector<std::shared_ptr<GraphicsUnitBase> > getPlayerUnits() const;

private:
    std::string m_name;
    QPixmap marker_;
    Course::ResourceMap m_playerResources;
    std::vector<std::shared_ptr<GameObjectBase>> playerObjects_ = {};
    std::vector<std::shared_ptr<GraphicsUnitBase>> playerUnits_ = {};
    std::vector<std::shared_ptr<GameBuildingBase>> playerBuildings_ =  {};
};

#endif // PLAYER_HH
