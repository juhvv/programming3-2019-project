#include "objectmanager.hh"

ObjectManager::ObjectManager(Course::SimpleGameScene* sgsPtr):
    sgsPtr_(sgsPtr)
{

}

void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{
    for (auto tile : tiles) {
        sgsPtr_->drawItem(tile);
        sgsPtr_->update();
        std::shared_ptr<Course::Coordinate> coord = tile->getCoordinatePtr();
        qDebug() << "Tile Coordinates: x=" << coord->x() << " y=" << coord->y();
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
