#include "watertileitem.h"



WaterTileItem::WaterTileItem(const Course::Coordinate &location,
                             const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                             const std::shared_ptr<Course::iObjectManager> &objectmanager,
                             CustomGraphicsScene* scene,
                             const unsigned int &max_build,
                             const unsigned int &max_work,
                             const Course::ResourceMap &production) :
    GraphicsTileBase (location, eventhandler, objectmanager, scene, max_build, max_work, production)
{
    // setOffset(-5,-5);
    // setZValue(1);
}

unsigned int WaterTileItem::getMovementCost()
{
    return 2;
}

std::string WaterTileItem::getType() const
{
    return "Water tile";
}

void WaterTileItem::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
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
    graphicsItem_->setPixmap(QPixmap(":/resources/water.PNG"));
    // setOffset(-5,-5);
    // setZValue(1);
    scene_->update();
}
