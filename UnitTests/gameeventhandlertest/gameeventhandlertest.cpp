#include <QString>
#include <QtTest>

class GameEventHandlerTest : public QObject
{
    Q_OBJECT

public:
    GameEventHandlerTest();

private Q_SLOTS:
    void testSlot1();
};

GameEventHandlerTest::GameEventHandlerTest()
{
}

void GameEventHandlerTest::testSlot1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(GameEventHandlerTest)

#include "gameeventhandlertest.moc"
