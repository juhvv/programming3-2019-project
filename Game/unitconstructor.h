#ifndef UNITCONSTRUCTOR_H
#define UNITCONSTRUCTOR_H

#include "player.hh"
#include "buildings/gamebuildingbase.h"
#include "units/graphicsunitbase.h"

class GameEventHandler;

class ObjectManager;

class UnitConstructor
{
public:
    UnitConstructor();

    ~UnitConstructor();

    template<typename BuildingType>
    std::shared_ptr<BuildingType> constructBuilding(std::shared_ptr<Player> &owner)
    {
        std::shared_ptr<BuildingType> newBuilding =
                std::make_shared<BuildingType>(eventHandler_, objectManager_, owner);
        return newBuilding;
    }

    template<typename UnitType>
    std::shared_ptr<UnitType> constructUnit(std::shared_ptr<Player> &owner)
    {
        std::shared_ptr<UnitType> newUnit =
                std::make_shared<UnitType>(eventHandler_, objectManager_, owner);
        return newUnit;
    }

    void setEventHandler(const std::shared_ptr<GameEventHandler> &eventHandler);

    void setObjectManager(const std::shared_ptr<ObjectManager> &objectManager);

private:
    std::shared_ptr<GameEventHandler> eventHandler_;
    std::shared_ptr<ObjectManager> objectManager_;
};

#endif // UNITCONSTRUCTOR_H
