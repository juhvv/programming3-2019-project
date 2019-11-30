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
                           CustomGraphicsScene* scene = nullptr,
                     const unsigned int& max_build = 1,
                     const unsigned int& max_work = 3,
                     const Course::ResourceMap& production = Course::ConstResourceMaps::FOREST_BP);

    virtual ~GrassTileItem() = default;

    virtual unsigned int getMovementCost() const override;

    virtual std::string getType() const override;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    virtual void getDescriptionBrief(std::string &desc) override;
};

#endif // GRASSTILEITEM_H
