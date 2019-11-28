#include "customgraphicsitem.h"
#include <QGraphicsEffect>

CustomGraphicsItem::CustomGraphicsItem( std::shared_ptr<GameObjectBase> parentObject,
                                         QPixmap pixmap,
                                       QGraphicsItem *parent) :
    QGraphicsPixmapItem (pixmap, parent),
    parentObject_(parentObject)
{
    setCursor(Qt::PointingHandCursor);

    QGraphicsColorizeEffect* highlightEffect = new QGraphicsColorizeEffect();
    highlightEffect->setColor(QColor(0,255,0));
    highlightEffect->setStrength(0.4);
    setGraphicsEffect(highlightEffect);
    highlightEffect->setEnabled(false);
}

QPainterPath CustomGraphicsItem::shape() const
{
    if (shapePref_ == DEFAULT) {
        return QGraphicsPixmapItem::shape();

    } else if (shapePref_ == NO_SHAPE) {
        QRectF shapeRect = QRectF(0,0,0,0);
        QPainterPath shapePath;
        shapePath.addRect(shapeRect);
        return shapePath;

    } else if (shapePref_ == SQUARE_128) {
        QRectF shapeRect = QRectF(0,0,128,128);
        QPainterPath shapePath;
        shapePath.addRect(shapeRect);
        return shapePath;

    }
    return QGraphicsPixmapItem::shape();
}



bool CustomGraphicsItem::isMovable()
{
    return parentObject_->isMovable();
}

void CustomGraphicsItem::getMenuItems(QMenu &menu)
{
    parentObject_->getMenuItems(menu);
}

bool CustomGraphicsItem::isSelectable()
{
    return parentObject_->isSelectable();
}

void CustomGraphicsItem::toggleHighlight(bool state) const
{
    QGraphicsEffect* effect = graphicsEffect();
    if (effect != nullptr) {
        effect->setEnabled(state);
    }

}

std::shared_ptr<GameObjectBase> CustomGraphicsItem::getParentObject() const
{
    return parentObject_;
}

void CustomGraphicsItem::setShapePref(const ShapePref &shapePref)
{
    shapePref_ = shapePref;
}

