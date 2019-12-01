#ifndef WORKER_H
#define WORKER_H

#include "units/graphicsunitbase.h"

class Worker : public GraphicsUnitBase
{
public:
    Worker() = delete ;
    explicit Worker(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                        const std::shared_ptr<Course::iObjectManager>& objectmanager,
                        const std::shared_ptr<Course::PlayerBase>& owner,
                        CustomGraphicsScene* scene = nullptr,
                        const int& tilespaces = 1,
                        const Course::ResourceMap& cost = {},
                        const Course::ResourceMapDouble& efficiency = {});

    virtual ~Worker() = default;

    // virtual void getMenuItems(QMenu &menu) override;

    // virtual void doSpecialAction() override;

    // virtual unsigned int getMovePoints();

    virtual bool moveToTile(std::shared_ptr<GraphicsTileBase> tileToMoveTo,
                            bool ignoreMovePoints = false) override;

    virtual bool canMoveToTile(GraphicsTileBase* tileToMoveTo) override;

    virtual void switchTurn() override;

    // virtual bool isSelectable() const override;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    // virtual void cancelMovement();
    virtual std::string getType() const override;

    virtual void getDescriptionBrief(std::string &desc) override;
};

#endif // WORKER_H
