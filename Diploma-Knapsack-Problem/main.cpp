#include "Elements.h" 
#include "Interface.h"

//for testing
#include "CalculateWorkingTime.h"

int main()
{
    std::cout << "Start main()" << std::endl;

    //Interface::defaultWork();

    CalculateWorkingTime::ForIntermediate(staticDefaulCharsData::default16);
    CalculateWorkingTime::ForDynamicProgramming(staticDefaulCharsData::default16);

    CalculateWorkingTime::ForIntermediate(staticDefaulCharsData::default32);
    CalculateWorkingTime::ForDynamicProgramming(staticDefaulCharsData::default32);

    CalculateWorkingTime::ForIntermediate(staticDefaulCharsData::default64);
    CalculateWorkingTime::ForDynamicProgramming(staticDefaulCharsData::default64);

    return 0;
}