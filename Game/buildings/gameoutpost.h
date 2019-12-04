#ifndef GAMEOUTPOST_H
#define GAMEOUTPOST_H

#include "gamebuildingbase.h"
#include "gameresourcemaps.hh"

/**
 * @brief The Outpost class implements outpost building that a scout unit can build.
 * \n Functionality for constructing workers is provided. When built, free adjacent tiles are claimed.
 */
class Outpost : public GameBuildingBase
{
public:
    Outpost() = delete;

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
    explicit Outpost(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            CustomGraphicsScene* scene = nullptr,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = GameConstResourceMaps::OUTPOST_BUILD_COST,
            const Course::ResourceMap& production = GameConstResourceMaps::OUTPOST_PRODUCTION
            );

    virtual ~Outpost() = default;

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

    /**
     * @copydoc GameObjectBase::getMenuItems
     */
    virtual void getMenuItems(QMenu &menu) override;

private slots:
    /**
     * @brief Constructs a worker at this building's tile
     */
    void hireWorkerSlot();
};
#endif // GAMEOUTPOST_H
