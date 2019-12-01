#include "sawmill.h"
#include "ui/customgraphicsscene.h"
#include "core/playerbase.h"


SawMill::SawMill(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                 const std::shared_ptr<Course::iObjectManager> &objectmanager,
                 const std::shared_ptr<Course::PlayerBase> &owner,
                 CustomGraphicsScene *scene,
                 const int &tilespaces,
                 const Course::ResourceMap &buildcost,
                 const Course::ResourceMap &production) :
    GameBuildingBase (eventhandler, objectmanager, owner, scene, tilespaces, buildcost, production)
{

}

void SawMill::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    GameBuildingBase::setGraphicsItem(graphicsItem, scene);

    graphicsItem_->setPixmap(QPixmap(":/resources/buildings/sawmill.png"));
}

std::string SawMill::getType() const
{
    return "Sawmill";
}

void SawMill::getDescriptionBrief(std::string &desc)
{
    desc += "\n " + getOwner()->getName() + " has built a sawmill here.";
}
