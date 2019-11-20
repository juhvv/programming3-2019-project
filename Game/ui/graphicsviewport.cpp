#include "graphicsviewport.h"
#include <QDebug>
#include <QWheelEvent>

GraphicsViewPort::GraphicsViewPort(QWidget* parent) :
    QGraphicsView (parent),
    zoomLevel_(1)
{

}

void GraphicsViewPort::wheelEvent(QWheelEvent *event)
{
    QPoint degrees = event->angleDelta();
    qDebug() << "Degrees: " << degrees.x() << ", " << degrees.y();
    if (degrees.y() != 0) {
        zoom(event->pos(), degrees.y() > 0);
    }
}

void GraphicsViewPort::zoom(QPoint centerLoc, bool isZoomIn)
{
    if (isZoomIn) {
        if (zoomLevel_ < 2) {
            zoomLevel_ *= 1.1;
            this->scale(1.1, 1.1);
            centerOn(centerLoc);
            qDebug() << "Zoomed in";
        }
    } else {
        if (zoomLevel_ > 0.5) {
            zoomLevel_ *= 0.9;
            this->scale(0.9, 0.9);
            centerOn(centerLoc);
            qDebug() << "Zoomed out";
        }
    }
}

