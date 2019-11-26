#include "objectmanager.hh"
#include "tiles/graphicstilebase.h"
#include "ui/tileoverlayitem.h"

ObjectManager::ObjectManager(Course::SimpleGameScene* sgsPtr, CustomGraphicsScene* scenePtr):
    sgsPtr_(sgsPtr), scenePtr_(scenePtr)
{

}

void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{

    for (auto tile : tiles) {
        //sgsPtr_->drawItem(tile);
        //sgsPtr_->update();

        //Course::TileBase* rawPtr = tile.get();
        std::shared_ptr<GraphicsTileBase> graphicTile;
        // std::unique_ptr<GraphicsTileBase> newItem;
        graphicTile = std::dynamic_pointer_cast<GraphicsTileBase>(tile);
        //newItem = std::move(*graphicTile);
        scenePtr_->addItem(graphicTile.get());
        Course::Coordinate newCoord = graphicTile->getCoordinate();

        graphicTile->setPos(newCoord.x() * 128, newCoord.y() * 128);
        graphicTile->update();
        scenePtr_->update();
    }

    // scenePtr_->setupMap(tiles);
    tiles_ = tiles;

}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::Coordinate &coordinate)
{
    for (auto tile : tiles_) {
        if (tile->getCoordinate() == coordinate) {
            return tile;
        }
    }
    return nullptr;
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId &id)
{
    return nullptr;
}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getTiles(const std::vector<Course::Coordinate> &coordinates)
{
    return {};
}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getAllTiles()
{
    return tiles_;
}

void ObjectManager::resetData()
{
    tiles_.clear();
}

void ObjectManager::setOwnerMarker(GraphicsTileBase *tile, const QPixmap* marker)
{
    TileOverlayItem* markerItem =
            new TileOverlayItem(*marker);
    markerItem->setZValue(10);
    scenePtr_->addItem(markerItem);
    markerItem->setPos(tile->x(), tile->y());
    scenePtr_->update();
    qDebug() << tile->getOwner()->getName().c_str();
}
