#ifndef BUILDER_H
#define BUILDER_H

#include "units/graphicsunitbase.h"
#include "gameeventhandler.hh"


class Builder : public GraphicsUnitBase
{
public:
    Builder() = delete ;
    explicit Builder(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                        const std::shared_ptr<Course::iObjectManager>& objectmanager,
                        const std::shared_ptr<Course::PlayerBase>& owner,
                        CustomGraphicsScene* scene = nullptr,
                        const int& tilespaces = 1,
                        const Course::ResourceMap& cost = GameConstResourceMaps::BUILDER_COST,
                        const Course::ResourceMapDouble& efficiency = {});

    virtual ~Builder() = default;

    virtual void getMenuItems(QMenu &menu) override;

    virtual void getBuildMenu(QMenu &bmenu);

    virtual void switchTurn() override;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    virtual std::string getType() const override;

    virtual void getDescriptionBrief(std::string &desc) override;

private slots:

    template<typename BuildingType>
    void buildSlot() {
        std::shared_ptr<GameEventHandler> handler =
                std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());


        handler->addBuilding<BuildingType>(getCurrentTile(),
                                           std::dynamic_pointer_cast<Player>(getOwner()));
        movePoints_ = 0;
    }
};

#endif // BUILDER_H
