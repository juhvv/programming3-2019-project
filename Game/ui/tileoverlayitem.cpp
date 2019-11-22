#include "tileoverlayitem.h"


TileOverlayItem::TileOverlayItem(const QPixmap &pixmap, QGraphicsItem *parent):
    QGraphicsPixmapItem (pixmap, parent)
{

}

QPainterPath TileOverlayItem::shape() const
{
    QRectF shapeRect = QRectF(0,0,0,0);
    QPainterPath shapePath;
    shapePath.addRect(shapeRect);
    return shapePath;
}
