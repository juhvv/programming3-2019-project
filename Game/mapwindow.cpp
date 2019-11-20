#include "mapwindow.hh"
#include "ui_mapwindow.h"

#include "graphics/simplemapitem.h"

#include "startwindow.hh"
#include "core/worldgenerator.h"
#include "tiles/forest.h"

#include <math.h>
#include <QAction>

MapWindow::MapWindow(QWidget *parent,
                     std::shared_ptr<Course::iGameEventHandler> handler):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    viewPortPtr_(new GraphicsViewPort(this)),
    m_GEHandler(NULL),
    eventhandler_(std::make_shared<GameEventHandler>()),
    m_simplescene(new Course::SimpleGameScene(this, 20,20))
{
    Course::SimpleGameScene* sgs_rawptr = m_simplescene.get();
    objectManager_ = std::make_shared<ObjectManager>(sgs_rawptr);
    m_GEHandler = eventhandler_;

    m_ui->setupUi(this);
    m_ui->viewTxtboxLayout->insertWidget(0,viewPortPtr_);
    viewPortPtr_->setRenderHint(QPainter::Antialiasing);
    viewPortPtr_->setBackgroundBrush(QPixmap(":/resources/placeholder.PNG"));
    //GameEventHandler* eventHandlerPtr = handler2.get();

    connect(m_ui->actionExit, &QAction::triggered, this, &MapWindow::close);
    connect(m_ui->actionStart, &QAction::triggered, this, &MapWindow::showStartWindow);
    connect(m_ui->turnSwitchBtn, &QPushButton::clicked, this, &MapWindow::switchTurn);

    Course::WorldGenerator& generaattori = Course::WorldGenerator::getInstance();

    generaattori.addConstructor<Course::Forest>(2);
    generaattori.addConstructor<Course::Grassland>(2);

    viewPortPtr_->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
    MapWindow::showStartWindow();
}

MapWindow::~MapWindow()
{
    delete m_ui;
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

void MapWindow::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->updateItem(obj);
}

void MapWindow::showStartWindow()
{
    Startwindow* startti = new Startwindow();
    startti->setModal(true);
    startti->show();

    connect(startti, &Startwindow::sendPlayerNames, this, &MapWindow::addPlayerNames);
    connect(startti, &Startwindow::sendSeed, this, &MapWindow::startNewGame);
    //connect(startti, SIGNAL(accept()), this, SLOT(startNewGame()));
}

void MapWindow::switchTurn()
{
    QString sad = "Turn ";
    sad.append(std::to_string(eventhandler_->getTurnNumber()).c_str()); sad.append(" ended\n");
    m_ui->textBox->insertPlainText(sad);
    eventhandler_->nextTurn();
}

void MapWindow::addPlayerNames(std::vector<std::string>)
{
    qDebug() << "data virraa!";
}

void MapWindow::startNewGame(unsigned int seed)
{
    m_ui->textBox->insertPlainText("<<<STARTED NEW GAME>>>\n");
    qDebug() << "started new game";
    objectManager_->resetData();
    eventhandler_->resetData();
    Course::WorldGenerator& generaattori = Course::WorldGenerator::getInstance();
    generaattori.generateMap(20,20,seed,objectManager_, m_GEHandler);
}


void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->removeItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->drawItem(obj);
}
