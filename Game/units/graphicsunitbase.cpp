#include "graphicsunitbase.h"


GraphicsUnitBase::GraphicsUnitBase(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                                   const std::shared_ptr<Course::iObjectManager> &objectmanager,
                                   const std::shared_ptr<Course::PlayerBase> &owner,
                                   const QPixmap &pixmap, QGraphicsItem *parent,
                                   const int &tilespaces,
                                   const Course::ResourceMap &cost,
                                   const Course::ResourceMapDouble &efficiency) :
    CustomGraphicsItem (pixmap, parent),
    Course::WorkerBase (eventhandler, objectmanager, owner)
{
    setZValue(5);
}

bool GraphicsUnitBase::isMovable()
{
    return true;
}

void GraphicsUnitBase::getMenuItems(QMenu &menu)
{
    QAction* infoAction = menu.addAction("Info");
}

void GraphicsUnitBase::doSpecialAction()
{

}
