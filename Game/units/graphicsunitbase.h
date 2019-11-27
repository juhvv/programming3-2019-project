#ifndef GRAPHICSUNITBASE_H
#define GRAPHICSUNITBASE_H

#include "ui/customgraphicsitem.h"
#include "gameobjectbase.h"
#include "workers/workerbase.h"

class GraphicsTileBase;

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

    virtual bool isMovable();

    virtual void getMenuItems(QMenu &menu) override;

    virtual void doSpecialAction() override;

    virtual unsigned int getMovePoints();

    virtual bool moveToTile(std::shared_ptr<GraphicsTileBase> tileToMoveTo);

    virtual bool canMoveToTile(GraphicsTileBase* tileToMoveTo);

    virtual void switchTurn();

    virtual bool isSelectable();

protected:
    unsigned int movePoints_ = 2;
};

#endif // GRAPHICSUNITBASE_H
