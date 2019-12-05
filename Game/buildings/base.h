#ifndef BASE_H
#define BASE_H

#include "buildings/gamebuildingbase.h"
#include "gameresourcemaps.hh"
#include "gameeventhandler.hh"

/**
 * @brief The Base class implements players base building. It provides functionality for
 * \n creating units. It is automatically built for each player when game starts.
 */
class Base : public GameBuildingBase
{
public:
    Base() = delete;
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
    explicit Base(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            CustomGraphicsScene* scene = nullptr,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = GameConstResourceMaps::HQ_BUILD_COST,
            const Course::ResourceMap& production = GameConstResourceMaps::HQ_PRODUCTION
            );

    virtual ~Base() = default;

    /**
     * @copydoc GameObjectBase::setGraphicsItem
     */
    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    /**
     * @copydoc GameObjectBase::getMenuItems
     */
    virtual void getMenuItems(QMenu &menu) override;

    /**
     * @brief getBuildMenu gets this building's unit hire menu
     * @param bmenu Menu which receives hire actions
     */
    virtual void getBuildMenu(QMenu &bmenu);

    /**
     * @copydoc GameObjectBase::getType
     */
    virtual std::string getType() const override;

    /**
     * @copydoc GameObjectBase::getDescriptionBrief
     */
    virtual void getDescriptionBrief(std::string &desc) override;

public slots:
    /**
     * @brief Create unit at tile of this building. Template parameter specifies unit type.
     */
    template<typename UnitType>
    void hireUnitSlot() {
        std::shared_ptr<GameEventHandler> handler =
                std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
        std::shared_ptr<ObjectManager> manager =
                std::dynamic_pointer_cast<ObjectManager>(lockObjectManager());

        handler->addUnit<UnitType>(manager->getGTile(getCoordinate()),
                                   std::dynamic_pointer_cast<Player>(getOwner()));
    }
};

#endif // BASE_H
