#include "foresttileitem.h"


ForestTileItem::ForestTileItem(const Course::Coordinate &location,
                               const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                               const std::shared_ptr<Course::iObjectManager> &objectmanager,
                               const QPixmap &pixmap,
                               QGraphicsItem *parent,
                               const unsigned int &max_build,
                               const unsigned int &max_work,
                               const Course::ResourceMap &production) :
    GraphicsTileBase (location, eventhandler, objectmanager, pixmap,parent,
                      max_build, max_work, production)
{
    setOffset(-10,-10);
}

QRectF ForestTileItem::boundingRect() const
{
    QRectF boundingRect = QRectF(0, 0, TILE_SIZE, TILE_SIZE);
    return boundingRect;
}

std::string ForestTileItem::getType() const
{
    return "Forest Tile";
}
