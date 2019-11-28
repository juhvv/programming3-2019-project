#include "foresttileitem.h"


ForestTileItem::ForestTileItem(const Course::Coordinate &location,
                               const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                               const std::shared_ptr<Course::iObjectManager> &objectmanager,
                               CustomGraphicsScene *scene,
                               const unsigned int &max_build,
                               const unsigned int &max_work,
                               const Course::ResourceMap &production) :
    GraphicsTileBase (location, eventhandler, objectmanager, scene, max_build, max_work, production)
{
    //graphicsItem_->setOffset(-10,-10);
    //graphicsItem_->setZValue(2);
}

unsigned int ForestTileItem::getMovementCost()
{
    return 2;
}

void ForestTileItem::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    //graphicsItem_ = graphicsItem;
    //scene_ = scene;

    GraphicsTileBase::setGraphicsItem(graphicsItem, scene);

    //graphicsObject_->setPixmap(QPixmap(":/resources/tilebase.PNG"));
    /*
    qreal newX = this->getCoordinate().x() * TILE_SIZE;
    qreal newY = this->getCoordinate().y() * TILE_SIZE;

    scene_->addItem(graphicsItem_);
    graphicsItem_->setPos(newX, newY);
    */
    graphicsItem_->setPixmap(QPixmap(":/resources/forest.PNG"));
    graphicsItem_->setOffset(-10,-50);
    graphicsItem_->setZValue(2);
    // scene_->update();
}

std::string ForestTileItem::getType() const
{
    return "Forest Tile";
}

