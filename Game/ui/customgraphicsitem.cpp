#include "customgraphicsitem.h"
#include <QGraphicsEffect>

CustomGraphicsItem::CustomGraphicsItem(const QPixmap &pixmap, QGraphicsItem *parent) :
    QGraphicsPixmapItem (pixmap, parent)
{
    setCursor(Qt::PointingHandCursor);
    QGraphicsColorizeEffect* highlightEffect = new QGraphicsColorizeEffect();
    highlightEffect->setColor(QColor(0,255,0));
    highlightEffect->setStrength(0.5);
    setGraphicsEffect(highlightEffect);
    highlightEffect->setEnabled(false);
}



bool CustomGraphicsItem::isMovable()
{
    return true;
}

void CustomGraphicsItem::toggleHighlight(bool state) const
{
    QGraphicsEffect* effect = graphicsEffect();
    if (effect != nullptr) {
        effect->setEnabled(state);
    }

}

/*
void CustomGraphicsItem::showContextMenu(QGraphicsSceneContextMenuEvent *contextEvent)
{
    contextMenuEvent(contextEvent);
}
*/
void CustomGraphicsItem::move()
{
    QPointF newPoint = QPointF(x()+1, y()+1);
    this->setPos(newPoint);
}

