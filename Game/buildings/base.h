#ifndef BASE_H
#define BASE_H

#include "buildings/gamebuildingbase.h"
#include "core/resourcemaps.h"

class Base : public GameBuildingBase
{
public:
    Base() = delete;

    explicit Base(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            CustomGraphicsScene* scene = nullptr,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = Course::ConstResourceMaps::HQ_BUILD_COST,
            const Course::ResourceMap& production = Course::ConstResourceMaps::HQ_PRODUCTION
            );

    virtual ~Base() = default;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    virtual void getMenuItems(QMenu &menu) override;

    virtual std::string getType() const override;

    virtual void getDescriptionBrief(std::string &desc) override;

public slots:
    virtual void buildUnit();
};

#endif // BASE_H
