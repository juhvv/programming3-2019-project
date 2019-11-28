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

std::shared_ptr<GameBuildingBase> UnitConstructor::constructBuilding(std::shared_ptr<Player> &owner)
{
    std::shared_ptr<Course::iGameEventHandler> iHandler =
            std::dynamic_pointer_cast<Course::iGameEventHandler>(eventHandler_);

    std::shared_ptr<Course::iObjectManager> iManager =
            std::dynamic_pointer_cast<Course::iObjectManager>(objectManager_);
    return std::make_shared<GameBuildingBase>(eventHandler_, objectManager_, owner);
}

void UnitConstructor::setEventHandler(const std::shared_ptr<GameEventHandler> &eventHandler)
{
    eventHandler_ = eventHandler;
}

void UnitConstructor::setObjectManager(const std::shared_ptr<ObjectManager> &objectManager)
{
    objectManager_ = objectManager;
}
