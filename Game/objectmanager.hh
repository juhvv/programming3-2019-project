#ifndef OBJECTMANAGER_HH
#define OBJECTMANAGER_HH

//#include <QObject>

#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"
#include "graphics/simplegamescene.h"
#include "ui/customgraphicsscene.h"
#include "tiles/graphicstilebase.h"

class ObjectManager : public QObject, public Course::iObjectManager
{
    Q_OBJECT
public:
    explicit ObjectManager(Course::SimpleGameScene* sgsPtr = NULL,  CustomGraphicsScene* scenePtr = NULL);

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

    std::vector<std::shared_ptr<Course::TileBase>> getAllTiles();


    void resetData();   // resets data

    void setOwnerMarker(GraphicsTileBase* tile, const QPixmap* marker);

public slots:
    // void addOwnersipMarker(unsigned int ID);

private:
    std::vector<std::shared_ptr<Course::TileBase>> tiles_;
    Course::SimpleGameScene* sgsPtr_;
    CustomGraphicsScene* scenePtr_;
};

#endif // OBJECTMANAGER_HH
