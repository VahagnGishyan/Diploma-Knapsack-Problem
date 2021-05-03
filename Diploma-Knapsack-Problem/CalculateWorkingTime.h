#pragma once

#include "Header.h"
#include "Elements.h"
#include "Interface.h"


class InputCharacteristic
{
private:
    uint m_elementsCount;   //const

    uint m_elementsLength;  //max length
    uint m_elementsValue;   //max value
    uint m_elementsNumber;  //max number

    uint m_lineCount;	    //const
    uint m_lineLength;	    //max length

    uint m_cycle;	    //const
public:
    InputCharacteristic();
    InputCharacteristic(int eCount, int eLength, int eValue, int eNumber, int lCount, int lLength, int cycle);
    
    void setElementsCount(int count);
    void setElementsLength(int length);
    void setElementsValue(int value);
    void setElementsNumber(int number);
    void setLineCount(int count);
    void setLineLength(int length);
    void setCycle(int cycle);

    uint getElementsCount() const;
    uint getElementsLength() const;
    uint getElementsValue() const;
    uint getElementsNumber() const;
    uint getLineCount() const;
    uint getLineLength() const;
    uint getCycle() const;
};
class OutputCharacteristic
{
private:
    bool m_elementsLimit;
    bool m_resultList;
public:
    void setElementsLimit(bool answer);
    void setResultList(bool answer);

    bool getElementsLimit() const;
    bool getResultList() const;
};

using inputChars  = InputCharacteristic;
using outputChars = OutputCharacteristic;

namespace RandomGeneration
{
    //for hollow
    void                ForHollow(std::string filename, ushint size, ushint seed = 4541);
    std::vector<ushint> ForHollow(ushint size, ushint seed = 4541);
    std::vector<ushint> ForHollow(const inputChars& inputArgument, ushint seed = 4541);

    //for elements
    void                ForElements(std::string filename, ushint size, ushint seed = 4541);
    Elements            ForElements(ushint size, ushint seed = 4541);
    Elements            ForElements(const inputChars& inputArgument, ushint seed = 4541);
}

namespace staticDefaulCharsData
{
    static const InputCharacteristic default16 (16,  32,  32,  32,  64,  1600, 100);
    static const InputCharacteristic default32 (32,  64,  64,  64,  100, 1600, 100);
    static const InputCharacteristic default64 (64,  64,  64,  64,  128, 1600, 100);
    static const InputCharacteristic default128(128, 128, 128, 128, 256, 3200, 100);
    static const InputCharacteristic default256(256, 128, 128, 128, 512, 6400, 100);
}

namespace CalculateWorkingTime
{
    using namespace staticDefaulCharsData;

    std::vector<double> ForIntermediate(ushint cycle);
    std::vector<double> ForDynamicProgramming(ushint cycle);

    //Limithed
    double ForGready(const inputChars& InputState = default32);	    //gready
    double ForNameDP(const inputChars& InputState = default32);		    //dynamic programming
    double ForLimitElement(const inputChars& InputState = default32);	    //intermediate

    //UnLimithed
    double ForGready(const inputChars& InputState = default32);		    //gready
    double ForDynamicProgramming(const inputChars& InputState = default32); //dynamic programming
    double ForIntermediate(const inputChars& InputState = default32);	    //intermediate

}
