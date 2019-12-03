#ifndef SCOUT_H
#define SCOUT_H

#include "units/graphicsunitbase.h"

class Scout : public GraphicsUnitBase
{
public:
    Scout() = delete ;
    explicit Scout(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                        const std::shared_ptr<Course::iObjectManager>& objectmanager,
                        const std::shared_ptr<Course::PlayerBase>& owner,
                        CustomGraphicsScene* scene = nullptr,
                        const int& tilespaces = 1,
                        const Course::ResourceMap& cost = GameConstResourceMaps::SCOUT_COST,
                        const Course::ResourceMapDouble& efficiency = {});

    virtual ~Scout() = default;

    virtual void getMenuItems(QMenu &menu) override;

    virtual void switchTurn() override;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    virtual std::string getType() const override;

    virtual void getDescriptionBrief(std::string &desc) override;

private slots:
    void claimActionSlot();
    void buildCampActionSlot();
};

#endif // SCOUT_H
