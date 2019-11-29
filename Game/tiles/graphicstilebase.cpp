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
    Course::TileBase (location, eventhandler, objectmanager, max_build, max_work, production),
    eventhandlerProtected_(eventhandler)
{

}

Course::iGameEventHandler *GraphicsTileBase::getEventHandlerPtr() const
{

    return eventhandlerProtected_.get();
}

void GraphicsTileBase::getMenuItems(QMenu &menu)
{

    QAction *infoAction = menu.addAction("Info");
    menu.addSeparator();
    // tile can only be claimed if it has no owner
    if (getOwner() == nullptr) {
        QAction *claimAction = menu.addAction("Claim");
        connect(claimAction, &QAction::triggered, this, &GraphicsTileBase::claimTile);
    }
    for (auto building : getBuildings()) {
        std::shared_ptr<GameBuildingBase> buildingPtr = std::dynamic_pointer_cast<GameBuildingBase>(building);
        buildingPtr->getMenuItems(menu);
    }
    connect(infoAction, &QAction::triggered, this, &GraphicsTileBase::sendInfo);

}

bool GraphicsTileBase::isSelectable() const
{
    std::shared_ptr<GameEventHandler> eventHndlr =
            std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
    return !(eventHndlr->getCurrentPlayer() != getOwner() && getOwner() != nullptr);
}

bool GraphicsTileBase::isMovable() const
{
    return false;
}

unsigned int GraphicsTileBase::getMovementCost() const
{
    return 1;
}

void GraphicsTileBase::addBuilding(const std::shared_ptr<GameBuildingBase> &building)
{
    std::shared_ptr<Course::BuildingBase> newBuilding =
            std::dynamic_pointer_cast<Course::BuildingBase>(building);
    TileBase::addBuilding(newBuilding);
}

bool GraphicsTileBase::generateResources()
{
    return true;
}

Course::ResourceMap GraphicsTileBase::generatedResources()
{
    Course::ResourceMapDouble worker_efficiency;
    Course::ResourceMap total_production;

    for( auto work_it = m_workers.begin();
         work_it != m_workers.end();
         ++work_it)
    {
        Course::ResourceMapDouble current_efficiency = work_it->lock()->tileWorkAction();

        worker_efficiency = Course::mergeResourceMapDoubles(worker_efficiency, current_efficiency);
    }

    total_production = Course::multiplyResourceMap(BASE_PRODUCTION, worker_efficiency);

    for( auto build_it = m_buildings.begin();
         build_it != m_buildings.end();
         ++build_it)
    {
        Course::ResourceMap current_production = build_it->lock()->getProduction();

        total_production = Course::mergeResourceMaps(total_production,
                                             current_production);
    }



    return total_production;
}

void GraphicsTileBase::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    graphicsItem_ = graphicsItem;
    scene_ = scene;

    graphicsItem_->setShapePref(SQUARE_128);

    //graphicsObject_->setPixmap(QPixmap(":/resources/tilebase.PNG"));
    /*
    qreal newX = this->getCoordinate().x() * TILE_SIZE;
    qreal newY = this->getCoordinate().y() * TILE_SIZE;

    scene_->addItem(graphicsItem_);
    graphicsItem_->setPos(newX, newY);
    */
    // graphicsObject_->setPixmap(QPixmap(":/resources/tilebase.PNG"));
    // scene_->update();
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
    std::shared_ptr<GameEventHandler> eventHndlr =
            std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
    // Course::iGameEventHandler* rwPtr = eventhandlerProtected_.get();
    // GameEventHandler* eventHndlr = static_cast<GameEventHandler*>(rwPtr);
    eventHndlr->claimTile(this);
}

