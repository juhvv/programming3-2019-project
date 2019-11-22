#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include "tiles/graphicstilebase.h"

class CustomGraphicsScene : public QGraphicsScene
{
public:
    CustomGraphicsScene(QObject *parent = nullptr);

    virtual ~CustomGraphicsScene() = default;

    void setupMap(const std::vector<std::shared_ptr<Course::TileBase>>& tiles);

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent) override;


    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

public slots:
    void enterMovementMode();

protected:
    bool movementModeFlag_ = false;
    CustomGraphicsItem *lastClickedItem_ = NULL;
};

#endif // CUSTOMGRAPHICSSCENE_H
