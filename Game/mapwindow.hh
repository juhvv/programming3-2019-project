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

class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = 0);
    ~MapWindow();

    void setGEHandler(std::shared_ptr<Course::iGameEventHandler> nHandler);

public slots:
    void updateVisibleResources();
    void showSaveWindow();
    void showLoadWindow();
    void showStartWindow();
    void switchTurn();
    void startNewGame(playerInfo info, unsigned int seed, MapSize::Size size);
    void sendMsgSlot(std::string &msg);

private:
    Ui::MapWindow* m_ui;

    GraphicsViewPort* viewPortPtr_;
    CustomGraphicsScene* scenePtr_;

    std::shared_ptr<GameEventHandler> eventhandler_;
    std::shared_ptr<ObjectManager> objectManager_;
    std::shared_ptr<UnitConstructor> unitConstructor_;

};

#endif // MapWINDOW_HH

