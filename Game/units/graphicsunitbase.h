#ifndef GRAPHICSUNITBASE_H
#define GRAPHICSUNITBASE_H

#include "ui/customgraphicsitem.h"
#include "gameobjectbase.h"
#include "workers/workerbase.h"
#include "gameresourcemaps.hh"

class GraphicsTileBase;

namespace Units {
    /**
     * @brief Type for defining units' movement ranges
     */
    enum Range {
        BASICRANGE = 2,
        LONGRANGE = 4
    };
}

/**
 * @brief The GraphicsUnitBase class is base class for different unit classes.
 */
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

    /**
      * @copydoc GameObjectBase::isMovable()
     */
    virtual bool isMovable() const final;

    /**
     * @copydoc GameObjectBase::getMenuItems(QMenu &menu)
     */
    virtual void getMenuItems(QMenu &menu) override;

    /**
     * @brief Implementation for virtual method inherited from WorkerBase class.
     * \n Currently does nothing.
     */
    virtual void doSpecialAction() override;

    /**
     * @brief Returns unit's current move points
     * @return Unit's current points
     */
    virtual unsigned int getMovePoints();

    /**
     * @brief Tries to move this unit to the specified tile.
     * @param tileToMoveTo Tile to attempt the move to
     * @param ignoreMovePoints Specifies if unit's movement points should be ignored
     * \n when checking move possibility
     * @return True if move succeeded, else false
     */
    virtual bool moveToTile(std::shared_ptr<GraphicsTileBase> tileToMoveTo,
                            bool ignoreMovePoints = false);

    /**
     * @brief Checks if unit can move to specified tile
     * @param tileToMoveTo Tile to check
     * @return True if unit can move to tile, else false
     */
    virtual bool canMoveToTile(GraphicsTileBase* tileToMoveTo);

    /**
     * @brief Resets this unit's movement points. Should be called when turn changes.
     */
    virtual void switchTurn();

    /**
     * @copydoc GameObjectBase::isSelectable()
     */
    virtual bool isSelectable() const override;

    /**
     * @copydoc GameObjectBase::setGraphicsItem
     */
    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    /**
     * @brief Resets unit's temporary adjacent tiles vector and de-highlights those tiles.
     * \n This method should also be called when move is excecuted.
     */
    virtual void cancelMovement() final;

    /**
     * @copydoc GameObjectBase::getDescriptionBrief()
     */
    virtual void getDescriptionBrief(std::string &desc) override;

    /**
     * @brief Returns this unit's current tile
     * @return Ptr to current tile
     */
    virtual std::shared_ptr<GraphicsTileBase> getCurrentTile() final;

public slots:
    /**
     * @brief Sets the scene to movement mode and highlights
     * \n adjacent tiles this unit can move to.
     */
    virtual void initMove() final;

    /**
     * @copydoc GameObjectBase::sendInfo()
     */
    virtual void sendInfo() override;

protected:
    unsigned int movePoints_ = 2;
    std::vector<CustomGraphicsItem *> adjacentTilesTemp_ = {};
};

#endif // GRAPHICSUNITBASE_H
