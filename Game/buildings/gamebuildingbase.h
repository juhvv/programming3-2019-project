#ifndef GAMEBUILDINGBASE_H
#define GAMEBUILDINGBASE_H

#include "buildings/buildingbase.h"
#include "gameobjectbase.h"
#include "gameresourcemaps.hh"

/**
 * @brief The GameBuildingBase class is a GameObjectBase and BuildingBase
 * \n derived base class for buildings
 */
class GameBuildingBase : public GameObjectBase, public Course::BuildingBase
{
public:
    GameBuildingBase() = delete;

    /**
     * @brief Constructor
     * @param eventhandler Ptr to eventhandler
     * @param objectmanager Ptr to objectmanager
     * @param owner Building's owner
     * @param scene Ptr to CustomGraphicsScene
     * @param tilespaces How many points of space this building takes from a tile
     * @param buildcost ResourceMap that specifies build cost
     * @param production ResourceMap that specifies building production
     */
    explicit GameBuildingBase(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            CustomGraphicsScene* scene = nullptr,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = {},
            const Course::ResourceMap& production = {}
            );

    virtual ~GameBuildingBase() = default;

    /**
     * @copydoc GameObjectBase::setGraphicsItem
     */
    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    /**
     * @copydoc GameObjectBase::getMenuItems
     */
    virtual void getMenuItems(QMenu &menu) override;

    /**
     * @copydoc GameObjectBase::getDescriptionBrief
     */
    virtual void getDescriptionBrief(std::string &desc) override;
};

#endif // GAMEBUILDINGBASE_H
