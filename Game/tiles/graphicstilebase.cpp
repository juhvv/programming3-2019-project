#include "graphicstilebase.h"
#include <QtDebug>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QLabel>
#include <QWidgetAction>
#include "gameeventhandler.hh"
#include "ui/customgraphicsscene.h"

GraphicsTileBase::GraphicsTileBase(const Course::Coordinate& location,
                                   const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                                   const std::shared_ptr<Course::iObjectManager>& objectmanager,
                                   CustomGraphicsScene* scene,
                                   const unsigned int& max_build,
                                   const unsigned int& max_work,
                                   const Course::ResourceMap& production) :
    GameObjectBase(scene),
    Course::TileBase (location, eventhandler, objectmanager, max_build, max_work, production)
{

}

void GraphicsTileBase::getMenuItems(QMenu &menu)
{

    QAction *infoAction = menu.addAction("Info");
    if (std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler())->getCurrentPlayer() == getOwner()
            || getOwner() == nullptr) {
        menu.addSeparator();

        for (auto building : getBuildings()) {
            std::shared_ptr<GameBuildingBase> buildingPtr = std::dynamic_pointer_cast<GameBuildingBase>(building);
            buildingPtr->getMenuItems(menu);
        }
    }

    connect(infoAction, &QAction::triggered, this, &GraphicsTileBase::sendInfo);

}

bool GraphicsTileBase::isSelectable() const
{
    return true;
    /*
    std::shared_ptr<GameEventHandler> eventHndlr =
            std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
    return !(eventHndlr->getCurrentPlayer() != getOwner() && getOwner() != nullptr);
    */
}

bool GraphicsTileBase::isMovable() const
{
    return false;
}

unsigned int GraphicsTileBase::getMovementCost() const
{
    return 1;
}

void GraphicsTileBase::addUnit(GraphicsUnitBase *unit)
{
    std::shared_ptr<GraphicsUnitBase> unitShrd =
            std::dynamic_pointer_cast<Player>(unit->getOwner())->getUnitById(unit->ID);
    if (unitShrd != nullptr) {
        Course::TileBase::addWorker(unitShrd);
    }
}

void GraphicsTileBase::removeUnit(GraphicsUnitBase *unit)
{
    std::shared_ptr<GraphicsUnitBase> unitShrd =
            std::dynamic_pointer_cast<Player>(unit->getOwner())->getUnitById(unit->ID);
    if (unitShrd != nullptr) {
        Course::TileBase::removeWorker(unitShrd);
    }
}

bool GraphicsTileBase::generateResources()
{
    return true;
}

Course::ResourceMap GraphicsTileBase::generatedResources(std::shared_ptr<Player> &currentPlayer)
{
    Course::ResourceMap tileNetProduction;
    Course::ResourceMap unitConsumption = GameConstResourceMaps::UNIT_CONSUMPTION;
    bool doesTileHaveWorker = false;
    for(long unsigned int i=0; i<getWorkers().size(); i++){
        tileNetProduction = Course::mergeResourceMaps(tileNetProduction, unitConsumption);
        if(getWorkers()[i]->getType()=="Worker"){
            doesTileHaveWorker = true;
        }
    }
    if(doesTileHaveWorker){
        if(getBuildings().size()>0){
            tileNetProduction = Course::mergeResourceMaps(tileNetProduction, getBuildings()[0]->getProduction());
        }
        else if(getOwner() == currentPlayer){
            tileNetProduction = Course::mergeResourceMaps(tileNetProduction, BASE_PRODUCTION);
        }
    }
    return tileNetProduction;
}

void GraphicsTileBase::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    graphicsItem_ = graphicsItem;
    scene_ = scene;

    graphicsItem_->setShapePref(shapePrefs::SQUARE_128);
}

QPointF GraphicsTileBase::getSceneCoord() const
{
    return graphicsItem_->pos();
}

void GraphicsTileBase::sendInfo()
{
    qDebug() << "Loc " << graphicsItem_->x() << ", " << graphicsItem_->y();
    qDebug() << "ID: " << this->ID;

    std::string infoMsg = getType();
    if (getOwner()) { infoMsg += " of " + getOwner()->getName();}
    getDescriptionBrief(infoMsg);
    for (auto building : getBuildings()) {
        std::dynamic_pointer_cast<GameBuildingBase>(building)->getDescriptionBrief(infoMsg);
    }

    std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler())->sendMsg(infoMsg);
}

void GraphicsTileBase::claimTile()
{
    /*
    std::shared_ptr<GameEventHandler> eventHndlr =
            std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
    eventHndlr->claimTile(this);*/
}


