#ifndef LOADGAME_HH
#define LOADGAME_HH

#include <QObject>
#include <QDebug>
#include <string>
#include "interfaces/iobjectmanager.h"
#include "interfaces/igameeventhandler.h"
#include "gameeventhandler.hh"
#include "objectmanager.hh"

#include "tiles/foresttileitem.h"
#include "tiles/grasstileitem.h"
#include "tiles/watertileitem.h"
#include "tiles/mountaintileitem.h"
#include "tiles/swamptileitem.h"

#include "buildings/gamebuildingbase.h"
#include "buildings/base.h"
#include "buildings/goldmine.h"
#include "buildings/sawmill.h"
#include "buildings/gamefarm.h"
#include "buildings/goldmine.h"
#include "buildings/gameoutpost.h"


#include "units/scout.h"
#include "units/graphicsunitbase.h"
#include "units/worker.h"
#include "units/builder.h"

#include <iostream>
#include <sstream>
#include <vector>



#include "QDir"
#include "QTextStream"
#include "QFile"

class LoadGame : public QObject
{
    Q_OBJECT
public:
    LoadGame(std::shared_ptr<GameEventHandler> &eventhandler,
             std::shared_ptr<ObjectManager> &objectmanager);

    std::vector<std::string> split(const std::string &stringToBeSplitted);

    using TileConstructorPointer = std::function<std::shared_ptr<Course::TileBase>(
        Course::Coordinate,
        std::shared_ptr<Course::iGameEventHandler>,
        std::shared_ptr<Course::iObjectManager>)>;

    /*
    using BuildingConstructorPointer = std::function<std::shared_ptr<Course::BuildingBase>(
        std::shared_ptr<Course::iGameEventHandler>,
        std::shared_ptr<Course::iObjectManager>,
        std::shared_ptr<Course::PlayerBase>)>;

    using UnitConstructorPointer = std::function<std::shared_ptr<Course::WorkerBase>(
        std::shared_ptr<Course::iGameEventHandler>,
        std::shared_ptr<Course::iObjectManager>,
        std::shared_ptr<Course::PlayerBase>)>;
    */

    template<typename T>
    void addTileConstructor(std::string tileType)
    {
        TileConstructorPointer ctor = std::make_shared<T,
                Course::Coordinate,
                std::shared_ptr<Course::iGameEventHandler>,
                std::shared_ptr<Course::iObjectManager> >;
        tileConctructorNames_.insert(std::make_pair(tileType, ctor));
    }

    /*
    template<typename T>
    void addBuildingConstructor(std::string buildingType)
    {
        BuildingConstructorPointer buildingctor = std::make_shared<T,
                std::shared_ptr<Course::iGameEventHandler>,
                std::shared_ptr<Course::iObjectManager>,
                std::shared_ptr<Course::PlayerBase> >;
        buildingConctructorNames_.insert(std::make_pair(buildingType, buildingctor));
    }


    template<typename T>
    void addUnitConstructor(std::string unitType)
    {
        UnitConstructorPointer unitctor = std::make_shared<T,
                std::shared_ptr<Course::iGameEventHandler>,
                std::shared_ptr<Course::iObjectManager>,
                std::shared_ptr<Course::PlayerBase> >;
        unitConctructorNames_.insert(std::make_pair(unitType, unitctor));
    }

    */
    void addUnitsAndBuildings(QString fileName);



public slots:
    void loadGame(QString fileName);

signals:
    void updateVisibleLabels();
    void sendMsg(std::string& msg);

private:
    std::shared_ptr<GameEventHandler> eventhandler_;
    std::shared_ptr<ObjectManager> objectManager_;
    std::vector<std::shared_ptr<Player>> playerVector_;

    std::multimap<std::string, TileConstructorPointer> tileConctructorNames_ ;

};

#endif // LOADGAME_HH
