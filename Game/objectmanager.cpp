#include "objectmanager.hh"
#include "tiles/graphicstilebase.h"

ObjectManager::ObjectManager(Course::SimpleGameScene* sgsPtr, QGraphicsScene* scenePtr):
    sgsPtr_(sgsPtr), scenePtr_(scenePtr)
{

}

void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{
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
