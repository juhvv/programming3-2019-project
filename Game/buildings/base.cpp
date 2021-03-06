#include "base.h"

#include "gameeventhandler.hh"
#include "ui/customgraphicsitem.h"
#include "ui/customgraphicsscene.h"
#include "units/builder.h"
#include "units/scout.h"
#include "units/worker.h"

Base::Base(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                                   const std::shared_ptr<Course::iObjectManager> &objectmanager,
                                   const std::shared_ptr<Course::PlayerBase> &owner,
                                   CustomGraphicsScene *scene,
                                   const int &tilespaces,
                                   const Course::ResourceMap &buildcost,
                                   const Course::ResourceMap &production) :
    GameBuildingBase (eventhandler, objectmanager,owner, scene, tilespaces, buildcost, production)
{

}

void Base::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    GameBuildingBase::setGraphicsItem(graphicsItem, scene);

    // std::shared_ptr<Course::TileBase> currentTile = lockObjectManager()->getTile(getCoordinate());
    std::shared_ptr<GraphicsTileBase> currentTile =
            std::dynamic_pointer_cast<GraphicsTileBase>(lockObjectManager()->getTile(getCoordinate()));
    std::vector<CustomGraphicsItem*> adjTiles;
    scene_->getAdjacentTiles(adjTiles, currentTile);

    std::shared_ptr<GameEventHandler> handler =
            std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());

    for (auto tileObj : adjTiles) {
        std::weak_ptr<GraphicsTileBase> tile =
                std::dynamic_pointer_cast<GraphicsTileBase>(tileObj->getParentObject().lock());
        handler->claimTile(tile.lock().get(), std::dynamic_pointer_cast<Player>(getOwner()));
    }
}

void Base::getMenuItems(QMenu &menu)
{
    menu.addSeparator();

    QMenu *workerHireMenu = menu.addMenu("Hire unit...");
    std::shared_ptr<ObjectManager> manager =
            std::dynamic_pointer_cast<ObjectManager>(lockObjectManager());
    std::shared_ptr<GraphicsTileBase> curTile = manager->getGTile(getCoordinate());

    // check if tile has any space for workers
    if (curTile->hasSpaceForWorkers(1)) {
        getBuildMenu(*workerHireMenu);

    } else {
        workerHireMenu->setDisabled(true);
        workerHireMenu->setTitle("Can't hire units - Tile is full");
    }
}

void Base::getBuildMenu(QMenu &bmenu)
{
    std::shared_ptr<ObjectManager> manager =
            std::dynamic_pointer_cast<ObjectManager>(lockObjectManager());
    std::shared_ptr<GraphicsTileBase> curTile = manager->getGTile(getCoordinate());
    QAction* hireBuilderAction = bmenu.addAction("Hire builder");
    QAction* hireScoutAction = bmenu.addAction("Hire scout");
    QAction* hireWorkerAction = bmenu.addAction("Hire worker");

    // currently there are no unit-specific build limitations, so following checks are always true
    if (/* DISABLES CODE */ (true)) {
        connect(hireBuilderAction, &QAction::triggered, this, &Base::hireUnitSlot<Builder>);

    } else {
        hireBuilderAction->setText("Not enough space for builder.");
        hireBuilderAction->setDisabled(true);
    }

    if (/* DISABLES CODE */ (true)) {
        connect(hireScoutAction, &QAction::triggered, this, &Base::hireUnitSlot<Scout>);

    } else {
        hireScoutAction->setText("Not enough space for scout.");
        hireScoutAction->setDisabled(true);
    }

    if (/* DISABLES CODE */ (true)) {
        connect(hireWorkerAction, &QAction::triggered, this, &Base::hireUnitSlot<Worker>);

    } else {
        hireWorkerAction->setText("Not enough space for worker.");
        hireWorkerAction->setDisabled(true);
    }
}

std::string Base::getType() const
{
    return "Base";
}

void Base::getDescriptionBrief(std::string &desc)
{
    desc += "\n " + getOwner()->getName() + " has built their base here.";
}

