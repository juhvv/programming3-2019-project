
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

    /**
      * @copydoc GameObjectBase::getMenuItems
     */
    virtual void getMenuItems(QMenu &menu) override;

    /**
      * @copydoc GameObjectBase::isSelectable()
     */
    virtual bool isSelectable() const override;

    /**
      * @copydoc GameObjectBase::isMovable()
     */
    virtual bool isMovable() const override;

    /**
     * @brief Returns this tile's move cost (i.e. how many points does it cost to
     * \n move to this tile)
     * @note This method should be re-implemented by derived classes
     * @return Tile's movement cost
     */
    virtual unsigned int getMovementCost() const;

    /**
     * @brief Adds specified unit to this tile's unit vector
     * @param unit Ptr to new unit
     */
    virtual void addUnit(GraphicsUnitBase* unit);

    /**
     * @brief Removes specified unit from this tile's units
     * @param unit Ptr to unit that is removed
     */
    virtual void removeUnit(GraphicsUnitBase* unit);


    virtual bool generateResources() override;

    /**
     * @brief generatedResources    // kirjoita tähän jotain
     * @param currentPlayer
     * @return
     */
    Course::ResourceMap generatedResources(std::shared_ptr<Player>& currentPlayer);

    /**
     * @copydoc GameObjectBase::setGraphicsItem()
     */
    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    /**
     * @brief Returns this tile's location in scene coordinates
     * @return QPointF location of this tile
     */
    virtual QPointF getSceneCoord() const;

public slots:

    /**
     * @copydoc GameObjectBase::sendInfo()
     */
    virtual void sendInfo() override;

    // DEBUG DELET THIS
    virtual void claimTile();
};

#endif // GRAPHICSTILEBASE_H
