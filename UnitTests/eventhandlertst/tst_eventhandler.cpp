#include <QtTest>
#include <memory>

// add necessary includes here
#include "gameeventhandler.hh"
#include "mapwindow.hh"

class handler_tester : public QObject
{
    Q_OBJECT

public:
    handler_tester();
    ~handler_tester();

private slots:
    void test_case1();

    // resource modification test
    void modResource_tst();
    void modResources_tst();

    void nextTurn_tst();

    void turnNumbers_tst();

    void getPlayers_tst();

    void addPlayers_tst();

    void cleanup();

private:
    void generateTestMap();
    std::shared_ptr<Player> p1_;
    std::shared_ptr<Player> p2_;
    std::shared_ptr<ObjectManager> objectMngr_;
    std::shared_ptr<GameEventHandler> test_handler_;
    std::shared_ptr<UnitConstructor> uConstructor_;
    Course::ResourceMap startResources_;
    CustomGraphicsScene* scene_;
};

handler_tester::handler_tester()
{
    startResources_.insert(std::pair<Course::BasicResource,int>(Course::MONEY, 0));
    startResources_.insert(std::pair<Course::BasicResource,int>(Course::FOOD, 0));
    startResources_.insert(std::pair<Course::BasicResource,int>(Course::WOOD, 0));
    startResources_.insert(std::pair<Course::BasicResource,int>(Course::STONE, 0));
    startResources_.insert(std::pair<Course::BasicResource,int>(Course::ORE, 0));

    p1_ = std::make_shared<Player>("p1", startResources_);
    p2_ = std::make_shared<Player>("p1", startResources_);
    scene_ = new CustomGraphicsScene();
    objectMngr_ = std::make_shared<ObjectManager>(scene_);
    uConstructor_ = std::make_shared<UnitConstructor>();
    test_handler_ = std::make_shared<GameEventHandler>(objectMngr_, uConstructor_);

    uConstructor_->setEventHandler(test_handler_);
    uConstructor_->setObjectManager(objectMngr_);
    generateTestMap();
}

handler_tester::~handler_tester()
{
    delete scene_;
}

void handler_tester::test_case1()
{

}

void handler_tester::modResource_tst()
{
    test_handler_->addPlayerVector({p1_, p2_});
    test_handler_->modifyResource(p1_, Course::BasicResource::ORE, 100);
    test_handler_->modifyResource(p1_, Course::BasicResource::ORE, -21);
    QVERIFY(p1_->getResourceValue(Course::BasicResource::ORE) == 79);
}

void handler_tester::modResources_tst()
{
    test_handler_->addPlayerVector({p1_, p2_});
    Course::ResourceMap tstMap = {{Course::MONEY, 120},
                                 {Course::FOOD, 120},
                                 {Course::STONE, 120},
                                 {Course::WOOD, 120},
                                 {Course::ORE, 120}};
    Course::ResourceMap subtractMap = {{Course::MONEY, -120},
                                 {Course::FOOD, -120},
                                 {Course::STONE, -120},
                                 {Course::WOOD, -120},
                                 {Course::ORE, -120}};
    test_handler_->modifyResources(p1_, tstMap);
    QVERIFY(p1_->getResourceMap() == tstMap);

    test_handler_->modifyResources(p1_, subtractMap);
    QVERIFY(p1_->getResourceMap() == startResources_);
}

void handler_tester::nextTurn_tst()
{
    test_handler_->addPlayerVector({p1_, p2_});
    test_handler_->setCurrentPlayer(p1_->getName());
    test_handler_->nextTurn();
    QVERIFY(test_handler_->getCurrentPlayer() == p2_);
    QVERIFY(test_handler_->getTurnNumber() == 2);
}

void handler_tester::turnNumbers_tst()
{
    QVERIFY(test_handler_->getTurnNumber() == 1);
    test_handler_->setTurnNumber(10);
    QVERIFY(test_handler_->getTurnNumber() == 10);
}

void handler_tester::getPlayers_tst()
{
    std::vector<std::shared_ptr<Player>> testPlayers = {p1_, p2_};
    test_handler_->addPlayerVector(testPlayers);
    test_handler_->setCurrentPlayer(p1_->getName());

    QVERIFY(test_handler_->getCurrentPlayer() == p1_);
    QVERIFY(test_handler_->getPlayerVector() == testPlayers);
    QVERIFY(test_handler_->getPlayerFromName("p1") == p1_);
    QVERIFY(test_handler_->getPlayerFromName("pelle") == nullptr);
}

void handler_tester::addPlayers_tst()
{
    std::vector<std::pair<std::string, int>> newPlayerData
            = {{"player1", 0}, {"player2", 1}};
    test_handler_->setCurrentPlayer("player1");
    test_handler_->addNewPlayers(newPlayerData, MapSize::NORMAL);

    // test building creation
    QVERIFY(test_handler_->getPlayerFromName("player1")->getPlayerBuildings()[0]->getType() ==
            "Base");

    QVERIFY(test_handler_->getPlayerFromName("player2")->getPlayerBuildings()[0]->getType() ==
            "Base");

    QVERIFY(test_handler_->getPlayerVector()[0] != nullptr &&
            test_handler_->getPlayerVector()[1] != nullptr);
}

void handler_tester::cleanup()
{
    p1_ = std::make_shared<Player>("p1", startResources_);
    p2_ = std::make_shared<Player>("p2", startResources_);
    test_handler_->resetData();
}

void handler_tester::generateTestMap()
{
    std::vector<std::shared_ptr<Course::TileBase>> tileVec = {};
    for (int x = 0; x < MapSize::NORMAL; ++x) {
        for (int y; y < MapSize::NORMAL; ++y) {
            std::shared_ptr<GrassTileItem> newTile =
                    std::make_shared<GrassTileItem>(Course::Coordinate(x,y), test_handler_, objectMngr_);
            tileVec.push_back(std::dynamic_pointer_cast<Course::TileBase>(newTile));
        }
    }
    objectMngr_->addTiles(tileVec);
}

QTEST_MAIN(handler_tester)

#include "tst_eventhandler.moc"
