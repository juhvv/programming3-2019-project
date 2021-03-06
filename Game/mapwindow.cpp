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
    eventhandler_(nullptr),
    unitConstructor_(nullptr)
{
    m_ui->setupUi(this);

    // create & setup objectmanager, unitconstructor and eventhandler
    unitConstructor_ = std::make_shared<UnitConstructor>();
    objectManager_ = std::make_shared<ObjectManager>(scenePtr_);
    eventhandler_ = std::make_shared<GameEventHandler>(objectManager_, unitConstructor_);
    unitConstructor_->setEventHandler(eventhandler_);
    unitConstructor_->setObjectManager(objectManager_);

    // setup graphics view
    m_ui->viewTxtboxLayout->insertWidget(0,viewPortPtr_);
    viewPortPtr_->setRenderHint(QPainter::Antialiasing);
    viewPortPtr_->setBackgroundBrush(QPixmap(":/resources/placeholder.PNG"));
    viewPortPtr_->setMinimumSize(500,400);
    viewPortPtr_->setScene(scenePtr_);

    // connect map window buttons and menu actions
    connect(m_ui->actionExit, &QAction::triggered, this, &MapWindow::close);
    connect(m_ui->actionSave, &QAction::triggered, this, &MapWindow::showSaveWindow);
    connect(m_ui->actionLoad, &QAction::triggered, this, &MapWindow::showLoadWindow);
    connect(m_ui->actionStart, &QAction::triggered, this, &MapWindow::showStartWindow);
    connect(m_ui->turnSwitchBtn, &QPushButton::clicked, this, &MapWindow::switchTurn);

    // connect eventhandler's signals
    connect(eventhandler_.get(), &GameEventHandler::signalUpdateVisibleResources,
            this, &MapWindow::updateVisibleResources);
    connect(eventhandler_.get(), &GameEventHandler::signalSendMsg, this, &MapWindow::sendMsgSlot);
    connect(eventhandler_.get(), &GameEventHandler::signalNextButtonMode, this, &MapWindow::nextButtonMode);

    // setup world generator
    Course::WorldGenerator& generaattori = Course::WorldGenerator::getInstance();
    generaattori.addConstructor<GrassTileItem>(4);
    generaattori.addConstructor<ForestTileItem>(4);
    generaattori.addConstructor<WaterTileItem>(2);
    generaattori.addConstructor<MountainTileItem>(2);
    generaattori.addConstructor<SwampTileItem>(1);

    MapWindow::showStartWindow();
}

MapWindow::~MapWindow()
{
}

void MapWindow::updateVisibleResources()
{
    std::shared_ptr<Player> currentPlayer = eventhandler_->getCurrentPlayer();
    //Just assign resource values
    QString goldValue= QString::number(currentPlayer->getResourceValue(Course::MONEY));
    QString foodValue= QString::number(currentPlayer->getResourceValue(Course::FOOD));
    QString woodValue= QString::number(currentPlayer->getResourceValue(Course::WOOD));

    //Calculates what would production be with current state of workers and buildings
    Course::ResourceMap production = eventhandler_->calculateProduction();

    //Update visible resources for current player
    m_ui->goldValueLbl->setText(goldValue);
    m_ui->foodValueLbl->setText(foodValue);
    m_ui->woodValueLbl->setText(woodValue);

    //These update production of resources  in turn that is shown in mapwindow for current player,
    //in current state of workers and buildings
    m_ui->goldProductionLbl->setText(QString::number(production[Course::MONEY]));
    m_ui->foodProductionLbl->setText(QString::number(production[Course::FOOD]));
    m_ui->woodProductionLbl->setText(QString::number(production[Course::WOOD]));

    //Shows who is the current player on mapwindow
    std::string playerTurnText = eventhandler_->getCurrentPlayer()->getName()
            + " - Turn " + std::to_string(eventhandler_->getTurnNumber());
    m_ui->groupBox->setTitle(playerTurnText.c_str());

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
    connect(loadGamePtr, &LoadGame::updateVisibleLabels, this, &MapWindow::updateVisibleResources);
    connect(loadGamePtr, &LoadGame::sendMsg, this, &MapWindow::sendMsgSlot);
    connect(loadwindow, &LoadWindow::sendLoadFileName, loadGamePtr, &LoadGame::loadGame);
}


void MapWindow::showStartWindow()
{
    Startwindow* startti = new Startwindow();
    startti->show();

    connect(startti, &Startwindow::startGame, this, &MapWindow::startNewGame);
}

void MapWindow::switchTurn()
{
    std::string msg = "\nTurn ";
    msg += std::to_string(eventhandler_->getTurnNumber()) + " ended, now it is turn of ";
    eventhandler_->nextTurn();      //Calls eventhandler to change turn
    std::string curPlayerName = eventhandler_->getCurrentPlayer()->getName();
    msg += curPlayerName;
    sendMsgSlot(msg);   //Shows message in mapwindow that turn is changed
}

void MapWindow::startNewGame(playerInfo info, unsigned int seed, MapSize::Size size)
{
    m_ui->turnSwitchBtn->setDisabled(false);
    m_ui->textBox->insertPlainText("<<<STARTED NEW GAME>>>\n");
    qDebug() << "started new game";

    eventhandler_->resetData();

    Course::WorldGenerator& generaattori = Course::WorldGenerator::getInstance();
    generaattori.generateMap(size, size, seed,objectManager_, eventhandler_);

    qDebug() << "Seed: " << seed;
    eventhandler_->addNewPlayers(info, size);
    std::string playerTurnText = eventhandler_->getCurrentPlayer()->getName()
            + " - Turn " + std::to_string(eventhandler_->getTurnNumber());
    m_ui->groupBox->setTitle(playerTurnText.c_str());
    updateVisibleResources();
}

void MapWindow::sendMsgSlot(std::string &msg)
{
    m_ui->textBox->insertPlainText((msg + "\n").c_str());
    QScrollBar *sb = m_ui->textBox->verticalScrollBar();
    sb->setValue(sb->maximum());
}

void MapWindow::nextButtonMode(bool buttonMode)
{
    if(buttonMode==true){
        m_ui->turnSwitchBtn->setEnabled(true);
    }
    else{
        m_ui->turnSwitchBtn->setEnabled(false);
    }
}
