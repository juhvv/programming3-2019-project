#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "objectmanager.hh"
#include "ui/customgraphicsscene.h"

class objectmanager : public QObject
{
    Q_OBJECT

public:
    objectmanager();
    ~objectmanager();

private slots:
    void test_case1();

};

objectmanager::objectmanager()
{

}

objectmanager::~objectmanager()
{

}

void objectmanager::test_case1()
{

}

QTEST_MAIN(objectmanager)

#include "tst_objectmanager.moc"
