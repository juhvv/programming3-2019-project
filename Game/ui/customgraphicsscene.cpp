#include "customgraphicsscene.h"
#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "buildings/gamebuildingbase.h"
#include <algorithm>

CustomGraphicsScene::CustomGraphicsScene(QObject *parent) :
    QGraphicsScene (parent)

{

}

void CustomGraphicsScene::setupMap(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{
    for (auto tile : tiles) {

        std::shared_ptr<GraphicsTileBase> newTile = std::dynamic_pointer_cast<GraphicsTileBase>(tile);
        CustomGraphicsItem* newItemVisual = new CustomGraphicsItem(newTile);
        qreal newX = newTile->getCoordinate().x() * TILE_SIZE;
        qreal newY = newTile->getCoordinate().y() * TILE_SIZE;
        addItem(newItemVisual);
        newItemVisual->setPos(newX, newY);
        newTile->setGraphicsItem(newItemVisual, this);
    }
    this->update(sceneRect());
}

void CustomGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent)
{
    QGraphicsItem* item = itemAt(contextMenuEvent->scenePos(), QTransform());

    CustomGraphicsItem* pressed = static_cast<CustomGraphicsItem*>(item);
    if (pressed == nullptr || movementModeFlag_) {
        return;
    }

    if (pressed->isSelectable()) {
        QMenu menu;
        if (!movementModeFlag_) {
            /*
            if (pressed->isMovable()) {
                QAction *moveAction = menu.addAction("Move");
                menu.addSeparator();
                connect(moveAction, &QAction::triggered, this, &CustomGraphicsScene::enterMovementMode);
            }
            */
            pressed->getMenuItems(menu);
            lastClickedItem_ = pressed;
            menu.exec(contextMenuEvent->screenPos());
        }
    }
}

void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    // case for moving units
    if (movementModeFlag_) {

        std::shared_ptr<GraphicsUnitBase> unitToBeMoved =
                std::dynamic_pointer_cast<GraphicsUnitBase>(lastClickedItem_->getParentObject().lock());

        // case for cancelling movement
        if (mouseEvent->button() == Qt::RightButton) {
            unitToBeMoved->cancelMovement();
            movementModeFlag_ = false;
        }

        CustomGraphicsItem* itemToMoveTo =
                dynamic_cast<CustomGraphicsItem*>(itemAt(mouseEvent->scenePos(), QTransform()));
        /*
        auto it = std::find(tileVec_.begin(), tileVec_.end(), itemToMoveTo);
        if (it == tileVec_.end()) {
                unitToBeMoved->cancelMovement();
                qDebug() << "cant go there";
                movementModeFlag_ = false;
                return;
            }
        */
        // GraphicsUnitBase* unit = dynamic_cast<GraphicsUnitBase*>(lastClickedItem_);
        std::weak_ptr<GraphicsTileBase> tileMoveTo =
                std::dynamic_pointer_cast<GraphicsTileBase>(itemToMoveTo->getParentObject().lock());
        if (tileMoveTo.lock() != nullptr && unitToBeMoved->moveToTile(tileMoveTo.lock())) {
            qDebug() << unitToBeMoved->ID << ": move successful";
        };

        update(sceneRect());
        unitToBeMoved->cancelMovement();
        movementModeFlag_ = false;
    }else {
        // default behaviour
        QGraphicsScene::mousePressEvent(mouseEvent);
    }
}

void CustomGraphicsScene::getAdjacentTiles(std::vector<CustomGraphicsItem *> &tileVec,
                                           std::shared_ptr<GraphicsTileBase> tile,
                                           const unsigned int range, GraphicsUnitBase *unit)
{
    // define selection area
    qreal posx = tile->getSceneCoord().x();
    qreal posy = tile->getSceneCoord().y();
    QRectF selectionRect = QRectF(posx - TILE_SIZE/2, posy - TILE_SIZE/2,
                                  TILE_SIZE * 2, TILE_SIZE * 2);

    QList<QGraphicsItem* > selectedItems = items(selectionRect);
    for (QGraphicsItem* item : selectedItems) {
        CustomGraphicsItem* itemPtr = static_cast<CustomGraphicsItem*>(item);
        std::shared_ptr<GraphicsTileBase> selectedTilePtr =
                std::dynamic_pointer_cast<GraphicsTileBase>(itemPtr->getParentObject().lock());

        if ( selectedTilePtr != nullptr ) {
            // add all tiles that can be moved to (defined by parameter range)
            // except center tile
            if (selectedTilePtr != tile && selectedTilePtr->getMovementCost() <= range) {
                if (unit) {
                    if (unit->canMoveToTile(selectedTilePtr.get())) {
                        qDebug() << "selected tile: " << selectedTilePtr->ID;
                        tileVec.push_back(itemPtr);
                    }
                } else {
                    qDebug() << "selected tile: " << selectedTilePtr->ID;
                    tileVec.push_back(itemPtr);
                }

            }
        }
    }
}

void CustomGraphicsScene::toggleTileHighlight(std::vector<CustomGraphicsItem *> &tileVec, bool value)
{
    for (auto graphObj : tileVec) {
        graphObj->toggleHighlight(value);
    }
}

void CustomGraphicsScene::enterMovementMode()
{
    // called when move is selected on a unit
    tileVec_.clear();
    movementModeFlag_ = true;
    // std::vector<QGraphicsItem*> tileVec = {};
    // getAdjacentTiles(tileVec_);
    /*
    for (CustomGraphicsItem* tileModel : tileVec_) {// USE FUNCTION
        tileModel->toggleHighlight(true);
    }*/
}
