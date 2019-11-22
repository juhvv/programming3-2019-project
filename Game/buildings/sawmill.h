#ifndef SAWMILL_H
#define SAWMILL_H

#include "buildings/buildingbase.h"

class SawMill : public Course::BuildingBase
{
public:
    SawMill() = delete;
    virtual ~SawMill() = default;
};

#endif // SAWMILL_H
