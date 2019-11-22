#include "objectmanager.hh"
#include "tiles/graphicstilebase.h"
#include "ui/tileoverlayitem.h"

ObjectManager::ObjectManager(Course::SimpleGameScene* sgsPtr, CustomGraphicsScene* scenePtr):
    sgsPtr_(sgsPtr), scenePtr_(scenePtr)
{

}

void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{
    /*
    for (auto tile : tiles) {
        //sgsPtr_->drawItem(tile);
        //sgsPtr_->update();

        Course::TileBase* rawPtr = tile.get();
        GraphicsTileBase* newItem = static_cast<GraphicsTileBase*>(rawPtr);
        scenePtr_->addItem(newItem);
        Course::Coordinate newCoord = newItem->getCoordinate();
        newItem->setPos(newCoord.x() * 128, newCoord.y() * 128);
        newItem->update();
        scenePtr_->update();
    }
    */
    scenePtr_->setupMap(tiles);
    tiles_ = tiles;
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::Coordinate &coordinate)
{
    for (auto tile : tiles_) {
        if (tile->getCoordinate() == coordinate) {
            return tile;
        }
    }
    return NULL;
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId &id)
{
    return NULL;
}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getTiles(const std::vector<Course::Coordinate> &coordinates)
{
    return {};
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
}
