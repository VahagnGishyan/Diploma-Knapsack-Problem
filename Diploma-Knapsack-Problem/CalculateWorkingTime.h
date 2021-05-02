#pragma once

#include "Header.h"
#include "Elements.h"
#include "Interface.h"


class InputCharacteristic
{
private:
    uint elementsCount;   //const

    uint elementsLength;  //max length
    uint elementsValue;   //max value
    uint elementsNumber;  //max number

    uint lineCount;	    //const
    uint lineLength;	    //max length

    uint cycle;	    //const
public:
    InputCharacteristic();
    InputCharacteristic(int eCount, int eLength, int eValue, int eNumber, int lCount, int lLength, int cycle);

    void setElementsCount(int count);
    void setElementsLength(int count);
    void setElementsValue(int count);
    void setElementsNumber(int count);
    void setLineCount(int count);
    void setLineLength(int count);
    void setCycle(int count);

    uint getElementsCount();
    uint getElementsLength();
    uint getElementsValue();
    uint getElementsNumber();
    uint getLineCount();
    uint getLineLength();
    uint getCycle();
};

class OutputCharacteristic
{
private:
    bool elementsLimit;
    bool resultList;
public:
    void setElementsLimit(int answer);
    void setResultList(bool answer);

    bool getElementsLimit();
    bool getResultList();
};


using inputChars  = InputCharacteristic;
using outputChars = OutputCharacteristic;


namespace RandomGeneration
{
    //for hollow
    void ForHollow(std::string filename, ushint size, ushint seed = 4541);
    std::vector<ushint> ForHollow(ushint size, ushint seed = 4541);
    std::vector<ushint> ForHollow(const inputChars& size, ushint seed = 4541);

    //for elements
    void ForElements(std::string filename, ushint size, ushint seed = 4541);
    Elements ForElements(ushint size, ushint seed = 4541);
    std::vector<ushint> ForElements(const outputChars& size, ushint seed = 4541);
}



namespace CalculateWorkingTime
{
    std::vector<double> ForIntermediate(ushint cycle = 1);
    std::vector<double> ForDynamicProgramming(ushint cycle = 1);

    namespace Chars
    {
	//Limithed
	double ForNameGready(inputChars InputState, outputChars OutState);		//gready
	double ForNameDP(inputChars InputState, outputChars OutState);			//dynamic programming
	double ForLimitElement(inputChars InputState, outputChars OutState);		//intermediate

	//UnLimithed
	double ForGready(inputChars InputState, outputChars OutState);			//gready
	double ForDynamicProgramming(inputChars InputState, outputChars OutState);	//dynamic programming
	double ForIntermediate(inputChars InputState, outputChars OutState);		//intermediate
    }
}
