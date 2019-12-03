
#ifndef GRAPHICSTILEBASE_H
#define GRAPHICSTILEBASE_H

#include "gameobjectbase.h"
#include "tiles/tilebase.h"
#include "units/graphicsunitbase.h"
#include "buildings/gamebuildingbase.h"
#include "gameresourcemaps.hh"
#include "player.hh"

/**
 * @brief The GraphicsTileBase class GameObjectBase and TileBase derived
 * base class for different tile objects
 */
class GraphicsTileBase :  public GameObjectBase, public Course::TileBase
{
public:
    GraphicsTileBase() = delete;
    explicit GraphicsTileBase(const Course::Coordinate& location,
                     const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                     const std::shared_ptr<Course::iObjectManager>& objectmanager,
                     CustomGraphicsScene* scene = nullptr,
                     const unsigned int& max_build = 1,
                     const unsigned int& max_work = 3,
                     const Course::ResourceMap& production = {});

    virtual ~GraphicsTileBase() = default;

    virtual Course::iGameEventHandler *getEventHandlerPtr() const;

    virtual void getMenuItems(QMenu &menu) override;

    virtual bool isSelectable() const override;

    virtual bool isMovable() const override;

    virtual unsigned int getMovementCost() const;

    virtual void addUnit(GraphicsUnitBase* unit);

    virtual void removeUnit(GraphicsUnitBase* unit);

    virtual bool generateResources() override;

    Course::ResourceMap generatedResources();
    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    virtual QPointF getSceneCoord() const;

public slots:

    virtual void sendInfo() override;
    virtual void claimTile();

protected:
    const std::shared_ptr<Course::iGameEventHandler> eventhandlerProtected_;
};

#endif // GRAPHICSTILEBASE_H
