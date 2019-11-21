#include "customgraphicsscene.h"


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
