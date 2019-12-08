#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include <map>

#include "interfaces/igameeventhandler.h"
#include "graphics/simplegamescene.h"
#include "ui/graphicsviewport.h"
#include "tiles/graphicstilebase.h"
#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "startwindow.hh"
#include "ui/customgraphicsscene.h"
#include "unitconstructor.h"
#include "savewindow.hh"
#include "loadwindow.hh"
#include "savegame.hh"
#include "loadgame.hh"


namespace Ui {
class MapWindow;
}
/**
 * @brief This is mainwindow that shows map, player's resources, and have buttons for actions.
 */
class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = 0);
    ~MapWindow();

public slots:
    /**
     * @brief Updates resources and player name that are shown in MapWindow for current player
     */
    void updateVisibleResources();
    /**
     * @brief Opens SaveWindow window that asks player for save file directory
     */
    void showSaveWindow();
    /**
     * @brief Opens LoadWindow window that asks player for load file directory
     */
    void showLoadWindow();
    /**
     * @brief Opens StartWindow window
     */
    void showStartWindow();
    /**
     * @brief Calls eventhandler to switch turn, and also shows turn changed message
     */
    void switchTurn();
    /**
     * @brief Starts new game. Calls for generaion of map. Assigns new player to eventhandler.
     * @param info vector of name of players and their factions
     * @param seed of map
     * @param size of map
     */
    void startNewGame(playerInfo info, unsigned int seed, MapSize::Size size);
    /**
     * @brief Shows message on textBox on mapwindow.
     * @param msg a message to be shown
     */
    void sendMsgSlot(std::string &msg);

    /**
     * @brief Changes mode of next button pressable or unpressable
     * @param buttonMode true changes button pressable, false makes button unpressable
     */
    void nextButtonMode(bool buttonMode);

private:
    Ui::MapWindow* m_ui;

    GraphicsViewPort* viewPortPtr_;
    CustomGraphicsScene* scenePtr_;

    std::shared_ptr<GameEventHandler> eventhandler_;
    std::shared_ptr<ObjectManager> objectManager_;
    std::shared_ptr<UnitConstructor> unitConstructor_;

};

#endif // MapWINDOW_HH

