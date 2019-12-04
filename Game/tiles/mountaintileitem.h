#ifndef MOUNTAINTILEITEM_H
#define MOUNTAINTILEITEM_H


#include "tiles/graphicstilebase.h"

/**
 * @brief The MountainTileItem class implements mountain tiles to the map. Move cost is 2
 * \n and tile has HAS_ROCK tag.
 */
class MountainTileItem : public GraphicsTileBase
{
public:
    MountainTileItem() = delete ;
    /**
     * @brief Constructor
     * @param location This tiles coordinates in the game's coordinate system
     * @param eventhandler Ptr to Eventhandler
     * @param objectmanager Ptr to Objectmanager
     * @param scene Ptr to CustomGraphicsScene
     * @param max_build How many buildings this tile can hold. Should be always 1.
     * @param max_work How many units this tile can hold.
     * @param production Resourcemap specifying this tile's production
     */
    explicit MountainTileItem(const Course::Coordinate& location,
                              const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                              const std::shared_ptr<Course::iObjectManager>& objectmanager,
                              CustomGraphicsScene* scene = nullptr,
                     const unsigned int& max_build = 1,
                     const unsigned int& max_work = 3,
                            const Course::ResourceMap& production = GameConstResourceMaps::MOUNTAIN_BP);

    virtual ~MountainTileItem() = default;

    /**
     * @copydoc GraphicsTileBase::getMovementCost()
     */
    virtual unsigned int getMovementCost() const override;

    /**
     * @copydoc GameObjectBase::getType
     */
    virtual std::string getType() const override;

    /**
     * @copydoc GameObjectBase::setGraphicsItem
     */
    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    /**
     * @copydoc GameObjectBase::getDescriptionBrief
     */
    virtual void getDescriptionBrief(std::string &desc) override;
};

#endif // MOUNTAINTILEITEM_H
