#ifndef OBJECTMANAGER_HH
#define OBJECTMANAGER_HH

//#include <QObject>
#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"
#include "graphics/simplegamescene.h"

class ObjectManager : public QObject, public Course::iObjectManager
{
    Q_OBJECT
public:
    explicit ObjectManager(Course::SimpleGameScene* sgsPtr = NULL);

    /**
     * @brief Adds new tiles to the ObjectManager.
     * @param tiles contains the tiles to be added.
     */
    void addTiles(
            const std::vector<std::shared_ptr<Course::TileBase>>& tiles);

    /**
     * @brief Returns a pointer to a Tile that has specified coordinate.
     * @param coordinate
     * @return
     * @post Exception Guarantee: Basic
     */
    std::shared_ptr<Course::TileBase> getTile(
            const Course::Coordinate& coordinate);

    /**
     * @brief Returns a pointer to a Tile that has specified ID
     * @param id
     * @return
     * @post Exception Guarantee: Basic
     */
    std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id) final;

    /**
     * @brief Returns a vector of pointers to Tiles specified by Coordinates.
     * @param coordinates
     * @return
     * @post Exception Guarantee: Basic
     */
    std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates) final;

    void resetData();   // resets data

private:
    std::vector<std::shared_ptr<Course::TileBase>> tiles_;
    Course::SimpleGameScene* sgsPtr_;
};

#endif // OBJECTMANAGER_HH
