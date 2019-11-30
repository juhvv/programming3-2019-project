#include "mountaintileitem.h"
#include "ui/customgraphicsscene.h"



MountainTileItem::MountainTileItem(const Course::Coordinate &location,
                                   const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                                   const std::shared_ptr<Course::iObjectManager> &objectmanager,
                                   CustomGraphicsScene* scene,
                                   const unsigned int &max_build,
                                   const unsigned int &max_work,
                                   const Course::ResourceMap &production) :
    GraphicsTileBase (location, eventhandler, objectmanager, scene,  max_build, max_work, production)
{
    //graphicsItem_->setOffset(-5,-50);
    //graphicsItem_->setZValue(2);
    tags_ = {objectTags::HAS_ROCK};
}

unsigned int MountainTileItem::getMovementCost()  const
{
    return 2;
}

std::string MountainTileItem::getType() const
{
    return "Mountain tile";
}

void MountainTileItem::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
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
    graphicsItem_->setPixmap(QPixmap(":/resources/mountains.PNG"));
    graphicsItem_->setOffset(-10,-50);
    graphicsItem_->setZValue(2);
    scene_->update();
}

void MountainTileItem::getDescriptionBrief(std::string &desc)
{
    desc += "\n Hard to traverse, but essential for obtaining precious metals.";
}
