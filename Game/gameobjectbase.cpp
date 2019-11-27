#include "gameobjectbase.h"
#include "ui/customgraphicsitem.h"

GameObjectBase::GameObjectBase(CustomGraphicsScene *scene):
    scene_(scene)
{

}

GameObjectBase::~GameObjectBase()
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
