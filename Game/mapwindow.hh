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

    //D void setSize(int width, int height);
    //D void setScale(int scale);
    //D void resize();

    //D void drawItem( std::shared_ptr<Course::GameObject> obj);
    //D void removeItem( std::shared_ptr<Course::GameObject> obj);
    //D void updateItem( std::shared_ptr<Course::GameObject> obj);

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

    //D std::shared_ptr<Course::iGameEventHandler> m_GEHandler = nullptr;
    std::shared_ptr<GameEventHandler> eventhandler_;
    std::shared_ptr<ObjectManager> objectManager_;
    //D std::shared_ptr<Course::SimpleGameScene> gameScene_ = nullptr;
    std::shared_ptr<UnitConstructor> unitConstructor_;

};

#endif // MapWINDOW_HH

