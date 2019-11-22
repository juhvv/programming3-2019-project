#ifndef GRAPHICSUNITBASE_H
#define GRAPHICSUNITBASE_H

#include "ui/customgraphicsitem.h"
#include "workers/workerbase.h"

class GraphicsUnitBase : public CustomGraphicsItem, public Course::WorkerBase
{
public:
    GraphicsUnitBase() = delete ;
    explicit GraphicsUnitBase(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                        const std::shared_ptr<Course::iObjectManager>& objectmanager,
                        const std::shared_ptr<Course::PlayerBase>& owner,
                        const QPixmap &pixmap = QPixmap(":/resources/units/worker.PNG"),
                        QGraphicsItem *parent = nullptr,
                        const int& tilespaces = 1,
                        const Course::ResourceMap& cost = {},
                        const Course::ResourceMapDouble& efficiency = {});

    virtual ~GraphicsUnitBase() = default;

    virtual bool isMovable() override;

    virtual void getMenuItems(QMenu &menu) override;

    virtual void doSpecialAction() override;
};

#endif // GRAPHICSUNITBASE_H
