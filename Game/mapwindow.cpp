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

#include <math.h>
#include <QAction>

MapWindow::MapWindow(QWidget *parent,
                     std::shared_ptr<Course::iGameEventHandler> handler):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    viewPortPtr_(new GraphicsViewPort(this)),
    scene_(new CustomGraphicsScene(viewPortPtr_)),
    m_GEHandler(nullptr),
    eventhandler_(nullptr),
    m_simplescene(new Course::SimpleGameScene(this, 20,20))
{
    Course::SimpleGameScene* sgs_rawptr = m_simplescene.get();
    objectManager_ = std::make_shared<ObjectManager>(sgs_rawptr, scene_);
    eventhandler_ = std::make_shared<GameEventHandler>(objectManager_);
    m_GEHandler = eventhandler_;

    m_ui->setupUi(this);

    // setup graphics view
    m_ui->viewTxtboxLayout->insertWidget(0,viewPortPtr_);
    viewPortPtr_->setRenderHint(QPainter::Antialiasing);
    viewPortPtr_->setBackgroundBrush(QPixmap(":/resources/placeholder.PNG"));

    connect(m_ui->actionExit, &QAction::triggered, this, &MapWindow::close);
    connect(m_ui->actionStart, &QAction::triggered, this, &MapWindow::showStartWindow);
    connect(m_ui->turnSwitchBtn, &QPushButton::clicked, this, &MapWindow::switchTurn);

    connect(eventhandler_.get(), &GameEventHandler::signalUpdateVisibleResources, this, &MapWindow::updateVisibleResources);

    Course::WorldGenerator& generaattori = Course::WorldGenerator::getInstance();

    generaattori.addConstructor<GrassTileItem>(2);
    generaattori.addConstructor<ForestTileItem>(2);
    generaattori.addConstructor<WaterTileItem>(1);
    generaattori.addConstructor<MountainTileItem>(1);
    /*
    for (unsigned int x = 0; x < 20; ++x)
    {
        for (unsigned int y = 0; y < 20; ++y)
        {
            Course::Coordinate coord = Course::Coordinate(x,y);
            //std::shared_ptr<GraphicsTileBase> newItem = std::make_shared<GraphicsTileBase>(coord, eventhandler_, objectManager_);
            //scene_->addItem(newItem.get());
            ForestTileItem* newItemPtr = new ForestTileItem(coord, eventhandler_, objectManager_);
            scene_->addItem(newItemPtr);
            newItemPtr->setPos(coord.x() * 128, coord.y() *128);
        }
    }
    */
    //GraphicsUnitBase* newUnit = new GraphicsUnitBase(eventhandler_, objectManager_, nullptr);
    //scene_->addItem(newUnit);
    //viewPortPtr_->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
    viewPortPtr_->setScene(scene_);
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
    m_simplescene->setSize(width, height);
}

void MapWindow::setScale(int scale)
{
    m_simplescene->setScale(scale);
}

void MapWindow::resize()
{
    m_simplescene->resize();
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
    m_simplescene->updateItem(obj);
}

void MapWindow::showStartWindow()
{
    Startwindow* startti = new Startwindow();
    startti->setModal(true);
    startti->show();

    //connect(startti, &Startwindow::sendPlayerNames, this, &MapWindow::addPlayerNames);
    //connect(startti, &Startwindow::sendSeed, this, &MapWindow::startNewGame);
    connect(startti, &Startwindow::startGame, this, &MapWindow::startNewGame);
    //connect(startti, SIGNAL(accept()), this, SLOT(startNewGame()));
}

void MapWindow::switchTurn()
{
    QString msg = "Turn ";
    msg.append(std::to_string(eventhandler_->getTurnNumber()).c_str()); msg.append(" ended, now it is turn of ");
    eventhandler_->nextTurn();
    msg.append(eventhandler_->getCurrentPlayer()->getName().c_str()); msg.append(" \n");
    m_ui->textBox->insertPlainText(msg);
    //updateVisibleResources();
}



void MapWindow::startNewGame(playerInfo info, unsigned int seed)
{
    m_ui->turnSwitchBtn->setDisabled(false);
    m_ui->textBox->insertPlainText("<<<STARTED NEW GAME>>>\n");
    qDebug() << "started new game";

    objectManager_->resetData();
    eventhandler_->resetData();
    eventhandler_->addNewPlayers(info);

    Course::WorldGenerator& generaattori = Course::WorldGenerator::getInstance();
    generaattori.generateMap(20,20,seed,objectManager_, m_GEHandler);
    eventhandler_->getCurrentPlayer();
    /*
    GraphicsUnitBase* newUnit = new GraphicsUnitBase(eventhandler_, objectManager_, eventhandler_->getCurrentPlayer());
    scene_->addItem(newUnit);
    */
}


void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->removeItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->drawItem(obj);
}
