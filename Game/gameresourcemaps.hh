#ifndef GAMERESOURCEMAPS_HH
#define GAMERESOURCEMAPS_HH

#include "core/basicresources.h"

namespace GameConstResourceMaps {

using namespace Course;

const ResourceMap EMPTY = {};

// Building - Farm
const ResourceMap FARM_BUILD_COST = {
    {BasicResource::MONEY, 50},
    {BasicResource::FOOD, 100},
    {BasicResource::WOOD, 25}
};
const ResourceMap FARM_PRODUCTION = {
    {BasicResource::MONEY, 1},
    {BasicResource::FOOD, 5}
};


// Building - HeadQuarters
const ResourceMap HQ_BUILD_COST = {
    {BasicResource::MONEY, 750},
    {BasicResource::FOOD, 1000},
    {BasicResource::WOOD, 500},
    {BasicResource::STONE, 250}
};
const ResourceMap HQ_PRODUCTION = {
    {BasicResource::MONEY, 10},
    {BasicResource::FOOD, 2},
};


// Building - Outpost
const ResourceMap OUTPOST_BUILD_COST = {
    {BasicResource::MONEY, -100},
    {BasicResource::FOOD, 200},
    {BasicResource::WOOD, 200},
    {BasicResource::STONE, 25}
};

const ResourceMap OUTPOST_PRODUCTION = {
    {BasicResource::MONEY, -5},
    {BasicResource::FOOD, -2}
};

// sawmill
const Course::ResourceMap SAWMILL_BUILD_COST = {
    {Course::BasicResource::MONEY, 50},
    {Course::BasicResource::FOOD, 100},
    {Course::BasicResource::WOOD, 25}
};
const Course::ResourceMap SAWMILL_PRODUCTION = {
    {Course::BasicResource::MONEY, 1},
    {Course::BasicResource::WOOD, 5}
};

// goldmine
const Course::ResourceMap GOLDMINE_BUILD_COST = {
    {Course::BasicResource::MONEY, 100},
    {Course::BasicResource::FOOD, 100},
    {Course::BasicResource::WOOD, 45}
};
const Course::ResourceMap GOLDMINE_PRODUCTION = {
    {Course::BasicResource::MONEY, 6},
    {Course::BasicResource::ORE, 4}
};


// Worker - BasicWorker
const ResourceMapDouble BW_WORKER_EFFICIENCY = {
    {MONEY, 0.25},
    {FOOD, 1.00},
    {WOOD, 0.75},
    {STONE, 0.50},
    {ORE, 0.50}
};

const Course::ResourceMap BW_RECRUITMENT_COST = {
    {MONEY, 10},
    {FOOD, 25}
};

const Course::ResourceMap UNIT_CONSUMPTION = {
    {FOOD, -5}
};

// scout
const Course::ResourceMap SCOUT_COST = {
    {MONEY, 20},
    {FOOD, 25}
};

// builder
const Course::ResourceMap BUILDER_COST = {
    {MONEY, 100},
    {FOOD, 30}
};


const ResourceMap FOREST_BP = {
    {MONEY, 1},
    {FOOD, 3},
    {WOOD, 5},
    {STONE, 1},
    {ORE, 0},
};

const ResourceMap GRASSLAND_BP = {
    {MONEY, 2},
    {FOOD, 5},
    {WOOD, 1},
    {STONE, 1},
    {ORE, 0},
};

const ResourceMap MOUNTAIN_BP = {
    {MONEY, 3},
    {FOOD, 0},
    {WOOD, 1},
    {STONE, 5},
    {ORE, 3},
};

const ResourceMap WATER_BP = {
    {MONEY, 1},
    {FOOD, 3},
    {WOOD, 0},
    {STONE, 0},
    {ORE, 0},
};

}

#endif // GAMERESOURCEMAPS_HH
