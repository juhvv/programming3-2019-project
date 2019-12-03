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
    QPoint degrees = event->angleDelta();
    if (degrees.y() != 0) {
        zoom(degrees.y() > 0);
    }
}

void GraphicsViewPort::zoom(bool isZoomIn)
{
    if (isZoomIn) {
        if (zoomLevel_ < 2) {
            zoomLevel_ *= 1.05;
            this->scale(1.05, 1.05);

        }
    } else {
        if (zoomLevel_ > 0.3) {
            zoomLevel_ *= 0.95;
            this->scale(0.95, 0.95);

        }
    }
}
