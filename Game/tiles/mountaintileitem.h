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
                     const QPixmap &pixmap = QPixmap(":/resources/mountains.PNG"),
                     QGraphicsItem *parent = nullptr,
                     const unsigned int& max_build = 2,
                     const unsigned int& max_work = 3,
                            const Course::ResourceMap& production = Course::ConstResourceMaps::FOREST_BP);

    virtual ~MountainTileItem() = default;

    // virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    // virtual QRectF boundingRect() const override;

    virtual std::string getType() const override;

public slots:
    // virtual void sendInfo() override;
};

#endif // MOUNTAINTILEITEM_H
