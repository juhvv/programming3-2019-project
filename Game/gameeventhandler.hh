#ifndef GAMEEVENTHANDLER_HH
#define GAMEEVENTHANDLER_HH

#include <QObject>
#include "interfaces/igameeventhandler.h"

class gameEventHandler : public Course::iGameEventHandler
{
public:
    gameEventHandler();
};

#endif // GAMEEVENTHANDLER_HH
