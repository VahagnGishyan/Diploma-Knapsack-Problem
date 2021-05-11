#pragma once

#include "Header.h"
#include "Elements.h"
#include "CalculateWorkingTime.h"

namespace Interface
{
    void                    StartWork(Elements& elements, std::vector<ushint>& hollow);
    void                    defaultWork();

    void                    returnMaxValue(std::vector<ushint> &lineLengths, Elements elements, std::ofstream file);

    namespace Hollow
    {
	std::vector<ushint> manualImport();
	std::vector<ushint> completefileInport(std::string filename);
    }

    namespace ForOutput
    {
	void	            setFileWay(const std::string& FileWay);
	std::string         getFileWay();
	void	            output(const std::vector<ElementsList>& object);
    }
}

void                        outputResult(Elements& elements, std::vector<ushint>& hollow, const bool key);

