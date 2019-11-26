#include "watertileitem.h"



WaterTileItem::WaterTileItem(const Course::Coordinate &location,
                             const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                             const std::shared_ptr<Course::iObjectManager> &objectmanager,
                             const QPixmap &pixmap,
                             QGraphicsItem *parent,
                             const unsigned int &max_build,
                             const unsigned int &max_work,
                             const Course::ResourceMap &production) :
    GraphicsTileBase (location, eventhandler, objectmanager, pixmap, parent, max_build, max_work, production)
{
    // setOffset(-5,-5);
    // setZValue(1);
}

std::string WaterTileItem::getType() const
{
    return "Water tile";
}