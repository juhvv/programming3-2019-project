#ifndef SCOUT_H
#define SCOUT_H

#include "units/graphicsunitbase.h"

/**
 * @brief The Scout class implements scout unit. It has 4 move points and can claim tiles and
 * \n construct outpost buildings.
 */
class Scout : public GraphicsUnitBase
{
public:
    Scout() = delete ;

    /**
     * @brief Constructor
     * @param eventhandler Ptr to EventHandler
     * @param objectmanager Ptr to ObjectManager
     * @param owner Ptr to this unit's owner
     * @param scene Ptr to CustomGraphicsScene
     * @param tilespaces How much space this unit takes on a tile
     * @param cost ResourceMap specifying unit construction cost
     * @param efficiency ResourceMap specifying worker efficiency (Not used)
     */
    explicit Scout(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                        const std::shared_ptr<Course::iObjectManager>& objectmanager,
                        const std::shared_ptr<Course::PlayerBase>& owner,
                        CustomGraphicsScene* scene = nullptr,
                        const int& tilespaces = 1,
                        const Course::ResourceMap& cost = GameConstResourceMaps::SCOUT_COST,
                        const Course::ResourceMapDouble& efficiency = {});

    virtual ~Scout() = default;

    /**
     * @copydoc GameObjectBase::getMenuItems(QMenu &menu)
     */
    virtual void getMenuItems(QMenu &menu) override;

    /**
     * @copydoc GraphicsUnitBase::switchTurn()
     */
    virtual void switchTurn() override;

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

private slots:
    /**
     * @brief Claims tile this unit is located on
     */
    void claimActionSlot();

    /**
     * @brief Constructs Outpost building on current tile
     */
    void buildCampActionSlot();
};

#endif // SCOUT_H
