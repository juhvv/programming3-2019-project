#include "goldmine.h"
#include "ui/customgraphicsscene.h"
#include "core/playerbase.h"

GoldMine::GoldMine(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                 const std::shared_ptr<Course::iObjectManager> &objectmanager,
                 const std::shared_ptr<Course::PlayerBase> &owner,
                 CustomGraphicsScene *scene,
                 const int &tilespaces,
                 const Course::ResourceMap &buildcost,
                 const Course::ResourceMap &production) :
    GameBuildingBase (eventhandler, objectmanager, owner, scene, tilespaces, buildcost, production)
{

}

void GoldMine::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    GameBuildingBase::setGraphicsItem(graphicsItem, scene);

    graphicsItem_->setPixmap(QPixmap(":/resources/buildings/sawmill.png"));
}

std::string GoldMine::getType() const
{
    return "Gold mine";
}

void GoldMine::getDescriptionBrief(std::string &desc)
{
    desc += "\n " + getOwner()->getName() + " has built a gold mine here.";
}
