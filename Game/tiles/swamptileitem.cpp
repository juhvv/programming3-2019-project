#include "swamptileitem.h"
#include "ui/customgraphicsscene.h"

SwampTileItem::SwampTileItem(const Course::Coordinate &location,
                                   const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                                   const std::shared_ptr<Course::iObjectManager> &objectmanager,
                                   CustomGraphicsScene* scene,
                                   const unsigned int &max_build,
                                   const unsigned int &max_work,
                                   const Course::ResourceMap &production) :
    GraphicsTileBase (location, eventhandler, objectmanager, scene,  max_build, max_work, production)
{
    tags_ = {objectTags::IS_FLAT};
}

unsigned int SwampTileItem::getMovementCost()  const
{
    return 2;
}

std::string SwampTileItem::getType() const
{
    return "Swamp tile";
}

void SwampTileItem::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    graphicsItem_ = graphicsItem;
    scene_ = scene;

    graphicsItem_->setPixmap(QPixmap(":/resources/swamp.PNG"));
    graphicsItem_->setOffset(-5,-5);
    graphicsItem_->setZValue(2);
    scene_->update();
}

void SwampTileItem::getDescriptionBrief(std::string &desc)
{
    desc += "\n Swampy terrain. But where is Jussi?";
}
