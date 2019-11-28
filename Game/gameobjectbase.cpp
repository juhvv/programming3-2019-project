#include "gameobjectbase.h"
#include "ui/customgraphicsitem.h"
#include "ui/customgraphicsscene.h"

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

bool GameObjectBase::isMovable() const
{
    return true;
}

bool GameObjectBase::isSelectable() const
{
    return true;
}

void GameObjectBase::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{

}
