#ifndef GRAPHICSVIEWPORT_H
#define GRAPHICSVIEWPORT_H

#include <QObject>
#include <QGraphicsView>


/**
 * @brief The GraphicsViewPort class is a custom QGraphicsview class for displaying the game scene
 */
class GraphicsViewPort : public QGraphicsView
{
    Q_OBJECT
public:
    /**
     * @brief GraphicsViewPort constructor
     * @param parent pointer to parent QWidget
     */
    explicit GraphicsViewPort(QWidget* parent = 0);

    virtual ~GraphicsViewPort() = default;

    /**
     * @brief This method handles QWheelEvents to zoom the view
     * @param event QWheelEvent to be handled
     */
    virtual void wheelEvent(QWheelEvent *event) override;

public slots:
    /**
     * @brief Zooms the view 5% either in or out
     * @param isZoomIn Defines direction of zoom, true zooms in
     */
    void zoom(bool isZoomIn);

private:
    double zoomLevel_;
};

#endif // GRAPHICSVIEWPORT_H
