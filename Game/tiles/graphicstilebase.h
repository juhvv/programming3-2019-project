#ifndef GRAPHICSTILEBASE_H
#define GRAPHICSTILEBASE_H

// #include "ui/customgraphicsitem.h"
#include "gameobjectbase.h"
#include "tiles/tilebase.h"
#include "units/graphicsunitbase.h"
#include "buildings/gamebuildingbase.h"

// static const unsigned int TILE_SIZE = 128;  // defines tile size (px)

/**
 * @brief The GraphicsTileBase class CustomGraphicsItem and TileBase derived
 * class that acts as the tile's graphics item and contains tile's data
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

    /*
    using Course::TileBase::addBuilding;
    void addBuilding(const std::shared_ptr<GameBuildingBase>& building)
    {
        std::shared_ptr<Course::BuildingBase> newBuilding =
                std::dynamic_pointer_cast<Course::BuildingBase>(building);
        TileBase::addBuilding(newBuilding);
    }
    */
    virtual bool generateResources() override;

    Course::ResourceMap generatedResources();
    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    virtual QPointF getSceneCoord() const;


public slots:

    virtual void sendInfo() override;
    virtual void claimTile();

private:
    std::vector<std::weak_ptr<GraphicsUnitBase>> m_workers;
    std::vector<std::weak_ptr<Course::BuildingBase>> m_buildings;

    //CustomGraphicsItem* graphicsObject_;

protected:
    const std::shared_ptr<Course::iGameEventHandler> eventhandlerProtected_;
    // CustomGraphicsItem* graphicsObject_;
};

#endif // GRAPHICSTILEBASE_H
