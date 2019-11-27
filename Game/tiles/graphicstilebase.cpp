#include "graphicstilebase.h"
#include <QtDebug>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QLabel>
#include <QWidgetAction>
#include "gameeventhandler.hh"

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
    // graphicsItem_->setOffset(5,5);
    // setFlag(QGraphicsItem::ItemIsSelectable, true);
}
/*
QPainterPath GraphicsTileBase::shape() const
{
    QRectF shapeRect = QRectF(0,0, TILE_SIZE, TILE_SIZE);
    QPainterPath shapePath;
    shapePath.addRect(shapeRect);
    return shapePath;
}
*/
Course::iGameEventHandler *GraphicsTileBase::getEventHandlerPtr() const
{

    return eventhandlerProtected_.get();
}

void GraphicsTileBase::getMenuItems(QMenu &menu)
{
    Course::iGameEventHandler* rwPtr = eventhandlerProtected_.get();
    GameEventHandler* eventHndlr = static_cast<GameEventHandler*>(rwPtr);

    QAction *infoAction = menu.addAction("Info");
    menu.addSeparator();
    // tile can only be claimed if it has no owner
    if (getOwner() == NULL) {
        QAction *claimAction = menu.addAction("Claim");
        connect(claimAction, &QAction::triggered, this, &GraphicsTileBase::sendPtr);
    }
    //QAction *claimAction = menu.addAction("Claim");
    connect(infoAction, &QAction::triggered, this, &GraphicsTileBase::sendInfo);
    // connect(claimAction, &QAction::triggered, this, &GraphicsTileBase::sendPtr);

}

bool GraphicsTileBase::getIsSelectable() const
{
    Course::iGameEventHandler* rwPtr = eventhandlerProtected_.get();
    GameEventHandler* eventHndlr = static_cast<GameEventHandler*>(rwPtr);
    return !(eventHndlr->getCurrentPlayer() != getOwner() && getOwner() != nullptr);
}

bool GraphicsTileBase::isMovable()
{
    return false;
}

unsigned int GraphicsTileBase::getMovementCost()
{
    return 1;
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

    //graphicsObject_->setPixmap(QPixmap(":/resources/tilebase.PNG"));
    /*
    qreal newX = this->getCoordinate().x() * TILE_SIZE;
    qreal newY = this->getCoordinate().y() * TILE_SIZE;

    scene_->addItem(graphicsItem_);
    graphicsItem_->setPos(newX, newY);
    */
    // graphicsObject_->setPixmap(QPixmap(":/resources/tilebase.PNG"));
    scene_->update();
}

QPointF GraphicsTileBase::getSceneCoord()
{
    return graphicsItem_->pos();
}



/*
void GraphicsTileBase::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

    Course::iGameEventHandler* rwPtr = eventhandlerProtected_.get();
    GameEventHandler* eventHndlr = static_cast<GameEventHandler*>(rwPtr);

    if (eventHndlr->getCurrentPlayer() != getOwner() && getOwner() != NULL) {
        return;
    }
    QMenu menu;
    QAction *infoAction = menu.addAction("Info");
    menu.addSeparator();
    QAction *moveAction = menu.addAction("Move");
    // tile can only be claimed if it has no owner
    if (getOwner() == NULL) {
        QAction *claimAction = menu.addAction("Claim");
        connect(claimAction, &QAction::triggered, this, &GraphicsTileBase::sendPtr);
    }
    //QAction *claimAction = menu.addAction("Claim");
    connect(infoAction, &QAction::triggered, this, &GraphicsTileBase::sendInfo);
    connect(moveAction, SIGNAL(triggered()), this, SLOT(move()));
    // connect(claimAction, &QAction::triggered, this, &GraphicsTileBase::sendPtr);
    menu.exec(event->screenPos());
}
*/
void GraphicsTileBase::sendInfo()
{
    // qDebug() << "BoundingRect: " << boundingRect();
    //qDebug() << "Shape: " << shape().boundingRect();
    // qDebug() << "Type: " << getType().c_str();
    qDebug() << "Loc " << graphicsItem_->x() << ", " << graphicsItem_->y();
    qDebug() << "ID: " << this->ID;
}

void GraphicsTileBase::sendPtr()
{
    Course::iGameEventHandler* rwPtr = eventhandlerProtected_.get();
    GameEventHandler* eventHndlr = static_cast<GameEventHandler*>(rwPtr);
    eventHndlr->claimTile(this);
}

