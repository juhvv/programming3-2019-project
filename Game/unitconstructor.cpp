#include "unitconstructor.h"
#include "objectmanager.hh"
#include "gameeventhandler.hh"

UnitConstructor::UnitConstructor() :
    eventHandler_(nullptr),
    objectManager_(nullptr)
{

}

UnitConstructor::~UnitConstructor()
{

}
/*
std::shared_ptr<GameBuildingBase> UnitConstructor::constructBuilding(std::shared_ptr<Player> &owner,
                                                                     std::shared_ptr<GraphicsTileBase> &tile)
{
    std::shared_ptr<GameBuildingBase> newBuilding =
            std::make_shared<GameBuildingBase>(eventHandler_, objectManager_, owner);
    std::shared_ptr<GameObjectBase> buildingGameObject = newBuilding;
    tile->addBuilding(newBuilding);
    objectManager_->setGraphicsObject(buildingGameObject);
    eventHandler_->claimTile(tile.get());

    return newBuilding;
}

std::shared_ptr<GraphicsUnitBase> UnitConstructor::constructUnit(std::shared_ptr<Player> &owner,
                                                                 std::shared_ptr<GraphicsTileBase> &tile)
{
    std::shared_ptr<GraphicsUnitBase> newUnit =
            std::make_shared<GraphicsUnitBase>(eventHandler_, objectManager_, owner);
    std::shared_ptr<GameObjectBase> unitGameObject = newUnit;
    objectManager_->setGraphicsObject(unitGameObject);
    newUnit->moveToTile(tile, true);
    return newUnit;
}
*/
void UnitConstructor::setEventHandler(const std::shared_ptr<GameEventHandler> &eventHandler)
{
    eventHandler_ = eventHandler;
}

void UnitConstructor::setObjectManager(const std::shared_ptr<ObjectManager> &objectManager)
{
    objectManager_ = objectManager;
}
