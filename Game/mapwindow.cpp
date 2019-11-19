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
    m_GEHandler(NULL),
    eventhandler_(NULL),
    m_simplescene(new Course::SimpleGameScene(this))
{

    MapWindow::showStartWindow();
    Course::SimpleGameScene* sgs_rawptr = m_simplescene.get();


    std::shared_ptr<ObjectManager> manager = std::make_shared<ObjectManager>(sgs_rawptr);
    eventhandler_ = std::make_shared<GameEventHandler>();
    Course::WorldGenerator& generaattori = Course::WorldGenerator::getInstance();

    generaattori.addConstructor<Course::Forest>(1);
    generaattori.addConstructor<Course::Grassland>(2);
    generaattori.generateMap(7,7,231,manager, m_GEHandler);


    m_ui->setupUi(this);

    //GameEventHandler* eventHandlerPtr = handler2.get();

    connect(m_ui->actionExit, &QAction::triggered, this, &MapWindow::close);
    connect(m_ui->actionStart, &QAction::triggered, this, &MapWindow::showStartWindow);
    connect(m_ui->turnSwitchBtn, &QPushButton::clicked, this, &MapWindow::switchTurn);

    //Course::SimpleGameScene* sgs_rawptr = m_simplescene.get();

    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
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
}

void MapWindow::switchTurn()
{
    char msgBuffer[100] = "asd";
    QString sad = "Turn ";
    sad.append(std::to_string(eventhandler_->getTurnNumber()).c_str()); sad.append(" ended\n");
    m_ui->textBox->insertPlainText(sad);
    eventhandler_->nextTurn();
}

void MapWindow::addPlayerNames(std::vector<std::string>)
{
    qDebug() << "data virraa!";
}


void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->removeItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->drawItem(obj);
}
