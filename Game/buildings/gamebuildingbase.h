#ifndef GAMEBUILDINGBASE_H
#define GAMEBUILDINGBASE_H

#include "buildings/buildingbase.h"
#include "gameobjectbase.h"
//#include "ui/customgraphicsscene.h"
//#include "units/graphicsunitbase.h"
#include "gameresourcemaps.hh"

class GameBuildingBase : public GameObjectBase, public Course::BuildingBase
{
public:
    GameBuildingBase() = delete;

    explicit GameBuildingBase(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            CustomGraphicsScene* scene = nullptr,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = {},
            const Course::ResourceMap& production = {}
            );

    virtual ~GameBuildingBase() = default;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    virtual void getMenuItems(QMenu &menu) override;

    virtual void getDescriptionBrief(std::string &desc) override;
};

#endif // GAMEBUILDINGBASE_H
