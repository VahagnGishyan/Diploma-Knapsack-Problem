#include "CalculateWorkingTime.h"

void RandomGeneration::ForTiruyt(std::string filename, ushint size, ushint seed)
{
    srand(seed);

    std::ofstream file(filename);

    //is file not open
    if (!file)
    {
	std::cerr << "File " << filename << " is not found" << std::endl;
    }

    do
    {
	file << rand() % 1500 << std::endl;
    }     
    while (--size);
}

void RandomGeneration::ForElements(std::string filename, ushint size, ushint seed)
{
    srand(seed);

    std::ofstream file(filename);

    //is file not open
    if (!file)
    {
	std::cerr << "File " << filename << " is not found" << std::endl;
    }

    do
    {
	shint count = 4;
	ushint length;
	while (--count)
	{
	    length = rand() % 64;
	    if (!length)
		length = 64;
	    file << length;
	    if (count != 1)
		file << " ";
	}
	file << std::endl;
    }     
    while (--size);
}