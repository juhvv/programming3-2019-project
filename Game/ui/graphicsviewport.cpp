#include "graphicsviewport.h"
#include <QDebug>
#include <QWheelEvent>

GraphicsViewPort::GraphicsViewPort(QWidget* parent) :
    QGraphicsView (parent),
    zoomLevel_(1)
{
    setDragMode(QGraphicsView::ScrollHandDrag);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
}

void GraphicsViewPort::wheelEvent(QWheelEvent *event)
{
    //this->translate(1, 1);
    QPoint degrees = event->angleDelta();
    if (degrees.y() != 0) {
        zoom(event->pos(), degrees.y() > 0);
    }
}

/*
void GraphicsViewPort::scrollContentsBy(int dx, int dy)
{
    qDebug() << "Drag x y: " << dx << ", " << dy;
    //centerOn(x() + dx, y() + dy);
    this->updateSceneRect(sceneRect());
}
*/

void GraphicsViewPort::zoom(QPoint centerLoc, bool isZoomIn)
{
    qDebug() << "Zoomcoord: " << centerLoc;

    QPoint fromScene = mapFromScene(centerLoc);
    QPointF toScene = mapToScene(centerLoc);
    qDebug() << "Transformed Coord: " << fromScene;
    qDebug() << "Mapped from Coord: " << toScene.toPoint();

    // this->scene()->update(sceneRect());

    if (isZoomIn) {
        if (zoomLevel_ < 2) {
            zoomLevel_ *= 1.05;
            this->scale(1.05, 1.05);
            //centerOn(toScene.toPoint());
        }
    } else {
        if (zoomLevel_ > 0.3) {
            zoomLevel_ *= 0.95;
            this->scale(0.95, 0.95);
            // centerOn(toScene.toPoint());
        }
    }

}
