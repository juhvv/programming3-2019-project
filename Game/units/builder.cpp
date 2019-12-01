#include "builder.h"
#include "gameeventhandler.hh"

#include "buildings/sawmill.h"
#include "buildings/goldmine.h"


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
        QAction* buildAction = menu.addAction("Build");
        if (getCurrentTile()->getBuildingCount() == 0
                && !getCurrentTile()->hasTag(objectTags::NO_BUILD)
                && getCurrentTile()->getOwner() == getOwner()) {
            connect(buildAction, &QAction::triggered, this, &Builder::buildActionSlot);
        } else {
            buildAction->setText("Build - Can't build here");
            buildAction->setDisabled(true);
        }

    }
}

void Builder::doSpecialAction()
{

}

void Builder::switchTurn()
{
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
