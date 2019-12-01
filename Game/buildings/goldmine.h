#ifndef GOLDMINE_H
#define GOLDMINE_H

#include "buildings/gamebuildingbase.h"

const Course::ResourceMap GOLDMINE_BUILD_COST = {
    {Course::BasicResource::MONEY, 100},
    {Course::BasicResource::FOOD, 100},
    {Course::BasicResource::WOOD, 45}
};
const Course::ResourceMap GOLDMINE_PRODUCTION = {
    {Course::BasicResource::MONEY, 6},
    {Course::BasicResource::ORE, 4}
};

class GoldMine : public GameBuildingBase
{
public:
    GoldMine() = delete;

    explicit GoldMine(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            CustomGraphicsScene* scene = nullptr,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = GOLDMINE_BUILD_COST,
            const Course::ResourceMap& production = GOLDMINE_PRODUCTION
            );

    virtual ~GoldMine() = default;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    // virtual void getMenuItems(QMenu &menu) override;

    virtual std::string getType() const override;

    virtual void getDescriptionBrief(std::string &desc) override;
};

#endif // GOLDMINE_H
