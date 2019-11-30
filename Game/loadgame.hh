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
#include "buildings/gamebuildingbase.h"

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

    template<typename T>
    void addConstructor(std::string tileType)
    {
        TileConstructorPointer ctor = std::make_shared<T, Course::Coordinate,
                std::shared_ptr<Course::iGameEventHandler>,
                std::shared_ptr<Course::iObjectManager> >;
        tileConctructorNames_.insert(std::make_pair(tileType, ctor));
    }










    void addUnitsAndBuildings();



public slots:
    void loadGame(QString fileName);


private:
    std::shared_ptr<GameEventHandler> eventhandler_;
    std::shared_ptr<ObjectManager> objectManager_;
    std::vector<std::shared_ptr<Player>> playerVector_;

    std::multimap<std::string, TileConstructorPointer> tileConctructorNames_ ;

};

#endif // LOADGAME_HH
