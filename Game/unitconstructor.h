#ifndef UNITCONSTRUCTOR_H
#define UNITCONSTRUCTOR_H

#include "player.hh"
#include "buildings/gamebuildingbase.h"
#include "units/graphicsunitbase.h"

class GameEventHandler;

class ObjectManager;

/**
 * @brief The UnitConstructor class is used to create new unit and
 * \n building objects.
 */
class UnitConstructor
{
public:
    /**
     * @brief Constructor
     */
    UnitConstructor();

    ~UnitConstructor();

    /**
     * @brief Creates new building object with type specified by
     * \n template parameter
     * @param owner new building's owner
     * @note eventhandler and objectmanager have to be set for this object
     * \n before calling this method
     * @return shared ptr to created building
     */
    template<typename BuildingType>
    std::shared_ptr<BuildingType> constructBuilding(std::shared_ptr<Player> &owner)
    {
        std::shared_ptr<BuildingType> newBuilding =
                std::make_shared<BuildingType>(eventHandler_, objectManager_, owner);
        return newBuilding;
    }

    /**
     * @brief Creates new unit object with type specified by
     * \n template parameter
     * @param owner new unit's owner
     * @note eventhandler and objectmanager have to be set for this object
     * \n before calling this method
     * @return shared ptr to created unit
     */
    template<typename UnitType>
    std::shared_ptr<UnitType> constructUnit(std::shared_ptr<Player> &owner)
    {
        std::shared_ptr<UnitType> newUnit =
                std::make_shared<UnitType>(eventHandler_, objectManager_, owner);
        return newUnit;
    }

    /**
     * @brief Sets the eventhandler used by this object
     * @param eventHandler pointer to eventhandler
     */
    void setEventHandler(const std::shared_ptr<GameEventHandler> &eventHandler);

    /**
     * @brief Sets the objectmanager used by this object
     * @param objectManager pointer to objectmanager
     */
    void setObjectManager(const std::shared_ptr<ObjectManager> &objectManager);

private:
    std::shared_ptr<GameEventHandler> eventHandler_;
    std::shared_ptr<ObjectManager> objectManager_;
};

#endif // UNITCONSTRUCTOR_H
