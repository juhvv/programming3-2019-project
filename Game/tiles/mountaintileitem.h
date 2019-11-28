#ifndef MOUNTAINTILEITEM_H
#define MOUNTAINTILEITEM_H


#include "tiles/graphicstilebase.h"

class MountainTileItem : public GraphicsTileBase
{
public:
    MountainTileItem() = delete ;
    explicit MountainTileItem(const Course::Coordinate& location,
                              const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                              const std::shared_ptr<Course::iObjectManager>& objectmanager,
                              CustomGraphicsScene* scene = nullptr,
                     const unsigned int& max_build = 1,
                     const unsigned int& max_work = 3,
                            const Course::ResourceMap& production = Course::ConstResourceMaps::FOREST_BP);

    virtual ~MountainTileItem() = default;

    virtual unsigned int getMovementCost() const override;

    virtual std::string getType() const override;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

public slots:
    // virtual void sendInfo() override;
};

#endif // MOUNTAINTILEITEM_H
