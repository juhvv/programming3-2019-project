#include "gamefarm.h"
#include "ui/customgraphicsscene.h"
#include "core/playerbase.h"

Farm::Farm(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                 const std::shared_ptr<Course::iObjectManager> &objectmanager,
                 const std::shared_ptr<Course::PlayerBase> &owner,
                 CustomGraphicsScene *scene,
                 const int &tilespaces,
                 const Course::ResourceMap &buildcost,
                 const Course::ResourceMap &production) :
    GameBuildingBase (eventhandler, objectmanager, owner, scene, tilespaces, buildcost, production)
{

}

void Farm::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    GameBuildingBase::setGraphicsItem(graphicsItem, scene);

    graphicsItem_->setPixmap(QPixmap(":/resources/buildings/farm.PNG"));
    graphicsItem_->setZValue(3);
}

std::string Farm::getType() const
{
    return "Farm";
}

void Farm::getDescriptionBrief(std::string &desc)
{
    desc += "\n " + getOwner()->getName() + " has built a farm here.";
}
