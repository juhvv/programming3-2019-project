#include "builder.h"
#include "gameeventhandler.hh"

#include "buildings/sawmill.h"
#include "buildings/goldmine.h"
#include "buildings/gamefarm.h"


Builder::Builder(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                 const std::shared_ptr<Course::iObjectManager> &objectmanager,
                 const std::shared_ptr<Course::PlayerBase> &owner,
                 CustomGraphicsScene *scene,
                 const int &tilespaces,
                 const Course::ResourceMap &cost,
                 const Course::ResourceMapDouble &efficiency) :
    GraphicsUnitBase (eventhandler, objectmanager, owner, scene, tilespaces, cost, efficiency)
{
    movePoints_ = Units::BASICRANGE;
}

void Builder::getMenuItems(QMenu &menu)
{
    GraphicsUnitBase::getMenuItems(menu);
    if (std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler())->getCurrentPlayer() == getOwner()) {
        QMenu* buildMenu = menu.addMenu("Build");
        if (getCurrentTile()->getBuildingCount() == 0
                && !getCurrentTile()->hasTag(objectTags::NO_BUILD)
                && getCurrentTile()->getOwner() == getOwner()) {
            //connect(buildAction, &QAction::triggered, this, &Builder::buildActionSlot);
            getBuildMenu(*buildMenu);

        } else {
            buildMenu->setTitle("Build - Can't build here");
            buildMenu->setDisabled(true);
        }
    }
}

void Builder::getBuildMenu(QMenu &bmenu)
{
    std::shared_ptr<GraphicsTileBase> curTile = getCurrentTile();
    QAction* buildFarmAction = bmenu.addAction("Build farm");
    QAction* buildSwmillAction = bmenu.addAction("Build sawmill");
    QAction* buildMineAction = bmenu.addAction("Build goldmine");

    if (curTile->hasTag(objectTags::IS_FLAT)) {
        connect(buildFarmAction, &QAction::triggered, this, &Builder::buildSlot<Farm>);

    } else {
        buildFarmAction->setText("Can't build a farm here.");
        buildFarmAction->setDisabled(true);
    }

    if (curTile->hasTag(objectTags::HAS_TREES)) {
        connect(buildSwmillAction, &QAction::triggered, this, &Builder::buildSlot<SawMill>);

    } else {
        buildSwmillAction->setText("Can't build a sawmill here.");
        buildSwmillAction->setDisabled(true);
    }

    if (curTile->hasTag(objectTags::HAS_ROCK)) {
        connect(buildMineAction, &QAction::triggered, this, &Builder::buildSlot<GoldMine>);

    } else {
        buildMineAction->setText("Can't build a goldmine here.");
        buildMineAction->setDisabled(true);
    }

}

void Builder::doSpecialAction()
{

}

void Builder::switchTurn()
{
    GraphicsUnitBase::switchTurn();
    movePoints_ = Units::BASICRANGE;
}

void Builder::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    GraphicsUnitBase::setGraphicsItem(graphicsItem, scene);
    graphicsItem_->setPixmap(QPixmap(":/resources/units/worker.PNG"));
    scene_->update();
}

std::string Builder::getType() const
{
    return "Builder";
}

void Builder::getDescriptionBrief(std::string &desc)
{
    desc += "\n Pete the builder.";
}

void Builder::buildActionSlot()
{
    std::shared_ptr<GameEventHandler> handler =
            std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
    handler->addBuilding<SawMill>(std::dynamic_pointer_cast<GraphicsTileBase>
                                  (lockObjectManager()->getTile(getCoordinate())));
}
