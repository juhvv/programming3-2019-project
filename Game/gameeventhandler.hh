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
     bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
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
     bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                 Course::ResourceMap resources);


    void nextTurn();    // called when a turn ends

    Course::ResourceMap calculateProduction(); //calculates production for current player

    void calculateAddProduction(); //calculates and adds production for current player

    unsigned int getTurnNumber();   // returns current turn number

    void setCurrentPlayer(std::string currentPlayer);

    void addPlayerVector(std::vector<std::shared_ptr<Player> > playerVector);

    std::shared_ptr<Player> getCurrentPlayer();

    std::vector<std::shared_ptr<Player>> getPlayerVector();

    void addNewPlayers(std::vector<std::pair<std::string, int>>); //adds new players to the game

    void resetData();   // resets stored data

    template<typename unitType>
    void addUnit(std::shared_ptr<GraphicsTileBase> tile, std::shared_ptr<Player> player = nullptr) {
        if (player == nullptr) {
            player = currentPlayer_;
        }
        //std::shared_ptr<GraphicsTileBase> tile =
                //std::dynamic_pointer_cast<GraphicsTileBase>(objectMngr_->getTile(TileId));

        std::shared_ptr<unitType> newUnit = unitConstructor_.lock()->constructUnit<unitType>(player);

        if (newUnit) {
            qDebug() << newUnit->getType().c_str();
            std::shared_ptr<GameObjectBase> unitObject = std::dynamic_pointer_cast<GameObjectBase>(newUnit);
            objectMngr_->setGraphicsObject(unitObject);
            newUnit->moveToTile(tile, true);

        }
        else {
            qDebug() << "Could not construct new unit";
        }
        std::shared_ptr<GraphicsUnitBase> newGameObject =
                std::dynamic_pointer_cast<GraphicsUnitBase>(newUnit);
        player->addUnit(newGameObject);
    }

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

    void sendMsg(std::string msg);


public slots:
    void claimTile(GraphicsTileBase *tile);

signals:
    void signalUpdateVisibleResources();
    void signalSendMsg(std::string &msg);

private:
    unsigned int turnNumber_;
    unsigned int maxTurns_;

    std::shared_ptr<ObjectManager> objectMngr_;

    std::vector<std::shared_ptr<Player>> playerVector_;
    std::shared_ptr<Player> currentPlayer_;

    std::weak_ptr<UnitConstructor> unitConstructor_;

};

#endif // GAMEEVENTHANDLER_HH
