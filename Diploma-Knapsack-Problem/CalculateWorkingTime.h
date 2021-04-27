#pragma once

#include <ctime>

#include "Header.h"
#include "Elements.h"
#include "Interface.h"


namespace RandomGeneration
{
    void ForHollow(std::string filename, ushint size, ushint seed = 4541);
    std::vector<ushint> ForHollow(ushint size, ushint seed = 4541);
    void ForElements(std::string filename, ushint size, ushint seed = 4541);
    Elements ForElements(ushint size, ushint seed = 4541);
}

namespace CalculateWorkingTime
{

    std::vector<ushint> ForIntermediate(ushint cycle = 1);
    //double CalculateWorkingTime();
}