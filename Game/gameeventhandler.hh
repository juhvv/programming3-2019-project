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

class GameEventHandler : public QObject, public Course::iGameEventHandler
{
    Q_OBJECT
public:
    explicit GameEventHandler(std::shared_ptr<ObjectManager> objectMngr);

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

    unsigned int getTurnNumber();   // returns current turn number

    std::shared_ptr<Player> getCurrentPlayer();

    void addNewPlayers(std::vector<std::pair<std::string, int>>); //adds new players to the game

    void resetData();   // resets stored data

public slots:
    void claimTile(GraphicsTileBase *tile);


private:
    unsigned int turnNumber_;
    unsigned int maxTurns_;
    std::shared_ptr<ObjectManager> objectMngr_;

    std::vector<std::shared_ptr<Player>> playerVector_;
    std::shared_ptr<Player> currentPlayer_;

};

#endif // GAMEEVENTHANDLER_HH
