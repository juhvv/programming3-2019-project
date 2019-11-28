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

            if (pressed->isMovable()) {
                QAction *moveAction = menu.addAction("Move");
                menu.addSeparator();
                connect(moveAction, &QAction::triggered, this, &CustomGraphicsScene::enterMovementMode);
            }
            pressed->getMenuItems(menu);
            lastClickedItem_ = pressed;
            menu.exec(contextMenuEvent->screenPos());
        }
    }
}

void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    // case for moving units
    if (movementModeFlag_ && mouseEvent->button() == Qt::LeftButton) {
        CustomGraphicsItem* itemToMoveTo =
                dynamic_cast<CustomGraphicsItem*>(itemAt(mouseEvent->scenePos(), QTransform()));

        auto it = std::find(tileVec_.begin(), tileVec_.end(), itemToMoveTo);
        if (it == tileVec_.end()) {
            // check if clicked tile is reachable
            for (CustomGraphicsItem* tile : tileVec_) {// USE FUNCTION
                tile->toggleHighlight(false);
            }
            qDebug() << "cant go there";
            movementModeFlag_ = false;
            return;
        }

        GraphicsUnitBase* unit = dynamic_cast<GraphicsUnitBase*>(lastClickedItem_);
        std::shared_ptr<GraphicsTileBase> tileMoveTo =
                std::dynamic_pointer_cast<GraphicsTileBase>(itemToMoveTo->getParentObject());
        unit->moveToTile(tileMoveTo);

        for (CustomGraphicsItem* tile : tileVec_) { // USE FUNCTION
            tile->toggleHighlight(false);
        }

        update(sceneRect());
        movementModeFlag_ = false;

        // case for cancelling movement
    } else if (movementModeFlag_ && mouseEvent->button() == Qt::RightButton){
        movementModeFlag_ = false;

    } else {
        // default behaviour
        QGraphicsScene::mousePressEvent(mouseEvent);
    }
}

void CustomGraphicsScene::getAdjacentTiles(std::vector<CustomGraphicsItem*> &tileVec)
{
    if (movementModeFlag_) {
        qreal posx = lastClickedItem_->x();
        qreal posy = lastClickedItem_->y();

        GraphicsUnitBase* unit = dynamic_cast<GraphicsUnitBase*>(lastClickedItem_);
        QRectF selectionRect = QRectF(posx - 50, posy - 50, 200, 200);
        QList<QGraphicsItem* > selectedItems = items(selectionRect);

        for (QGraphicsItem* item : selectedItems) {
            CustomGraphicsItem* itemPtr = static_cast<CustomGraphicsItem*>(item);
            GraphicsTileBase* tilePtr = dynamic_cast<GraphicsTileBase*>(itemPtr->getParentObject().get());

            if ( tilePtr != nullptr) {
                // add tiles that are reachable to tileVec
                if (unit->canMoveToTile(tilePtr)) {
                    qDebug() << "selected tile: " << tilePtr->ID;
                    tileVec.push_back(itemPtr);
                }
                qDebug() << "selected tile: " << tilePtr->ID;
            }
        }
    }
}

void CustomGraphicsScene::addObject(std::shared_ptr<GameObjectBase> &newObject)
{
    std::shared_ptr<GameBuildingBase> buildingPtr = std::dynamic_pointer_cast<GameBuildingBase>(newObject);

    if (buildingPtr != nullptr) {

    }
}

void CustomGraphicsScene::enterMovementMode()
{
    // called when move is selected on a unit
    tileVec_.clear();
    movementModeFlag_ = true;
    // std::vector<QGraphicsItem*> tileVec = {};
    getAdjacentTiles(tileVec_);
    for (CustomGraphicsItem* tileModel : tileVec_) {// USE FUNCTION
        tileModel->toggleHighlight(true);
    }
}
