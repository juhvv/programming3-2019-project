#ifndef WATERTILEITEM_H
#define WATERTILEITEM_H


#include "tiles/graphicstilebase.h"

class WaterTileItem : public GraphicsTileBase
{
public:
    WaterTileItem() = delete ;
    explicit WaterTileItem(const Course::Coordinate& location,
                           const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                           const std::shared_ptr<Course::iObjectManager>& objectmanager,
                           CustomGraphicsScene* scene = nullptr,
                     const unsigned int& max_build = 2,
                     const unsigned int& max_work = 3,
                     const Course::ResourceMap& production = Course::ConstResourceMaps::FOREST_BP);

    virtual ~WaterTileItem() = default;

    virtual unsigned int getMovementCost() override;

    // virtual QRectF boundingRect() const override;

    virtual std::string getType() const override;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;
};


#endif // WATERTILEITEM_H
