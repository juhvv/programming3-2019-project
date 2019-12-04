#ifndef GAMEFARM_H
#define GAMEFARM_H

#include "gamebuildingbase.h"
#include "core/resourcemaps.h"

/**
 * @brief The Farm class implements farm building that produces food. Can be built
 * \n only on tiles that have IS_FLAT tag.
 */
class Farm : public GameBuildingBase
{
public:
    Farm() = delete;

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
    explicit Farm(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            CustomGraphicsScene* scene = nullptr,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = GameConstResourceMaps::FARM_BUILD_COST,
            const Course::ResourceMap& production = GameConstResourceMaps::FARM_PRODUCTION
            );

    virtual ~Farm() = default;

    /**
     * @copydoc GameObjectBase::setGraphicsItem
     */
    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    /**
     * @copydoc GameObjectBase::getType
     */
    virtual std::string getType() const override;

    /**
     * @copydoc GameObjectBase::getDescriptionBrief
     */
    virtual void getDescriptionBrief(std::string &desc) override;
};

#endif // GAMEFARM_H
