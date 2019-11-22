#ifndef GRAPHICSTILEBASE_H
#define GRAPHICSTILEBASE_H

#include "ui/customgraphicsitem.h"
#include "tiles/tilebase.h"

static const unsigned int TILE_SIZE = 128;  // defines tile size (px)

/**
 * @brief The DrawBias enum defines when a tile is drawn to th map scene
 */
enum DrawBias {
    DEFAULT = 0,
    LAST = 1,
};

/**
 * @brief The GraphicsTileBase class CustomGraphicsItem and TileBase derived
 * class that acts as the tile's graphics item and contains tile's data
 */
class GraphicsTileBase : public CustomGraphicsItem, public Course::TileBase
{
public:
    GraphicsTileBase() = delete;
    explicit GraphicsTileBase(const Course::Coordinate& location,
                     const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                     const std::shared_ptr<Course::iObjectManager>& objectmanager,
                     const QPixmap &pixmap = QPixmap(":/resources/grass.PNG"),
                     QGraphicsItem *parent = nullptr,
                     const unsigned int& max_build = 2,
                     const unsigned int& max_work = 3,
                     const Course::ResourceMap& production = {});



    virtual QPainterPath shape() const override;
    // virtual QRectF boundingRect() const override;

    // virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    virtual Course::iGameEventHandler *getEventHandlerPtr() const override;

    virtual void getMenuItems(QMenu &menu) override;

    virtual bool isSelectable() override;

    virtual DrawBias getDrawBias() = 0;

public slots:

    virtual void sendInfo();
    virtual void sendPtr();

protected:
    const std::shared_ptr<Course::iGameEventHandler> eventhandlerProtected_;
};

#endif // GRAPHICSTILEBASE_H
