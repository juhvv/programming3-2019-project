#include "customgraphicsitem.h"

CustomGraphicsItem::CustomGraphicsItem(const QPixmap &pixmap, QGraphicsItem *parent) :
    QGraphicsPixmapItem (pixmap, parent)
{
    setFlag(CustomGraphicsItem::ItemIsMovable, true);
}


QPainterPath CustomGraphicsItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void CustomGraphicsItem::move()
{
    QPointF newPoint = QPointF(x()+1, y()+1);
    this->setPos(newPoint);
}

