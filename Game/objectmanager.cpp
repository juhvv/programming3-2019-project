#include "objectmanager.hh"
#include "tiles/graphicstilebase.h"
#include "ui/tileoverlayitem.h"
#include "core/playerbase.h"
#include <algorithm>

ObjectManager::ObjectManager(CustomGraphicsScene* scenePtr):
    Course::iObjectManager(),
    scenePtr_(scenePtr)
{

}

void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{
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
    return nullptr;
}

std::shared_ptr<GraphicsTileBase> ObjectManager::getGTile(const Course::Coordinate &coordinate)
{
    return std::dynamic_pointer_cast<GraphicsTileBase>(getTile(coordinate));
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId &id)
{
    for (auto tile : tiles_) {
        if (tile->ID == id) {
            return tile;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getTiles(const std::vector<Course::Coordinate> &coordinates)
{
    std::vector<std::shared_ptr<Course::TileBase>> tiles = {};
    for (auto coord : coordinates) {
        for (auto tile : tiles_) {
            if (tile->getCoordinate() == coord) {
                tiles.push_back(tile);
            }
        }
    };

    return tiles;
}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getAllTiles()
{
    return tiles_;
}

void ObjectManager::resetData()
{
    scenePtr_->clear();
    tiles_.clear();
}

void ObjectManager::setOwnerMarker(GraphicsTileBase *tile, const QPixmap* marker)
{
    TileOverlayItem* markerItem =
            new TileOverlayItem(*marker);
    scenePtr_->addItem(markerItem);
    markerItem->setPos(tile->getSceneCoord());
    scenePtr_->update();
    qDebug() << tile->getOwner()->getName().c_str();
}

void ObjectManager::setGraphicsObject(std::shared_ptr<GameObjectBase> &gameObject)
{
    CustomGraphicsItem* newGraphicsItem = new CustomGraphicsItem(gameObject);
    gameObject->setGraphicsItem(newGraphicsItem, scenePtr_);
    scenePtr_->update();
}
