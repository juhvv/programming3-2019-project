#ifndef CUSTOMGRAPHICSITEM_H
#define CUSTOMGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <string>
#include <QDebug>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
//#include "interfaces/igameeventhandler.h"
#include <memory>
#include "gameobjectbase.h"

enum ShapePref {
    NO_SHAPE,
    DEFAULT,
    SQUARE_128
};


class CustomGraphicsItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    CustomGraphicsItem() = delete;
    explicit CustomGraphicsItem(std::shared_ptr<GameObjectBase> parentObject,
                                QPixmap pixmap = QPixmap(":/resources/tilebase.PNG"),
                                QGraphicsItem *parent = nullptr);

    virtual ~CustomGraphicsItem() = default;

    virtual QPainterPath shape() const override;

    virtual bool isMovable();

    virtual void getMenuItems(QMenu &menu);

    virtual bool isSelectable();

    virtual void toggleHighlight(bool state) const;

    std::shared_ptr<GameObjectBase> getParentObject() const;

    void setShapePref(const ShapePref &shapePref);

private:
    // bool isMovable_;
    // bool isSelectable_;
    std::shared_ptr<GameObjectBase> parentObject_;
    ShapePref shapePref_ = DEFAULT;
};

#endif // CUSTOMGRAPHICSITEM_H
