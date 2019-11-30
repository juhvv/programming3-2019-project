#ifndef BUILDER_H
#define BUILDER_H

#include "units/graphicsunitbase.h"


class Builder : public GraphicsUnitBase
{
public:
    Builder() = delete ;
    explicit Builder(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                        const std::shared_ptr<Course::iObjectManager>& objectmanager,
                        const std::shared_ptr<Course::PlayerBase>& owner,
                        CustomGraphicsScene* scene = nullptr,
                        const int& tilespaces = 1,
                        const Course::ResourceMap& cost = {},
                        const Course::ResourceMapDouble& efficiency = {});

    virtual ~Builder() = default;

    virtual void getMenuItems(QMenu &menu) override;

    virtual void doSpecialAction() override;

    // virtual unsigned int getMovePoints();

    // virtual bool moveToTile(std::shared_ptr<GraphicsTileBase> tileToMoveTo,
                            //bool ignoreMovePoints = false);

    // virtual bool canMoveToTile(GraphicsTileBase* tileToMoveTo);

    // virtual void switchTurn();

    // virtual bool isSelectable() const override;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    // virtual void cancelMovement();
    virtual std::string getType() const override;

    virtual void getDescriptionBrief(std::string &desc) override;


public slots:
    // virtual void initMove();

    // virtual void sendInfo() override;

protected:
    // unsigned int movePoints_ = 2;
    //std::vector<CustomGraphicsItem *> adjacentTilesTemp_ = {};

private slots:
    void buildActionSlot();
};

#endif // BUILDER_H
