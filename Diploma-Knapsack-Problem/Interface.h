#pragma once

#include "Header.h"
#include "Elements.h"

namespace Interface
{
    void StartWork(Elements& elements, std::vector<ushint>& hollow);

    namespace Hollow
    {
	std::vector<ushint> manualImport();
	std::vector<ushint> completefileInport(std::string filename);
    }

    namespace ForOutput
    {
	void	    setFileWay(const std::string& FileWay);
	std::string getFileWay();
	void	    output(const std::vector<ElementsList>& object);
    }
}