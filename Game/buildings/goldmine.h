#ifndef GOLDMINE_H
#define GOLDMINE_H

#include "buildings/buildingbase.h"

class GoldMine : public Course::BuildingBase
{
public:
    GoldMine() = delete;
    virtual ~GoldMine() = default;
};

#endif // GOLDMINE_H
