#ifndef BASE_H
#define BASE_H

#include "buildings/gamebuildingbase.h"
#include "gameresourcemaps.hh"
#include "gameeventhandler.hh"

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
            const Course::ResourceMap& buildcost = GameConstResourceMaps::HQ_BUILD_COST,
            const Course::ResourceMap& production = GameConstResourceMaps::HQ_PRODUCTION
            );

    virtual ~Base() = default;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    virtual void getMenuItems(QMenu &menu) override;

    virtual void getBuildMenu(QMenu &bmenu);

    virtual std::string getType() const override;

    virtual void getDescriptionBrief(std::string &desc) override;

public slots:
    virtual void buildUnit();

    template<typename UnitType>
    void hireUnitSlot() {
        std::shared_ptr<GameEventHandler> handler =
                std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
        std::shared_ptr<ObjectManager> manager =
                std::dynamic_pointer_cast<ObjectManager>(lockObjectManager());

        handler->addUnit<UnitType>(manager->getGTile(getCoordinate()),
                                   std::dynamic_pointer_cast<Player>(getOwner()));
    }
};

#endif // BASE_H