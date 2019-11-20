#include "graphicstilebase.h"
#include <QtDebug>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

GraphicsTileBase::GraphicsTileBase(const Course::Coordinate& location,
                                   const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                                   const std::shared_ptr<Course::iObjectManager>& objectmanager,
                                   const QPixmap &pixmap,
                                   QGraphicsItem *parent,
                                   const unsigned int& max_build,
                                   const unsigned int& max_work,
                                   const Course::ResourceMap& production) :
    CustomGraphicsItem (pixmap, parent),
    Course::TileBase (location, eventhandler, objectmanager, max_build, max_work, production)

{
    setOffset(5,5);
}



QRectF GraphicsTileBase::boundingRect() const
{
    QRectF boundingRect = QRectF(0,0, TILE_SIZE, TILE_SIZE);
    return boundingRect;
}

void GraphicsTileBase::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *infoAction = menu.addAction("Info");
    QAction *moveAction = menu.addAction("Move");
    connect(infoAction, &QAction::triggered, this, &GraphicsTileBase::sendInfo);
    connect(moveAction, SIGNAL(triggered()), this, SLOT(move()));
    menu.exec(event->screenPos());
}

void GraphicsTileBase::sendInfo()
{
    qDebug() << "BoundingRect: " << boundingRect();
    qDebug() << "Shape: " << shape().boundingRect();
    qDebug() << "Type: " << getType().c_str();
}

