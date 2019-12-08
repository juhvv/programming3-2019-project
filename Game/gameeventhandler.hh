#ifndef GAMEEVENTHANDLER_HH
#define GAMEEVENTHANDLER_HH

#include <QObject>
#include <QMainWindow>
#include <QTextBrowser>
#include <QDebug>
#include <QPushButton>
#include <vector>
#include "player.hh"
#include "interfaces/igameeventhandler.h"
#include "tiles/tilebase.h"
#include "tiles/graphicstilebase.h"
#include "objectmanager.hh"
#include "workers/basicworker.h"
#include "unitconstructor.h"
#include "startwindow.hh"


class GameEventHandler :
        public QObject, public Course::iGameEventHandler
{
    Q_OBJECT
public:
    explicit GameEventHandler(std::shared_ptr<ObjectManager> objectMngr,
                              std::weak_ptr<UnitConstructor> unitConstructor);

    virtual ~GameEventHandler() = default;


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
     virtual bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                Course::BasicResource resource,
                                int amount) final;

    virtual bool modifyResource(std::shared_ptr<Player> player,
                               Course::BasicResource resource,
                               int amount) final;


    /**
     * @brief Modify Player's resources. Can be used to both sum or subtract
     * @param player Pointer to the Player whose resources are being modified.
     * @param resources ResourceMap containing change amounts.
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    virtual bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                 Course::ResourceMap resources) final;

    /**
     * @brief Modify Player's resources. Can be used to both sum or subtract
     * @param player Sharedptr to the Player whose resources are being modified.
     * @param resources ResourceMap containing change amounts.
     * @return
     * True - Modification was succesful. \n
     * False - Modification failed. \n
     */
    virtual bool modifyResources(std::shared_ptr<Player> player,
                                 Course::ResourceMap resources) final;

    /**
     * @brief Switches to next turn. Handles player and game data updating
     */
    void nextTurn();

    /**
     * @brief Calculates production for current player
     * @return ResourceMap containing calculated production
     */
    Course::ResourceMap calculateProduction();

    /**
     * @brief Calculates and adds production for current player.
     */
    void calculateAddProduction();

    /**
     * @brief Returns current turn number
     * @return Current turn number
     */
    unsigned int getTurnNumber();

    /**
     * @brief Sets current player to desired player.
     * @param currentPlayer Name of the new current player
     */
    void setCurrentPlayer(std::string currentPlayer);

    /**
     * @brief Sets turn number to desired value.
     * @param turn New turn number
     */
    void setTurnNumber(unsigned int turn);

    /**
     * @brief Searches player by name.
     * @param playerName Name of the player to be searched.
     * @return Sharedptr to player, nullptr if player was not found.
     */
    std::shared_ptr<Player> getPlayerFromName(std::string playerName);

    /**
     * @brief Sets the eventhandler's list of players
     * @param playerVector New players as sharedptrs in a vector
     */
    void addPlayerVector(std::vector<std::shared_ptr<Player> > playerVector);

    /**
     * @brief Inquires current player
     * @return Sharedptr to current player
     */
    std::shared_ptr<Player> getCurrentPlayer();

    /**
     * @brief Inquires eventhandler's player list
     * @return Vector containing sharedptrs to players.
     */
    std::vector<std::shared_ptr<Player>> getPlayerVector();

    /**
     * @brief Adds new players to eventhandler.
     * @param nameVct Pairs of player names as strings and corresponding icon index in a vector.
     * @param mapSize Map's x and y size in tiles
     * @note Currently other player needs to have icon index of 0,
     * \n while the other has index bigger than zero in order to have different icons.
     */
    void addNewPlayers(std::vector<std::pair<std::string, int>> nameVct, MapSize::Size mapSize);

    /**
     * @brief Deletes current players and clears objectmanager's all data aswell.
     */
    void resetData();

    /**
     * @brief Check if game should end based on the win conditions
     * @param endMessage Message that is displayed when game ends.
     */
    void isGameOver(std::string endMessage);

    /**
     * @brief Adds new unit, which is specified by template parameter, to a player.
     * @param tile Location for new unit as sharedptr to tile
     * @param player New unit's owner. If not provided, current player is set as owner.
     */
    template<typename unitType>
    void addUnit(std::shared_ptr<GraphicsTileBase> tile, std::shared_ptr<Player> player = nullptr) {
        if (player == nullptr) {
            player = currentPlayer_;
        }

        std::shared_ptr<unitType> newUnit = unitConstructor_.lock()->constructUnit<unitType>(player);

        if (newUnit) {
            std::shared_ptr<GameObjectBase> unitObject = std::dynamic_pointer_cast<GameObjectBase>(newUnit);
            objectMngr_->setGraphicsObject(unitObject);

            player->addUnit(newUnit);
            newUnit->moveToTile(tile, true);

        }
        else {
            qDebug() << "addUnit: Could not construct new unit";
        }
    }

    /**
     * @brief Adds new building, which is specified by template parameter, to a player.
     * @param tile Location for new building as sharedptr to tile
     * @param player New building's owner. If not provided, current player is set as owner.
     */
    template <typename buildingType>
    void addBuilding(std::shared_ptr<GraphicsTileBase> tile, std::shared_ptr<Player> player = nullptr)
    {
        if (player == nullptr) {
            player = currentPlayer_;
        }
        std::shared_ptr<buildingType> startBuilding =
                unitConstructor_.lock()->constructBuilding<buildingType>(player);
        std::shared_ptr<GameObjectBase> gameObject = std::dynamic_pointer_cast<GameObjectBase>(startBuilding);

        tile->addBuilding(startBuilding);
        player->addNewBuilding(startBuilding);
        objectMngr_->setGraphicsObject(gameObject);
    }

    /**
     * @brief Inserts message to the ui's messagebox.
     * @param msg Message as string
     */
    void sendMsg(std::string msg);

    /**
     * @brief Re-calculates and updates players' resources
     */
    void updateVisibleResources();


public slots:
    /**
     * @brief Sets new owner and owner marker for a tile.
     * @param tile Tile to be claimed
     * @param player Tile's new owner. If not provided, current player is set as owner.
     */
    void claimTile(GraphicsTileBase *tile, std::shared_ptr<Player> player=nullptr);

signals:
    /**
     * @brief Signal that is emitted when ui's resource labels should update.
     */
    void signalUpdateVisibleResources();

    /**
     * @brief Signal that is emitted when new message should be displayed in ui's textbox.
     * @param msg Message to be displayed as a string
     */
    void signalSendMsg(std::string &msg);

private:
    unsigned int turnNumber_;   // current turn number
    unsigned int maxTurns_; // maximum turn numbers

    std::shared_ptr<ObjectManager> objectMngr_; // ptr to objectmanager used

    std::vector<std::shared_ptr<Player>> playerVector_; // current players
    std::shared_ptr<Player> currentPlayer_; // current player

    std::weak_ptr<UnitConstructor> unitConstructor_; // ptr to unitconstructor

};

#endif // GAMEEVENTHANDLER_HH
