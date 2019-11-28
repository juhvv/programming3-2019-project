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

    std::shared_ptr<GameBuildingBase> constructBuilding(std::shared_ptr<Player> &owner,
                                                        std::shared_ptr<GraphicsTileBase> &tile);

    void setEventHandler(const std::shared_ptr<GameEventHandler> &eventHandler);

    void setObjectManager(const std::shared_ptr<ObjectManager> &objectManager);

private:
    std::shared_ptr<GameEventHandler> eventHandler_;
    std::shared_ptr<ObjectManager> objectManager_;
};

#endif // UNITCONSTRUCTOR_H
