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
    if (shapePref_ == shapePrefs::DEFAULT) {
        return QGraphicsPixmapItem::shape();

    } else if (shapePref_ == shapePrefs::NO_SHAPE) {
        QRectF shapeRect = QRectF(0,0,0,0);
        QPainterPath shapePath;
        shapePath.addRect(shapeRect);
        return shapePath;

    } else if (shapePref_ == shapePrefs::SQUARE_128) {
        QRectF shapeRect = QRectF(0,0,128,128);
        QPainterPath shapePath;
        shapePath.addRect(shapeRect);
        return shapePath;

    }
    return QGraphicsPixmapItem::shape();
}



bool CustomGraphicsItem::isMovable()
{
    return parentObject_.lock()->isMovable();
}

void CustomGraphicsItem::getMenuItems(QMenu &menu)
{
    parentObject_.lock()->getMenuItems(menu);
}

bool CustomGraphicsItem::isSelectable()
{
    return parentObject_.lock()->isSelectable();
}

void CustomGraphicsItem::toggleHighlight(bool state) const
{
    QGraphicsEffect* effect = graphicsEffect();
    if (effect != nullptr) {
        effect->setEnabled(state);
    }

}

std::weak_ptr<GameObjectBase> CustomGraphicsItem::getParentObject() const
{
    return parentObject_;
}

void CustomGraphicsItem::setShapePref(const shapePrefs::ShapePref &shapePref)
{
    shapePref_ = shapePref;
}

