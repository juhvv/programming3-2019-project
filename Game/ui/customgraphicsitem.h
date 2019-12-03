#ifndef CUSTOMGRAPHICSITEM_H
#define CUSTOMGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <string>
#include <QDebug>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <memory>

#include "gameobjectbase.h"

namespace shapePrefs {
    /**
     * @brief Type for defining item's shape (clickable area)
     */
    enum ShapePref {
        NO_SHAPE,   // item has no shape
        DEFAULT,    // QGraphicsPixmapItem::shape()
        SQUARE_128  // shape is 128x128px square
    };
}

/**
 * @brief The CustomGraphicsItem class
 */
class CustomGraphicsItem : public QGraphicsPixmapItem
{
public:
    CustomGraphicsItem() = delete;
    /**
     * @brief CustomGraphicsItem constructor
     * @param parentObject Parent GameObject
     * @param pixmap Pixmap to be used
     * @param parent Parent QGraphicsItem
     */
    explicit CustomGraphicsItem(std::shared_ptr<GameObjectBase> parentObject,
                                QPixmap pixmap = QPixmap(":/resources/tilebase.PNG"),
                                QGraphicsItem *parent = nullptr);

    virtual ~CustomGraphicsItem() = default;

    /**
     * @brief Defines shape (clickable area) for this item
     * @return QPainterPath defining shape
     */
    virtual QPainterPath shape() const override;

    /**
     * @brief Returns bool value whether this item's parent item is movable
     * @return bool value whether this item's parent item is movable
     */
    virtual bool isMovable();

    /**
     * @brief Retrieves this item's parent object's menu actions
     * @param menu QMenu that stores the menu actions
     */
    virtual void getMenuItems(QMenu &menu);

    /**
     * @brief Returns bool value whether this item is selectable
     * @return bool value whether this item is selectable
     */
    virtual bool isSelectable();

    /**
     * @brief Toggles this item's highlight state
     * @param state Bool value for highlight state
     */
    virtual void toggleHighlight(bool state) const;

    /**
     * @brief Returns this item's parent object
     * @return weakPtr to the parent object
     */
    std::weak_ptr<GameObjectBase> getParentObject() const;

    /**
     * @brief Sets this items ShapePref
     * @param shapePref ShapePref to be set
     */
    void setShapePref(const shapePrefs::ShapePref &shapePref);

private:
    std::weak_ptr<GameObjectBase> parentObject_;
    shapePrefs::ShapePref shapePref_ = shapePrefs::DEFAULT;
};

#endif // CUSTOMGRAPHICSITEM_H
