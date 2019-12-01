#include "gamebuildingbase.h"
#include "gameeventhandler.hh"
#include "ui/customgraphicsitem.h"
#include "ui/customgraphicsscene.h"

GameBuildingBase::GameBuildingBase(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                                   const std::shared_ptr<Course::iObjectManager> &objectmanager,
                                   const std::shared_ptr<Course::PlayerBase> &owner,
                                   CustomGraphicsScene *scene,
                                   const int &tilespaces,
                                   const Course::ResourceMap &buildcost,
                                   const Course::ResourceMap &production) :
    GameObjectBase(scene),
    Course::BuildingBase (eventhandler, objectmanager,owner, tilespaces, buildcost, production)
{

}

void GameBuildingBase::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    graphicsItem_ = graphicsItem;
    scene_ = scene;

    graphicsItem_->setShapePref(shapePrefs::NO_SHAPE);
    graphicsItem_->setPixmap(QPixmap(":/resources/buildings/base.PNG"));


    qreal newX = this->getCoordinate().x() * TILE_SIZE;
    qreal newY = this->getCoordinate().y() * TILE_SIZE;

    scene_->addItem(graphicsItem_);
    graphicsItem_->setZValue(6);
    graphicsItem_->setPos(newX, newY);


    scene_->update();
}

void GameBuildingBase::getMenuItems(QMenu &menu)
{
    // implement actions for all buildings here
}

void GameBuildingBase::getDescriptionBrief(std::string &desc)
{
    desc += "\n " + getOwner()->getName() + " has built their base here.";
}
