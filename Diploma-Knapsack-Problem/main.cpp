#include "Elements.h" 
#include "Interface.h"

#include "CalculateWorkingTime.h"

void Work(std::string filename)
{
    std::vector<std::string> files;
    files.push_back("forTiruyt_1.txt");
    files.push_back("forTiruyt_10.txt");
    files.push_back("forTiruyt_100.txt");
    files.push_back("forTiruyt_1000.txt");
    files.push_back("forTiruyt_10000.txt");

    RandomGeneration::ForHollow(files[0], 1);
    RandomGeneration::ForHollow(files[1], 10);
    RandomGeneration::ForHollow(files[2], 100);
    RandomGeneration::ForHollow(files[3], 1000);
    RandomGeneration::ForHollow(files[4], 10000);

    std::vector<std::string> elements;
    elements.push_back("forElements_16.txt");
    elements.push_back("forElements_32.txt");
    elements.push_back("forElements_64.txt");
    elements.push_back("forElements_128.txt");
    elements.push_back("forElements_256.txt");

    std::cout << "A" << std::endl;
    RandomGeneration::ForElements(elements[0], 16);
    std::cout << "B" << std::endl;
    RandomGeneration::ForElements(elements[1], 32);
    std::cout << "C" << std::endl;
    RandomGeneration::ForElements(elements[2], 64);
    std::cout << "D" << std::endl;
    RandomGeneration::ForElements(elements[3], 128);
    std::cout << "E" << std::endl;
    RandomGeneration::ForElements(elements[4], 256);
    std::cout << "F" << std::endl;
}

int main()
{
    std::cout << "Start main()" << std::endl;

    CalculateWorkingTime::ForIntermediate();

    return 0;
}