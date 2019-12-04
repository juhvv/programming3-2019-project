#ifndef WORKER_H
#define WORKER_H

#include "units/graphicsunitbase.h"

/**
 * @brief The Worker class implements worker unit. It generates resources working on tile it
 * \n is placed on. It has 4 move points.
 */
class Worker : public GraphicsUnitBase
{
public:
    Worker() = delete ;
    /**
     * @brief Constructor
     * @param eventhandler Ptr to EventHandler
     * @param objectmanager Ptr to ObjectManager
     * @param owner Ptr to this unit's owner
     * @param scene Ptr to CustomGraphicsScene
     * @param tilespaces How much space this unit takes on a tile
     * @param cost ResourceMap specifying unit construction cost
     * @param efficiency ResourceMap specifying worker efficiency
     */
    explicit Worker(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                        const std::shared_ptr<Course::iObjectManager>& objectmanager,
                        const std::shared_ptr<Course::PlayerBase>& owner,
                        CustomGraphicsScene* scene = nullptr,
                        const int& tilespaces = 1,
                        const Course::ResourceMap& cost = GameConstResourceMaps::BW_RECRUITMENT_COST,
                        const Course::ResourceMapDouble& efficiency = GameConstResourceMaps::BW_WORKER_EFFICIENCY);

    virtual ~Worker() = default;

    /**
     * @copydoc GraphicsUnitBase::switchTurn()
     */
    virtual void switchTurn() override;

    virtual const Course::ResourceMapDouble tileWorkAction() override;

    /**
     * @copydoc GameObjectBase::setGraphicsItem
     */
    virtual void setGraphicsItem(CustomGraphicsItem *graphicsItem, CustomGraphicsScene *scene) override;

    /**
     * @copydoc GameObjectBase::getType
     */
    virtual std::string getType() const override;

    /**
     * @copydoc GameObjectBase::getDescriptionBrief
     */
    virtual void getDescriptionBrief(std::string &desc) override;
};

#endif // WORKER_H
