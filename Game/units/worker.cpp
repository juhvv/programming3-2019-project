#include "worker.h"
#include "ui/customgraphicsscene.h"

Worker::Worker(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
               const std::shared_ptr<Course::iObjectManager> &objectmanager,
               const std::shared_ptr<Course::PlayerBase> &owner,
               CustomGraphicsScene *scene,
               const int &tilespaces,
               const Course::ResourceMap &cost,
               const Course::ResourceMapDouble &efficiency) :
    GraphicsUnitBase (eventhandler, objectmanager, owner, scene, tilespaces, cost, efficiency)
{
    movePoints_ = Units::LONGRANGE;
}

void Worker::switchTurn()
{
    GraphicsUnitBase::switchTurn();
    movePoints_ = Units::LONGRANGE;
}

const Course::ResourceMapDouble Worker::tileWorkAction()
{
    auto player = getOwner();
        auto events = lockEventHandler();
        double satisfaction = 0;
        Course::BasicResource focus = getResourceFocus();

        Course::ResourceMapDouble final_modifier;

        if ( events->modifyResource(player, Course::BasicResource::FOOD, -1) )
        {
            satisfaction = 0.5;
            if ( events->modifyResource(player, Course::BasicResource::MONEY, -1) )
            {
                satisfaction = 1;
            }
        }

        if( focus != Course::BasicResource::NONE )
        {
            final_modifier[focus] =
                    WORKER_EFFICIENCY.at(focus) * (satisfaction + 0.25);
        }
        else
        {
            for( auto it = WORKER_EFFICIENCY.begin();
                 it != WORKER_EFFICIENCY.end();
                 ++it )
            {
                final_modifier[it->first] = it->second * satisfaction;
            }
        }

        return final_modifier;
}

void Worker::setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene)
{
    GraphicsUnitBase::setGraphicsItem(graphicsItem, scene);
    graphicsItem_->setPixmap(QPixmap(":/resources/units/worker.PNG"));
    graphicsItem_->setOffset(-50,0);
    scene_->update();
}

std::string Worker::getType() const
{
    return "Worker";
}

void Worker::getDescriptionBrief(std::string &desc)
{
    desc += "\n A hard-working fellow.";
}
