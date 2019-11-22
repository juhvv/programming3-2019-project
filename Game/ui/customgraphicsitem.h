#ifndef CUSTOMGRAPHICSITEM_H
#define CUSTOMGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <string>
#include <QDebug>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include "interfaces/igameeventhandler.h"
#include "core/playerbase.h"

class CustomGraphicsItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    CustomGraphicsItem() = delete;
    explicit CustomGraphicsItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);

    virtual ~CustomGraphicsItem() = default;

    // virtual QPainterPath shape() const override;

    virtual bool isMovable();

    virtual void getMenuItems(QMenu &menu) = 0;

    virtual bool isSelectable() {return true;}

    virtual Course::iGameEventHandler *getEventHandlerPtr() const {return NULL;}

public slots:
    void move();
};

#endif // CUSTOMGRAPHICSITEM_H
