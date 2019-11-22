#include "customgraphicsscene.h"
#include "gameeventhandler.hh"


CustomGraphicsScene::CustomGraphicsScene(QObject *parent) : QGraphicsScene (parent)
{

}

void CustomGraphicsScene::setupMap(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{
    for (auto tile : tiles) {
        Course::TileBase* rawPtr = tile.get();
        GraphicsTileBase* newItem = static_cast<GraphicsTileBase*>(rawPtr);
        addItem(newItem);
        qreal newX = newItem->getCoordinate().x() * TILE_SIZE;
        qreal newY = newItem->getCoordinate().y() * TILE_SIZE;
        newItem->setPos(newX, newY);
    }
    this->update(sceneRect());
    /*
    std::vector<GraphicsTileBase* > drawBuffer = {};
    int offset = 0;

    for (auto tile : tiles) {
        Course::TileBase* rawPtr = tile.get();
        GraphicsTileBase* newItem = static_cast<GraphicsTileBase*>(rawPtr);

        if (newItem->getDrawBias() < LAST) {
            addItem(newItem);
            qreal newX = newItem->getCoordinate().x() * TILE_SIZE;
            qreal newY = newItem->getCoordinate().y() * TILE_SIZE;
            newItem->setPos(newX, newY);
        } else {
            drawBuffer.push_back(newItem);
        }
    }

    for (auto laterTile : drawBuffer) {
        addItem(laterTile);
        qreal newX = laterTile->getCoordinate().x() * TILE_SIZE;
        qreal newY = laterTile->getCoordinate().y() * TILE_SIZE;
        laterTile->setPos(newX, newY);
    }
    */
}

void CustomGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent)
{
    //qDebug() << "mousePos: " << contextMenuEvent->pos();
    // qDebug() << "sceneRect: " << this->sceneRect();
    QGraphicsItem* item = itemAt(contextMenuEvent->scenePos(), QTransform());

    CustomGraphicsItem* pressed = static_cast<CustomGraphicsItem*>(item);
    if (pressed == NULL) {
        return;
    }

    if (pressed->isSelectable()) {
        QMenu menu;
        if (!movementModeFlag_) {
            QAction *infoAction = menu.addAction("Info");
            menu.addSeparator();

            if (pressed->isMovable()) {
                QAction *moveAction = menu.addAction("Move");
                connect(moveAction, &QAction::triggered, this, &CustomGraphicsScene::enterMovementMode);
            }

            pressed->getMenuItems(menu);
            lastClickedItem_ = pressed;
            menu.exec(contextMenuEvent->screenPos());
        } else {
            //QAction *moveHereAction = menu.addAction("Move here");
            //connect(moveHereAction, &QAction::triggered, this, &CustomGraphicsScene::moveObject);
        }
    }


   // menu.exec(contextMenuEvent->screenPos());
}

void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (movementModeFlag_ && mouseEvent->button() == Qt::RightButton) {
        lastClickedItem_->setPos(mouseEvent->scenePos());
        update(sceneRect());
        movementModeFlag_ = false;
    } else {
        QGraphicsScene::mousePressEvent(mouseEvent);
    }
}

void CustomGraphicsScene::enterMovementMode()
{
    movementModeFlag_ = true;
}
