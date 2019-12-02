#include <math.h>
#include <QAction>
#include <QScrollBar>

#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "graphics/simplemapitem.h"
#include "startwindow.hh"
#include "core/worldgenerator.h"
#include "tiles/forest.h"
#include "tiles/foresttileitem.h"
#include "tiles/grasstileitem.h"
#include "tiles/watertileitem.h"
#include "tiles/mountaintileitem.h"
#include "units/graphicsunitbase.h"



MapWindow::MapWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    viewPortPtr_(new GraphicsViewPort(this)),
    scenePtr_(new CustomGraphicsScene(viewPortPtr_)),
    m_GEHandler(nullptr),
    eventhandler_(nullptr),
    gameScene_(new Course::SimpleGameScene(this, 20,20)),
    unitConstructor_(nullptr)
{
    unitConstructor_ = std::make_shared<UnitConstructor>();
    objectManager_ = std::make_shared<ObjectManager>(scenePtr_);
    eventhandler_ = std::make_shared<GameEventHandler>(objectManager_, unitConstructor_);

    unitConstructor_->setEventHandler(eventhandler_);
    unitConstructor_->setObjectManager(objectManager_);

    m_ui->setupUi(this);

    // setup graphics view
    m_ui->viewTxtboxLayout->insertWidget(0,viewPortPtr_);
    viewPortPtr_->setRenderHint(QPainter::Antialiasing);
    viewPortPtr_->setBackgroundBrush(QPixmap(":/resources/placeholder.PNG"));
    viewPortPtr_->setMinimumSize(500,400);

    connect(m_ui->actionExit, &QAction::triggered, this, &MapWindow::close);
    connect(m_ui->actionStart, &QAction::triggered, this, &MapWindow::showStartWindow);
    connect(m_ui->turnSwitchBtn, &QPushButton::clicked, this, &MapWindow::switchTurn);

    connect(eventhandler_.get(), &GameEventHandler::signalUpdateVisibleResources, this, &MapWindow::updateVisibleResources);
    connect(eventhandler_.get(), &GameEventHandler::signalSendMsg, this, &MapWindow::sendMsgSlot);

    connect(m_ui->actionSave, &QAction::triggered, this, &MapWindow::showSaveWindow);
    connect(m_ui->actionLoad, &QAction::triggered, this, &MapWindow::showLoadWindow);

    Course::WorldGenerator& generaattori = Course::WorldGenerator::getInstance();


    generaattori.addConstructor<GrassTileItem>(2);
    generaattori.addConstructor<ForestTileItem>(2);
    generaattori.addConstructor<WaterTileItem>(1);
    generaattori.addConstructor<MountainTileItem>(1);

    viewPortPtr_->setScene(scenePtr_);
    MapWindow::showStartWindow();
}

MapWindow::~MapWindow()
{
}

void MapWindow::setGEHandler(
        std::shared_ptr<Course::iGameEventHandler> nHandler)
{
    m_GEHandler = nHandler;
}

void MapWindow::setSize(int width, int height)
{
    gameScene_->setSize(width, height);
}

void MapWindow::setScale(int scale)
{
    gameScene_->setScale(scale);
}

void MapWindow::resize()
{
    gameScene_->resize();
}

void MapWindow::updateVisibleResources()
{
    std::shared_ptr<Player> currentPlayer = eventhandler_->getCurrentPlayer();
    QString goldValue= QString::number(currentPlayer->getResourceValue(Course::MONEY));
    QString foodValue= QString::number(currentPlayer->getResourceValue(Course::FOOD));
    QString woodValue= QString::number(currentPlayer->getResourceValue(Course::WOOD));

    Course::ResourceMap production = eventhandler_->calculateProduction();

    m_ui->goldValueLbl->setText(goldValue);
    m_ui->foodValueLbl->setText(foodValue);
    m_ui->woodValueLbl->setText(woodValue);
    m_ui->goldProductionLbl->setText(QString::number(production[Course::MONEY]));
    m_ui->foodProductionLbl->setText(QString::number(production[Course::FOOD]));
    m_ui->woodProductionLbl->setText(QString::number(production[Course::WOOD]));

}

void MapWindow::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    gameScene_->updateItem(obj);
}

void MapWindow::showSaveWindow()
{
    SaveGame* saveGamePtr = new SaveGame(eventhandler_, objectManager_);
    SaveWindow* savewindow = new SaveWindow();
    savewindow->setModal(true);
    savewindow->show();
    connect(savewindow, &SaveWindow::sendSaveFileName, saveGamePtr, &SaveGame::saveCurrentGame);
}

void MapWindow::showLoadWindow()
{
    LoadGame* loadGamePtr = new LoadGame(eventhandler_, objectManager_);
    LoadWindow* loadwindow = new LoadWindow();
    loadwindow->setModal(true);
    loadwindow->show();
    connect(loadwindow, &LoadWindow::sendLoadFileName, loadGamePtr, &LoadGame::loadGame);
}

void MapWindow::showStartWindow()
{
    Startwindow* startti = new Startwindow();
    startti->show();

    //connect(startti, &Startwindow::sendPlayerNames, this, &MapWindow::addPlayerNames);
    //connect(startti, &Startwindow::sendSeed, this, &MapWindow::startNewGame);
    connect(startti, &Startwindow::startGame, this, &MapWindow::startNewGame);
    //connect(startti, SIGNAL(accept()), this, SLOT(startNewGame()));
}

void MapWindow::switchTurn()
{
    std::string msg = "\nTurn ";
    msg += std::to_string(eventhandler_->getTurnNumber()) + " ended, now it is turn of ";
    eventhandler_->nextTurn();
    std::string curPlayerName = eventhandler_->getCurrentPlayer()->getName();
    msg += curPlayerName;
    std::string playerTurnText = eventhandler_->getCurrentPlayer()->getName()
            + " - Turn " + std::to_string(eventhandler_->getTurnNumber());
    m_ui->groupBox->setTitle(playerTurnText.c_str());
    sendMsgSlot(msg);
    //updateVisibleResources();
}



void MapWindow::startNewGame(playerInfo info, unsigned int seed)
{
    m_ui->turnSwitchBtn->setDisabled(false);
    m_ui->textBox->insertPlainText("<<<STARTED NEW GAME>>>\n");
    qDebug() << "started new game";

    eventhandler_->resetData();

    Course::WorldGenerator& generaattori = Course::WorldGenerator::getInstance();
    generaattori.generateMap(20,20,seed,objectManager_, eventhandler_);

    qDebug() << "Seed: " << seed;
    eventhandler_->addNewPlayers(info);
    std::string playerTurnText = eventhandler_->getCurrentPlayer()->getName()
            + " - Turn " + std::to_string(eventhandler_->getTurnNumber());
    m_ui->groupBox->setTitle(playerTurnText.c_str());
    /*
    GraphicsUnitBase* newUnit = new GraphicsUnitBase(eventhandler_, objectManager_, eventhandler_->getCurrentPlayer());
    scene_->addItem(newUnit);
    */
}

void MapWindow::sendMsgSlot(std::string &msg)
{
    m_ui->textBox->insertPlainText((msg + "\n").c_str());
    QScrollBar *sb = m_ui->textBox->verticalScrollBar();
    sb->setValue(sb->maximum());
}


void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    gameScene_->removeItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    gameScene_->drawItem(obj);
}
