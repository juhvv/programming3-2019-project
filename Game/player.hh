#ifndef PLAYER_HH
#define PLAYER_HH

#include "core/playerbase.h"
#include "core/gameobject.h"
#include <QPixmap>
#include "core/basicresources.h"
#include "ui/customgraphicsitem.h"
#include "buildings/gamebuildingbase.h"
#include <units/graphicsunitbase.h>

/**
 * @brief The Player class stores player's name, icon, units, buildings and resources
 * \n and provides methods for modifying this data
 */
class Player : public Course::PlayerBase
{
public:
    /**
      * @brief constructor
      * @param name Player name
      * @param startingResources Initial resources
      * @param objects Initial game objects
      */
    explicit Player(const std::string& name, Course::ResourceMap startingResources,
           const std::vector<std::shared_ptr<Course::GameObject> > objects ={});

    virtual ~Player() = default;

    /**
     * @brief Sets player's marker
     * @param index 0 or 1
     * @note Since there are currently only 2 different markers, all index values above
     * \n 0 will set marker 2 while 0 sets marker 1.
     */
    void setMarker(int index);

    /**
     * @brief Retrieves player's marker icon
     * @param icon QPixmap object whicsh stores the icon
     */
    void getIcon(QPixmap &icon);

    /**
     * @brief Deletes player's units and buildings
     */
    void resetData();

    /**
     * @brief Modify Player's resource. Can be used to both sum or subtract.
     * @param player Pointer to the Player whose resource is being modified.
     * @param resource Defines the modified resource.
     * @param amount Defines the amount of change.
     * @post Exception guarantee: Basic
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    bool modifyResource(Course::BasicResource resource, int amount);

    /**
     * @brief  Modify Player's resources. Can be used to both sum or subtract.
     * @param resources Defines modified resources
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    bool modifyResources(Course::ResourceMap resources);

    /**
     * @brief Returns amount of specified resource
     * @param resource Resource to be inquired
     * @return Amount of param resource
     */
    int getResourceValue(Course::BasicResource resource);

    /**
     * @brief Returns player's resource map
     * @return Player's resource map
     */
    Course::ResourceMap getResourceMap();

    /**
     * @brief Adds new unit to this player's units
     * @param newUnit Unit to be added
     */
    void addUnit(std::shared_ptr<GraphicsUnitBase> newUnit);

    /**
     * @brief Adds new building for this player
     * @param newBuilding Building to be added
     */
    void addNewBuilding(std::shared_ptr<GameBuildingBase> newBuilding);

    /**
     * @brief Searches this players units for unit with specified ID
     * @param ID ID to be searched
     * @return Pointer to unit, nullptr if unit is not found
     */
    std::shared_ptr<GraphicsUnitBase> getUnitById(unsigned int ID);

    /**
     * @brief Returns vector containing this player's all units
     * @return Vector containing pointers to the units
     */
    std::vector<std::shared_ptr<GraphicsUnitBase> > getPlayerUnits();

    /**
     * @brief Returns vector containing this player's all buildings
     * @return Vector containing pointers to the buildings
     */
    std::vector<std::shared_ptr<GameBuildingBase> > getPlayerBuildings() const;

private:
    std::string m_name;
    QPixmap marker_;
    Course::ResourceMap m_playerResources;
    std::vector<std::shared_ptr<GraphicsUnitBase>> playerUnits_ = {};
    std::vector<std::shared_ptr<GameBuildingBase>> playerBuildings_ =  {};
};

#endif // PLAYER_HH
