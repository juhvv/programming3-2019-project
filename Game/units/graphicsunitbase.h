#ifndef GRAPHICSUNITBASE_H
#define GRAPHICSUNITBASE_H

#include "ui/customgraphicsitem.h"
#include "gameobjectbase.h"
#include "workers/workerbase.h"
#include "gameresourcemaps.hh"

class GraphicsTileBase;

namespace Units {
    enum Range {
        BASICRANGE = 2,
        LONGRANGE = 4
    };
}

class GraphicsUnitBase : public Course::WorkerBase, public GameObjectBase
{
public:
    GraphicsUnitBase() = delete ;
    explicit GraphicsUnitBase(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                        const std::shared_ptr<Course::iObjectManager>& objectmanager,
                        const std::shared_ptr<Course::PlayerBase>& owner,
                        CustomGraphicsScene* scene = nullptr,
                        const int& tilespaces = 1,
                        const Course::ResourceMap& cost = {},
                        const Course::ResourceMapDouble& efficiency = {});

    virtual ~GraphicsUnitBase() = default;

    virtual bool isMovable() const override final;

    virtual void getMenuItems(QMenu &menu) override;

    virtual unsigned int getMovePoints();

    virtual bool moveToTile(std::shared_ptr<GraphicsTileBase> tileToMoveTo,
                            bool ignoreMovePoints = false);

    virtual bool canMoveToTile(GraphicsTileBase* tileToMoveTo);

    virtual void switchTurn();

    virtual bool isSelectable() const override;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    virtual void cancelMovement() final;

    virtual void getDescriptionBrief(std::string &desc) override;

    virtual std::shared_ptr<GraphicsTileBase> getCurrentTile() final;

public slots:
    virtual void initMove() final;

    virtual void sendInfo() override;

protected:
    unsigned int movePoints_ = 2;
    std::vector<CustomGraphicsItem *> adjacentTilesTemp_ = {};
};

#endif // GRAPHICSUNITBASE_H
