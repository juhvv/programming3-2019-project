#include "scout.h"

#include "gameeventhandler.hh"
#include "buildings/base.h"



Scout::Scout(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
             const std::shared_ptr<Course::iObjectManager> &objectmanager,
             const std::shared_ptr<Course::PlayerBase> &owner,
             CustomGraphicsScene *scene,
             const int &tilespaces,
             const Course::ResourceMap &cost,
             const Course::ResourceMapDouble &efficiency) :
    GraphicsUnitBase (eventhandler, objectmanager, owner, scene, tilespaces, cost, efficiency)
{
    movePoints_ = Units::LONGRANGE;
}

void Scout::getMenuItems(QMenu &menu)
{
    GraphicsUnitBase::getMenuItems(menu);
    if (std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler())->getCurrentPlayer() == getOwner()) {
        QAction* claimAction = menu.addAction("Conquer tile");
        QAction* buildCampAction = menu.addAction("Build camp");

        if (getCurrentTile()->getOwner() == nullptr) {
            connect(claimAction, &QAction::triggered, this, &Scout::claimActionSlot);

        } else {
            claimAction->setText("Conquer tile - Tile already owned");
            claimAction->setDisabled(true);
        }

        if (getCurrentTile()->getBuildingCount() == 0
                && !getCurrentTile()->hasTag(objectTags::NO_BUILD)
                && getCurrentTile()->getOwner() == getOwner()) {
            connect(buildCampAction, &QAction::triggered, this, &Scout::buildCampActionSlot);
        } else {
            buildCampAction->setText("Build camp - Can't build here");
            buildCampAction->setDisabled(true);
        }

    }
}

void Scout::doSpecialAction()
{

}

void Scout::switchTurn()
{
    movePoints_ = Units::LONGRANGE;
}

void Scout::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    GraphicsUnitBase::setGraphicsItem(graphicsItem, scene);
    graphicsItem_->setPixmap(QPixmap(":/resources/units/scout.PNG"));
    scene_->update();
}

std::string Scout::getType() const
{
    return "Scout";
}

void Scout::getDescriptionBrief(std::string &desc)
{
    desc += "\n A true Eräjorma.";
}

void Scout::claimActionSlot()
{
    std::shared_ptr<GameEventHandler> handler =
            std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
    handler->claimTile(getCurrentTile().get());
    movePoints_ = 0;
}

void Scout::buildCampActionSlot()
{
    std::shared_ptr<GameEventHandler> handler =
            std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
    handler->addBuilding<Base>(std::dynamic_pointer_cast<GraphicsTileBase>
                                  (lockObjectManager()->getTile(getCoordinate())));

}
