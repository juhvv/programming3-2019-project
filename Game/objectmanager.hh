#ifndef OBJECTMANAGER_HH
#define OBJECTMANAGER_HH

//#include <QObject>

#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"
#include "ui/customgraphicsscene.h"
#include "tiles/graphicstilebase.h"

/**
 * @brief The ObjectManager class stores map tiles and provides
 * \n methods for searching tiles and manipulating game objects
 */
class ObjectManager : public QObject, public Course::iObjectManager
{
    Q_OBJECT
public:
    /**
     * @brief ObjectManager constructor
     * @param scenePtr Pointer to CustomGraphicsScene used
     */
    explicit ObjectManager(CustomGraphicsScene* scenePtr = nullptr);

    virtual ~ObjectManager() = default;

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
     * @brief Returns a pointer to a GraphicsTileObject that has specified coordinate.
     * @param coordinate
     * @return
     * @post Exception Guarantee: Basic
     */
    std::shared_ptr<GraphicsTileBase> getGTile(
            const Course::Coordinate& coordinate);

    /**
     * @brief Returns a pointer to a Tile that has specified ID
     * @param id
     * @return
     * @post Exception Guarantee: Basic
     */
    std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id) final;

    /**
     * @brief Returns a vector of pointers to Tiles
     * @param coordinates
     * @return
     * @post Exception Guarantee: Basic
     */
     std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates
            ) final;

     /**
     * @brief Returns all tiles stored by objectmanager
     * @return Vector containing pointers to tiles
     */
    std::vector<std::shared_ptr<Course::TileBase>> getAllTiles();

    /**
     * @brief Deletes all tiles and clears the graphicsscene
     */
    void resetData();

    /**
     * @brief Sets ownermarker on specified tile.
     * @param tile Tile to be marked
     * @param marker Marker that is added at tile
     */
    void setOwnerMarker(GraphicsTileBase* tile, const QPixmap* marker);

    /**
     * @brief Adds graphicsobject for gameobject.
     * @param gameObject
     * @note Undefined operation may occur if methods are called on a gameobject
     * which has no graphicsobject.
     */
    void setGraphicsObject(std::shared_ptr<GameObjectBase> &gameObject);

private:
    std::vector<std::shared_ptr<Course::TileBase>> tiles_;
    CustomGraphicsScene* scenePtr_;
};

#endif // OBJECTMANAGER_HH
