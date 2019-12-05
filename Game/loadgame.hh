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

    using TileConstructorPointer = std::function<std::shared_ptr<Course::TileBase>(
        Course::Coordinate,
        std::shared_ptr<Course::iGameEventHandler>,
        std::shared_ptr<Course::iObjectManager>)>;

    /**
     * @brief Adds a Tile's constructor in multimap to be finded with tileType
     * Use the Tile's type as the template parameter: addConstructor<Forest>();
     * @param tileType is name of the tile, that can be later used to retrieve tile constructor
     * from multimap
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

    /**
      * @brief splits string to vector using "," as delimiter
      * @param stringToBeSplitted string to be splitted to vector
      * @return splitted string as a vector
      */
    std::vector<std::string> split(const std::string &stringToBeSplitted);

    /**
      * @brief set owner to tiles, and loads units and buildings
      * @param fileName path and filename to .txt file where game will be loaded
      */
    void addUnitsAndBuildings(QString fileName);



public slots:
    /**
      * @brief loads players, tiles and turn number
      * @param fileName path and filename to .txt file where game will be loaded
      */
    void loadGame(QString fileName);

signals:
    /**
      * @brief signal that is connected to updateVisibleResources in mapwindow
      */
    void updateVisibleLabels();
    /**
      * @brief signal that is connected to sendMsgSlot in mapwindow, sends message
      * @param msg message to be sended
      */
    void sendMsg(std::string& msg);

private:
    std::shared_ptr<GameEventHandler> eventhandler_;
    std::shared_ptr<ObjectManager> objectManager_;
    std::vector<std::shared_ptr<Player>> playerVector_;
    std::multimap<std::string, TileConstructorPointer> tileConctructorNames_ ;

};

#endif // LOADGAME_HH
