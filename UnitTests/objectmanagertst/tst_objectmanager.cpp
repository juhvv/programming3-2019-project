#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "objectmanager.hh"
#include "ui/customgraphicsscene.h"

#include "gameeventhandler.hh"
#include "mapwindow.hh"

class objectmanager_tester : public QObject
{
    Q_OBJECT

public:
    objectmanager_tester();
    ~objectmanager_tester();

private slots:
    void getTile_tst();
    void resetData_tst();
   // void setGraphicsObject_Tst();
private:
    void generateTestMap();
    std::shared_ptr<ObjectManager> objectMngr_;
    std::shared_ptr<GameEventHandler> test_handler_;
    std::shared_ptr<UnitConstructor> uConstructor_;
    Course::ResourceMap startResources_;
    CustomGraphicsScene* scene_;
};

objectmanager_tester::objectmanager_tester()
{
    scene_ = new CustomGraphicsScene();
    objectMngr_ = std::make_shared<ObjectManager>(scene_);
    test_handler_ = std::make_shared<GameEventHandler>(objectMngr_, uConstructor_);

}

objectmanager_tester::~objectmanager_tester()
{

}



void objectmanager_tester::resetData_tst(){
    generateTestMap();
    objectMngr_->resetData();
    QVERIFY(objectMngr_->getAllTiles().size()==0);
}

void objectmanager_tester::getTile_tst(){
    generateTestMap();
    std::vector<Course::Coordinate> coordVector;
    Course::Coordinate testCoord = Course::Coordinate(1, 1);
    coordVector.push_back(testCoord);
    coordVector.push_back(Course::Coordinate(2, 2));
    //test that size of tilevector is the same on getAllTiles
    QVERIFY(sqrt(objectMngr_->getAllTiles().size())==MapSize::NORMAL);
    //test that tile type stays the same on getTile
    QVERIFY(objectMngr_->getTile(testCoord)->getType()=="Grass tile");
    //Test getTiles
    QVERIFY(objectMngr_->getTiles(coordVector).size()==2);
}

void objectmanager_tester::generateTestMap()
{
    std::vector<std::shared_ptr<Course::TileBase>> tileVec = {};
    for (int x = 0; x < MapSize::NORMAL; ++x) {
        for (int y = 0; y < MapSize::NORMAL; ++y) {
            std::shared_ptr<GrassTileItem> newTile =
                    std::make_shared<GrassTileItem>(Course::Coordinate(x,y), test_handler_, objectMngr_);
            tileVec.push_back(std::dynamic_pointer_cast<Course::TileBase>(newTile));
        }
    }
    objectMngr_->addTiles(tileVec);
}



QTEST_MAIN(objectmanager_tester)

#include "tst_objectmanager.moc"
