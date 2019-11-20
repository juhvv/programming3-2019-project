#ifndef CUSTOMGRAPHICSITEM_H
#define CUSTOMGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <string>
#include <QDebug>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

class CustomGraphicsItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    CustomGraphicsItem() = delete;
    explicit CustomGraphicsItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);

    virtual QPainterPath shape() const override;

public slots:
    void move();
};

#endif // CUSTOMGRAPHICSITEM_H
