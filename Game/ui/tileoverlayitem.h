#ifndef TILEOVERLAYITEM_H
#define TILEOVERLAYITEM_H

#include <QGraphicsPixmapItem>

class TileOverlayItem : public QGraphicsPixmapItem
{
public:
    TileOverlayItem() = delete;

    virtual ~TileOverlayItem() = default;
    explicit TileOverlayItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);

    virtual QPainterPath shape() const override;
};

#endif // TILEOVERLAYITEM_H
