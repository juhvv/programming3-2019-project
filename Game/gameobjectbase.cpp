#include "gameobjectbase.h"
#include "ui/customgraphicsitem.h"

GameObjectBase::GameObjectBase(CustomGraphicsScene *scene):
    scene_(scene)
{

}

GameObjectBase::~GameObjectBase()
{

}

void GameObjectBase::getMenuItems(QMenu &menu)
{

}

bool GameObjectBase::getIsMovable() const
{
    return isMovable_;
}

bool GameObjectBase::getIsSelectable() const
{
    return isSelectable_;
}

void GameObjectBase::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{

}
