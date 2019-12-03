#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <memory>
#include "tiles/graphicstilebase.h"
#include "ui/customgraphicsitem.h"

class CustomGraphicsItem;

class GameEventHandler;

class ObjectManager;

class GameObjectBase;

/**
 * @brief The CustomGraphicsScene class is custom QGraphicsScene class for displaying
 * \n map tiles and other game objects. Additionally, interaction with these items is implemented.
 */
class CustomGraphicsScene : public QGraphicsScene
{
public:
    /**
     * @brief CustomGraphicsScene constructor
     * @param parent Parent QObject for scene
     */
    CustomGraphicsScene(QObject *parent = nullptr);

    virtual ~CustomGraphicsScene() = default;

    /**
     * @brief Draws and places map tiles in the scene
     * @param tiles Vector containing pointers to tile objects
     */
    void setupMap(const std::vector<std::shared_ptr<Course::TileBase>>& tiles);

    /**
     * @brief Handles context menu events. Retrieves menu from GraphicsObject and its parent object
     * @param contextMenuEvent Event to be handled
     */
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent) override;

    /**
     * @brief Handles mouse press events to implement some interactions with GraphicsObjects
     * @param mouseEvent Event to be handled
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

    /**
     * @brief Retrieves tiles adjacent to the parameter 'tile' and stores them to 'tileVec'.
     * \n If parameters 'unit' and 'range' are present, only tiles that the unit can move to are
     * \n selected.
     * @param tileVec Vector which stores pointers to adjacent tiles.
     * @param tile Center tile of the selection
     * @param range Specifies max movement cost for selected tiles
     * @param unit Unit which is inquiring the tiles (for moving)
     */
    void getAdjacentTiles(std::vector<CustomGraphicsItem* > &tileVec,
                          std::shared_ptr<GraphicsTileBase> tile,
                          const unsigned int range = 999,
                          GraphicsUnitBase* unit = nullptr);

    /**
     * @brief Toggles highlight effect (see CustomGraphicsItem) on selected GraphicsItems
     * @param tileVec Vector containing GraphicsItems
     * @param value Bool value for highlight state
     */
    void toggleTileHighlight(std::vector<CustomGraphicsItem *> &tileVec, bool value = false);

public slots:
    /**
     * @brief This slot sets the scene to process next mouse press as object move command
     */
    void enterMovementMode();

protected:
    bool movementModeFlag_ = false; // defines whether mouse presses as move commands
    CustomGraphicsItem *lastClickedItem_ = nullptr;

    std::shared_ptr<GameEventHandler> eventHandler_;
    std::shared_ptr<ObjectManager> objectManager_;
};

#endif // CUSTOMGRAPHICSSCENE_H
