#pragma once
#include "Header.h"

namespace RandomGeneration
{
    void ForTiruyt  (std::string filename, ushint size, ushint seed = 4541);
    void ForElements(std::string filename, ushint size, ushint seed = 4541);
}

namespace CalculateWorkingTime
{
    std::vector<double> ForIntermediate(std::vector<std::string> filenames, std::vector<std::string> elements);
    //double CalculateWorkingTime();
}