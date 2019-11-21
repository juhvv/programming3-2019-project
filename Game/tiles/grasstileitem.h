#ifndef GRASSTILEITEM_H
#define GRASSTILEITEM_H

#include "tiles/graphicstilebase.h"

class GrassTileItem : public GraphicsTileBase
{
public:
    GrassTileItem() = delete ;
    explicit GrassTileItem(const Course::Coordinate& location,
                     const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                     const std::shared_ptr<Course::iObjectManager>& objectmanager,
                     const QPixmap &pixmap = QPixmap(":/resources/grass.PNG"),
                     QGraphicsItem *parent = nullptr,
                     const unsigned int& max_build = 2,
                     const unsigned int& max_work = 3,
                     const Course::ResourceMap& production = Course::ConstResourceMaps::FOREST_BP);

    // virtual QRectF boundingRect() const override;

    virtual std::string getType() const override;

    virtual DrawBias getDrawBias() override;
};

#endif // GRASSTILEITEM_H
