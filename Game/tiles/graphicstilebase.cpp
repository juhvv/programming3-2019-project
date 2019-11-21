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
                                   const QPixmap &pixmap,
                                   QGraphicsItem *parent,
                                   const unsigned int& max_build,
                                   const unsigned int& max_work,
                                   const Course::ResourceMap& production) :
    CustomGraphicsItem (pixmap, parent),
    Course::TileBase (location, eventhandler, objectmanager, max_build, max_work, production),
    eventhandlerProtected_(eventhandler)
{
    setOffset(5,5);
}

QPainterPath GraphicsTileBase::shape() const
{
    QRectF shapeRect = QRectF(0,0, TILE_SIZE, TILE_SIZE);
    QPainterPath shapePath;
    shapePath.addRect(shapeRect);
    return shapePath;
}

void GraphicsTileBase::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *infoAction = menu.addAction("Info");
    menu.addSeparator();
    QAction *moveAction = menu.addAction("Move");
    QAction *claimAction = menu.addAction("Claim");
    connect(infoAction, &QAction::triggered, this, &GraphicsTileBase::sendInfo);
    connect(moveAction, SIGNAL(triggered()), this, SLOT(move()));
    connect(claimAction, &QAction::triggered, this, &GraphicsTileBase::sendPtr);
    menu.exec(event->screenPos());
}

void GraphicsTileBase::sendInfo()
{
    qDebug() << "BoundingRect: " << boundingRect();
    //qDebug() << "Shape: " << shape().boundingRect();
    // qDebug() << "Type: " << getType().c_str();
    qDebug() << "Loc " << x() << ", " << y();
    qDebug() << "ID: " << this->ID;
}

void GraphicsTileBase::sendPtr()
{
    qDebug() << "sending ptr";
    Course::iGameEventHandler* rwPtr = eventhandlerProtected_.get();
    GameEventHandler* eventHndlr = static_cast<GameEventHandler*>(rwPtr);
    eventHndlr->claimTile(this);

}

