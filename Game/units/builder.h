#ifndef BUILDER_H
#define BUILDER_H

#include "units/graphicsunitbase.h"
#include "gameeventhandler.hh"

/**
 * @brief The Builder class implements builder unit to the game. It has movement 2 move points and
 * \n provides building construction functionality.
 */
class Builder : public GraphicsUnitBase
{
public:
    Builder() = delete ;

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
    explicit Builder(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                        const std::shared_ptr<Course::iObjectManager>& objectmanager,
                        const std::shared_ptr<Course::PlayerBase>& owner,
                        CustomGraphicsScene* scene = nullptr,
                        const int& tilespaces = 1,
                        const Course::ResourceMap& cost = GameConstResourceMaps::BUILDER_COST,
                        const Course::ResourceMapDouble& efficiency = {});

    virtual ~Builder() = default;

    /**
     * @copydoc GameObjectBase::getMenuItems(QMenu &menu)
     */
    virtual void getMenuItems(QMenu &menu) override;

    /**
     * @brief Adds build actions to the passed menu. Impossible build options will be disabled.
     * @param bmenu QMenu for the actions
     */
    virtual void getBuildMenu(QMenu &bmenu);

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
     * @brief Constructs building specified by templater parameter on current tile.
     */
    template<typename BuildingType>
    void buildSlot() {
        std::shared_ptr<GameEventHandler> handler =
                std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());


        handler->addBuilding<BuildingType>(getCurrentTile(),
                                           std::dynamic_pointer_cast<Player>(getOwner()));
        movePoints_ = 0;
    }
};

#endif // BUILDER_H
