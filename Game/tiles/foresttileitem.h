#ifndef FORESTTILEITEM_H
#define FORESTTILEITEM_H

#include "tiles/graphicstilebase.h"

class ForestTileItem : public GraphicsTileBase
{
public:
    ForestTileItem() = delete ;
    explicit ForestTileItem(const Course::Coordinate& location,
                            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                            const std::shared_ptr<Course::iObjectManager>& objectmanager,
                            CustomGraphicsScene* scene = nullptr,
                     const unsigned int& max_build = 1,
                     const unsigned int& max_work = 3,
                            const Course::ResourceMap& production = Course::ConstResourceMaps::FOREST_BP);

    virtual ~ForestTileItem() = default;

    virtual unsigned int getMovementCost() const override;

    // virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    // virtual QRectF boundingRect() const override;

    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    virtual std::string getType() const override;

    virtual void getDescriptionBrief(std::string &desc) override;

public slots:
    // virtual void sendInfo() override;
};

#endif // FORESTTILEITEM_H
