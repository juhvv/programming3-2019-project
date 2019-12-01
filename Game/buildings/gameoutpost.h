#ifndef GAMEOUTPOST_H
#define GAMEOUTPOST_H

#include "gamebuildingbase.h"
#include "gameresourcemaps.hh"


class Outpost : public GameBuildingBase
{
public:
    Outpost() = delete;

    explicit Outpost(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            CustomGraphicsScene* scene = nullptr,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = GameConstResourceMaps::OUTPOST_BUILD_COST,
            const Course::ResourceMap& production = GameConstResourceMaps::OUTPOST_PRODUCTION
            );

    virtual ~Outpost() = default;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    virtual std::string getType() const override;

    virtual void getDescriptionBrief(std::string &desc) override;

    virtual void getMenuItems(QMenu &menu) override;

private slots:
    void hireWorkerSlot();
};
#endif // GAMEOUTPOST_H
