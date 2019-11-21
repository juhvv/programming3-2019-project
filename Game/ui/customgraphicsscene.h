#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include "tiles/graphicstilebase.h"

class CustomGraphicsScene : public QGraphicsScene
{
public:
    CustomGraphicsScene(QObject *parent = nullptr);

    void setupMap(const std::vector<std::shared_ptr<Course::TileBase>>& tiles);
};

#endif // CUSTOMGRAPHICSSCENE_H
