#ifndef SAWMILL_H
#define SAWMILL_H

#include "buildings/gamebuildingbase.h"

/**
 * @brief The Sawmill class implements sawmill building that produces wood. Can be built
 * \n only on tiles that have HAS_TREES tag.
 */
class SawMill : public GameBuildingBase
{
public:
    SawMill() = delete;

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
    explicit SawMill(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            CustomGraphicsScene* scene = nullptr,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = GameConstResourceMaps::SAWMILL_BUILD_COST,
            const Course::ResourceMap& production = GameConstResourceMaps::SAWMILL_PRODUCTION
            );

    virtual ~SawMill() = default;

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

#endif // SAWMILL_H
