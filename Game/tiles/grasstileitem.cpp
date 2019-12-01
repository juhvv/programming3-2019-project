#include "grasstileitem.h"
#include "ui/customgraphicsscene.h"



GrassTileItem::GrassTileItem(const Course::Coordinate &location,
                             const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                             const std::shared_ptr<Course::iObjectManager> &objectmanager,
                             CustomGraphicsScene* scene,
                             const unsigned int &max_build,
                             const unsigned int &max_work,
                             const Course::ResourceMap &production) :
    GraphicsTileBase (location, eventhandler, objectmanager, scene, max_build, max_work, production)
{
    //graphicsItem_->setOffset(-5,-5);
    //graphicsItem_->setZValue(1);
    tags_ = {objectTags::IS_FLAT};
}

unsigned int GrassTileItem::getMovementCost()  const
{
    return 1;
}

std::string GrassTileItem::getType() const
{
    return "Grass tile";
}

void GrassTileItem::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
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
    graphicsItem_->setPixmap(QPixmap(":/resources/grass.PNG"));
    graphicsItem_->setOffset(-5,-5);
    graphicsItem_->setZValue(1);
    scene_->update();
}

void GrassTileItem::getDescriptionBrief(std::string &desc)
{
    desc += "\n Lots of grass.";
}

