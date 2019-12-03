#include "foresttileitem.h"
#include "ui/customgraphicsscene.h"


ForestTileItem::ForestTileItem(const Course::Coordinate &location,
                               const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                               const std::shared_ptr<Course::iObjectManager> &objectmanager,
                               CustomGraphicsScene *scene,
                               const unsigned int &max_build,
                               const unsigned int &max_work,
                               const Course::ResourceMap &production) :
    GraphicsTileBase (location, eventhandler, objectmanager, scene, max_build, max_work, production)
{
    tags_ = {objectTags::HAS_TREES};
}

unsigned int ForestTileItem::getMovementCost() const
{
    return 2;
}

void ForestTileItem::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    GraphicsTileBase::setGraphicsItem(graphicsItem, scene);

    graphicsItem_->setPixmap(QPixmap(":/resources/forest.PNG"));
    graphicsItem_->setOffset(-10,-50);
    graphicsItem_->setZValue(4);
}

std::string ForestTileItem::getType() const
{
    return "Forest Tile";
}

void ForestTileItem::getDescriptionBrief(std::string &desc)
{
    desc += "\n Traditional Finnish boreal forest. Ideal for getting wood.";
}

