#ifndef GAMERESOURCEMAPS_HH
#define GAMERESOURCEMAPS_HH

#include "core/basicresources.h"

// This file contains definitions for resource ma+ps used in the game
namespace GameConstResourceMaps {

using namespace Course;

const ResourceMap EMPTY = {};

// Building - Farm
const ResourceMap FARM_BUILD_COST = {
    {BasicResource::WOOD, 20}
};
const ResourceMap FARM_PRODUCTION = {
    {BasicResource::FOOD, 15}
};


// Building - HeadQuarters
const ResourceMap HQ_BUILD_COST = {
    {BasicResource::MONEY, 750},
    {BasicResource::FOOD, 1000},
    {BasicResource::WOOD, 500},
    {BasicResource::STONE, 250}
};
const ResourceMap HQ_PRODUCTION = {
};


// Building - Outpost
const ResourceMap OUTPOST_BUILD_COST = {
    {BasicResource::WOOD, 20}
};

const ResourceMap OUTPOST_PRODUCTION = {
};

// sawmill
const Course::ResourceMap SAWMILL_BUILD_COST = {
    {Course::BasicResource::WOOD, 20}
};
const Course::ResourceMap SAWMILL_PRODUCTION = {
    {Course::BasicResource::WOOD, 10}
};

// goldmine
const Course::ResourceMap GOLDMINE_BUILD_COST = {
    {Course::BasicResource::WOOD, 50}
};
const Course::ResourceMap GOLDMINE_PRODUCTION = {
    {Course::BasicResource::MONEY, 10},
};


// Worker - BasicWorker, not used in the game
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

//Consumpion of food per unit per turn
const Course::ResourceMap UNIT_CONSUMPTION = {
    {FOOD, -5}
};

// scout
const Course::ResourceMap SCOUT_COST = {
    {MONEY, 10},
};

// builder
const Course::ResourceMap BUILDER_COST = {
    {MONEY, 20},
};


const ResourceMap FOREST_BP = {
    {WOOD, 5}
};

const ResourceMap GRASSLAND_BP = {
    {FOOD, 10}
};

const ResourceMap SWAMP_BP = {
    {FOOD, 12}
};


const ResourceMap MOUNTAIN_BP = {
    {MONEY, 5},
};

const ResourceMap WATER_BP = {
    {FOOD, 5},
};

}

#endif // GAMERESOURCEMAPS_HH
