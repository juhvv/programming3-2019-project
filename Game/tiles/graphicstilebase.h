#ifndef GRAPHICSTILEBASE_H
#define GRAPHICSTILEBASE_H

#include "ui/customgraphicsitem.h"
#include "tiles/tilebase.h"

static const unsigned int TILE_SIZE = 128;  // defines tile size (px)

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



    //virtual QPainterPath shape() const override;
    virtual QRectF boundingRect() const override;

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

public slots:
    virtual void sendInfo();
};

#endif // GRAPHICSTILEBASE_H
