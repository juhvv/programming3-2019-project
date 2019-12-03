#ifndef TILEOVERLAYITEM_H
#define TILEOVERLAYITEM_H

#include <QGraphicsPixmapItem>

/**
 * @brief The TileOverlayItem is a non-clikable version of QGraphicsPixmapItem.
 */
class TileOverlayItem : public QGraphicsPixmapItem
{
public:
    TileOverlayItem() = delete;

    virtual ~TileOverlayItem() = default;
    explicit TileOverlayItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);

    /**
      * @copydoc QGraphicsPixmapItem::shape()
     */
    virtual QPainterPath shape() const override;
};

#endif // TILEOVERLAYITEM_H
