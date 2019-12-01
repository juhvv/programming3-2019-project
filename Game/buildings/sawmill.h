#ifndef SAWMILL_H
#define SAWMILL_H

#include "buildings/gamebuildingbase.h"

const Course::ResourceMap SAWMILL_BUILD_COST = {
    {Course::BasicResource::MONEY, 50},
    {Course::BasicResource::FOOD, 100},
    {Course::BasicResource::WOOD, 25}
};
const Course::ResourceMap SAWMILL_PRODUCTION = {
    {Course::BasicResource::MONEY, 1},
    {Course::BasicResource::WOOD, 5}
};

class SawMill : public GameBuildingBase
{
public:
    SawMill() = delete;

    explicit SawMill(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            CustomGraphicsScene* scene = nullptr,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = SAWMILL_BUILD_COST,
            const Course::ResourceMap& production = SAWMILL_PRODUCTION
            );

    virtual ~SawMill() = default;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    virtual std::string getType() const override;

    virtual void getDescriptionBrief(std::string &desc) override;
};

#endif // SAWMILL_H
