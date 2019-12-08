#include <QtTest>

// add necessary includes here

class eventhandler : public QObject
{
    Q_OBJECT

public:
    eventhandler();
    ~eventhandler();

private slots:
    void test_case1();

};

eventhandler::eventhandler()
{

}

eventhandler::~eventhandler()
{

}

void eventhandler::test_case1()
{

}

QTEST_APPLESS_MAIN(eventhandler)

#include "tst_eventhandler.moc"
