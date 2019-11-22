#include "customgraphicsitem.h"

CustomGraphicsItem::CustomGraphicsItem(const QPixmap &pixmap, QGraphicsItem *parent) :
    QGraphicsPixmapItem (pixmap, parent)
{

}


QPainterPath CustomGraphicsItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

bool CustomGraphicsItem::isMovable()
{
    return true;
}
/*
void CustomGraphicsItem::showContextMenu(QGraphicsSceneContextMenuEvent *contextEvent)
{
    contextMenuEvent(contextEvent);
}
*/
void CustomGraphicsItem::move()
{
    QPointF newPoint = QPointF(x()+1, y()+1);
    this->setPos(newPoint);
}

