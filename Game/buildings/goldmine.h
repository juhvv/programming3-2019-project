#ifndef GOLDMINE_H
#define GOLDMINE_H

#include "buildings/gamebuildingbase.h"

/**
 * @brief The GoldMine class implements gold mine building that produces gold and ore. Can be built
 * \n only on tiles that have HAS_ROCK tag.
 */
class GoldMine : public GameBuildingBase
{
public:
    GoldMine() = delete;

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
    explicit GoldMine(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            CustomGraphicsScene* scene = nullptr,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = GameConstResourceMaps::GOLDMINE_BUILD_COST,
            const Course::ResourceMap& production = GameConstResourceMaps::GOLDMINE_PRODUCTION
            );

    virtual ~GoldMine() = default;

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

#endif // GOLDMINE_H
