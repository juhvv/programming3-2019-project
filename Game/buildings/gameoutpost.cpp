#include "gameoutpost.h"
#include "ui/customgraphicsscene.h"
#include "core/playerbase.h"
#include "gameeventhandler.hh"
#include "units/worker.h"

Outpost::Outpost(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                 const std::shared_ptr<Course::iObjectManager> &objectmanager,
                 const std::shared_ptr<Course::PlayerBase> &owner,
                 CustomGraphicsScene *scene,
                 const int &tilespaces,
                 const Course::ResourceMap &buildcost,
                 const Course::ResourceMap &production) :
    GameBuildingBase (eventhandler, objectmanager, owner, scene, tilespaces, buildcost, production)
{

}

void Outpost::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    GameBuildingBase::setGraphicsItem(graphicsItem, scene);

    graphicsItem_->setPixmap(QPixmap(":/resources/buildings/outpost.png"));

    std::shared_ptr<GraphicsTileBase> currentTile =
            std::dynamic_pointer_cast<GraphicsTileBase>(lockObjectManager()->getTile(getCoordinate()));
    std::vector<CustomGraphicsItem*> adjTiles;
    scene_->getAdjacentTiles(adjTiles, currentTile);

    std::shared_ptr<GameEventHandler> handler =
            std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());

    for (auto tileObj : adjTiles) {
        std::weak_ptr<GraphicsTileBase> tile =
                std::dynamic_pointer_cast<GraphicsTileBase>(tileObj->getParentObject().lock());
        handler->claimTile(tile.lock().get());
    }
}

std::string Outpost::getType() const
{
    return "Outpost";
}

void Outpost::getDescriptionBrief(std::string &desc)
{
    desc += "\n " + getOwner()->getName() + " has built an outpost here.";
}

void Outpost::getMenuItems(QMenu &menu)
{
    menu.addSeparator();

    QAction *workerHireAction = menu.addAction("Hire worker");
    connect(workerHireAction, &QAction::triggered, this, &Outpost::hireWorkerSlot);
}

void Outpost::hireWorkerSlot()
{
    std::shared_ptr<GameEventHandler> handler =
            std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
    std::shared_ptr<ObjectManager> manager =
            std::dynamic_pointer_cast<ObjectManager>(lockObjectManager());

    handler->addUnit<Worker>(manager->getGTile(getCoordinate()));
}
