#ifndef OBJECTMANAGER_HH
#define OBJECTMANAGER_HH

#include <QObject>
#include "interfaces/iobjectmanager.h"

class objectManager : public Course::iObjectManager
{
public:
    objectManager();
};

#endif // OBJECTMANAGER_HH
