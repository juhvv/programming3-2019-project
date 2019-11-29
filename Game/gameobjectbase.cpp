#include "gameobjectbase.h"
#include "ui/customgraphicsitem.h"
#include "ui/customgraphicsscene.h"

GameObjectBase::GameObjectBase(CustomGraphicsScene *scene):
    scene_(scene)
{

}

GameObjectBase::~GameObjectBase()
{
    // delete graphicsitem if it is not yet deleted
    if (scene_ != nullptr && graphicsItem_ !=nullptr) {
        scene_->removeItem(graphicsItem_);
        delete graphicsItem_;
    }
}

void GameObjectBase::getMenuItems(QMenu &menu)
{

}

bool GameObjectBase::isMovable() const
{
    return true;
}

bool GameObjectBase::isSelectable() const
{
    return false;
}

void GameObjectBase::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{

}

void GameObjectBase::getDescriptionBrief(std::string &desc)
{
    desc += "baseObject";
}

void GameObjectBase::sendInfo()
{

}

CustomGraphicsItem *GameObjectBase::getGraphicsItem() const
{
    return graphicsItem_;
}
