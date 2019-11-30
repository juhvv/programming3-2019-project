#include "base.h"

#include "gameeventhandler.hh"
#include "ui/customgraphicsitem.h"
#include "ui/customgraphicsscene.h"
#include "units/builder.h"

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
        handler->claimTile(tile.lock().get());
    }
}

void Base::getMenuItems(QMenu &menu)
{
    menu.addSeparator();

    QAction *workerHireAction = menu.addAction("Build worker");
    connect(workerHireAction, &QAction::triggered, this, &GameBuildingBase::buildUnit);

    //QAction *claimAction = menu.addAction("Claim");
    // connect(infoAction, &QAction::triggered, this, &GraphicsTileBase::sendInfo);
    // connect(claimAction, &QAction::triggered, this, &GraphicsTileBase::sendPtr);
}

std::string Base::getType() const
{
    return "Base";
}

void Base::getDescriptionBrief(std::string &desc)
{
    desc += "\n " + getOwner()->getName() + " has built their base here.";
}

void Base::buildUnit()
{
    std::shared_ptr<GameEventHandler> handler =
            std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
    handler->addUnit<Builder>(lockObjectManager()->getTile(getCoordinate())->ID);
}

