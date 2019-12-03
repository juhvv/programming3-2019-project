#ifndef SWAMPTILEITEM_H
#define SWAMPTILEITEM_H

#include "tiles/graphicstilebase.h"

class SwampTileItem : public GraphicsTileBase
{
public:
    SwampTileItem() = delete ;
    explicit SwampTileItem(const Course::Coordinate& location,
                              const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                              const std::shared_ptr<Course::iObjectManager>& objectmanager,
                              CustomGraphicsScene* scene = nullptr,
                     const unsigned int& max_build = 1,
                     const unsigned int& max_work = 2,
                            const Course::ResourceMap& production = GameConstResourceMaps::SWAMP_BP);

    virtual ~SwampTileItem() = default;

    virtual unsigned int getMovementCost() const override;

    virtual std::string getType() const override;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    virtual void getDescriptionBrief(std::string &desc) override;
};

#endif // SWAMPTILEITEM_H
