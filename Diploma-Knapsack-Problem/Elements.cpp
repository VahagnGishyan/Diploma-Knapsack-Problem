#include "Elements.h"

//struct Element
Element::Element(int length, double value) : m_value(value), m_length(length)
{
    assert(length > 0);
    m_priorityCoefficient = value / length;
}
Element::Element(const Element& copyObject)
{
    m_value = copyObject.m_value;
    m_length = copyObject.m_length;
    m_priorityCoefficient = copyObject.m_priorityCoefficient;
    m_number = copyObject.m_number;
}
Element::Element(Element&& copyObject) noexcept
{
    m_value = copyObject.m_value;
    m_length = copyObject.m_length;
    m_priorityCoefficient = copyObject.m_priorityCoefficient;
    m_number = copyObject.m_number;

    copyObject.m_length = 0;
    copyObject.m_priorityCoefficient = 0;
    copyObject.m_value = 0;
    copyObject.m_number = 0;
}

//Operators
std::ostream& operator<< (std::ostream& out, const Element& object)
{
    std::cout << "\tValue ::\t\t" << object.m_value << std::endl <<
	"\tLength ::\t\t" << object.m_length << std::endl <<
	"\tPriority Coefficient ::\t" << object.m_priorityCoefficient;
    return out;
}
Element& Element::operator= (const Element& object)
{
    if (this == &object)
	return *this;

    m_length = object.m_length;
    m_value = object.m_value;
    m_priorityCoefficient = object.m_priorityCoefficient;
    m_number = object.m_number;
    return *this;
}
bool Element::operator==(const Element& drob)
{
    return ((m_length == drob.m_length) && (m_value == drob.m_value));
}
bool Element::operator!=(const Element& drob)
{
    return ((m_length != drob.m_length) && (m_value != drob.m_value));
}

//Class Elements => container class Element
Elements::Elements()
{

}
Elements::Elements(std::string filename)
{
    //varible
    std::ifstream variableForInputtingDataFromFile(filename);
    std::vector<std::string> reservStringsFromFile;
    std::vector<std::vector<int>> temporaryData;

    //is file not open
    if (!variableForInputtingDataFromFile)
    {
	std::cerr << "File " << filename << " is not found" << std::endl;
    }

    //input form file
    while (!variableForInputtingDataFromFile.eof())
    {
	std::string line;
	getline(variableForInputtingDataFromFile, line);
	reservStringsFromFile.push_back(line);
    }

    uShInt size = static_cast<uShInt>(reservStringsFromFile.size());
    temporaryData.resize(size);
    m_data.resize(size);

    //input m_data from "reservStringsFromFile"
    for (uShInt start = 0; start < size; ++start)
    {
	std::string reservNumber = "";
	for (uShInt index = 0; index < reservStringsFromFile[start].size(); ++index)
	{
	    char symbol = reservStringsFromFile[start][index];
	    if ((symbol >= '0') && (symbol <= '9'))
	    {
		reservNumber += symbol;
	    }
	    else if(reservNumber.size())
	    {
		temporaryData[start].push_back(std::stoi(reservNumber));
		reservNumber = "";
	    }
	}
	temporaryData[start].push_back(std::stoi(reservNumber));
    }

    for (ushint start = 0; start < size; ++start)
    {
	m_data[start].m_length = temporaryData[start][0];
	m_data[start].m_value = temporaryData[start][1];
	m_data[start].m_number = temporaryData[start][2];
    }
}

//For Work
void Elements::print()
{
    const uShInt size = static_cast<uShInt>(m_data.size());
    for (uShInt start = 0; start < size; ++start)
	std::cout << "Element " << start << "\n" << m_data[start] << std::endl;
    std::cout << std::endl;
}
void Elements::print(std::vector<Element> printData)
{
    const uShInt size = static_cast<uShInt>(printData.size());
    for (uShInt start = 0; start < size; ++start)
	std::cout << "Element " << start << "\n" << printData[start] << std::endl;
    std::cout << std::endl;
}

void Elements::mergSort(std::vector<Element>& array)
{
    ushint length = static_cast<ushint>(array.size());


    ushint MergeIterator;
    ushint LeftBorder;
    ushint MidBorder;
    ushint RightBorder;

    for (ushint BlockSizeIterator = 1; BlockSizeIterator < length; BlockSizeIterator *= 2)
    {
	ushint LeftBlockIterator;
	ushint RightBlockIterator;

	for (ushint BlockIterator = 0; BlockIterator < length - BlockSizeIterator; BlockIterator += 2 * BlockSizeIterator)
	{
	    LeftBlockIterator = 0;
	    RightBlockIterator = 0;
	    LeftBorder = BlockIterator;
	    MidBorder = BlockIterator + BlockSizeIterator;
	    RightBorder = BlockIterator + 2 * BlockSizeIterator;
	    RightBorder = (RightBorder < length) ? RightBorder : length;

	    std::vector<Element> SortedBlock(RightBorder - LeftBorder);

	    while (LeftBorder + LeftBlockIterator < MidBorder && MidBorder + RightBlockIterator < RightBorder)
	    {
		if (array[LeftBorder + LeftBlockIterator].m_value > array[MidBorder + RightBlockIterator].m_value)
		{
		    SortedBlock[LeftBlockIterator + RightBlockIterator] = array[LeftBorder + LeftBlockIterator];
		    LeftBlockIterator += 1;
		}
		else
		{
		    SortedBlock[LeftBlockIterator + RightBlockIterator] = array[MidBorder + RightBlockIterator];
		    RightBlockIterator += 1;
		}
	    }
	    while (LeftBorder + LeftBlockIterator < MidBorder)
	    {
		SortedBlock[LeftBlockIterator + RightBlockIterator] = array[LeftBorder + LeftBlockIterator];
		LeftBlockIterator += 1;
	    }
	    while (MidBorder + RightBlockIterator < RightBorder)
	    {
		SortedBlock[LeftBlockIterator + RightBlockIterator] = array[MidBorder + RightBlockIterator];
		RightBlockIterator += 1;
	    }

	    for (MergeIterator = 0; MergeIterator < LeftBlockIterator + RightBlockIterator; MergeIterator++)
	    {
		array[LeftBorder + MergeIterator] = SortedBlock[MergeIterator];
	    }
	}
    }
}
void Elements::swapElement(Element& object1, Element& object2)
{
    Element obj = object1;
    object1 = object2;
    object2 = obj;
}
void Elements::sortByLenght(std::vector<Element>& array)
{
    ushint length = static_cast<uShInt>(array.size());

    ushint MergeIterator;
    ushint LeftBorder;
    ushint MidBorder;
    ushint RightBorder;

    for (ushint BlockSizeIterator = 1; BlockSizeIterator < length; BlockSizeIterator *= 2)
    {
	ushint LeftBlockIterator;
	ushint RightBlockIterator;

	for (ushint BlockIterator = 0; BlockIterator < length - BlockSizeIterator; BlockIterator += 2 * BlockSizeIterator)
	{
	    LeftBlockIterator = 0;
	    RightBlockIterator = 0;
	    LeftBorder = BlockIterator;
	    MidBorder = BlockIterator + BlockSizeIterator;
	    RightBorder = BlockIterator + 2 * BlockSizeIterator;
	    RightBorder = (RightBorder < length) ? RightBorder : length;

	    std::vector<Element> SortedBlock(RightBorder - LeftBorder);

	    while (LeftBorder + LeftBlockIterator < MidBorder && MidBorder + RightBlockIterator < RightBorder)
	    {
		if (array[LeftBorder + LeftBlockIterator].m_length < array[MidBorder + RightBlockIterator].m_length)
		{
		    SortedBlock[LeftBlockIterator + RightBlockIterator] = array[LeftBorder + LeftBlockIterator];
		    LeftBlockIterator += 1;
		}
		else
		{
		    SortedBlock[LeftBlockIterator + RightBlockIterator] = array[MidBorder + RightBlockIterator];
		    RightBlockIterator += 1;
		}
	    }
	    while (LeftBorder + LeftBlockIterator < MidBorder)
	    {
		SortedBlock[LeftBlockIterator + RightBlockIterator] = array[LeftBorder + LeftBlockIterator];
		LeftBlockIterator += 1;
	    }
	    while (MidBorder + RightBlockIterator < RightBorder)
	    {
		SortedBlock[LeftBlockIterator + RightBlockIterator] = array[MidBorder + RightBlockIterator];
		RightBlockIterator += 1;
	    }

	    for (MergeIterator = 0; MergeIterator < LeftBlockIterator + RightBlockIterator; MergeIterator++)
	    {
		array[LeftBorder + MergeIterator] = SortedBlock[MergeIterator];
	    }
	}
    }
}
void Elements::sortByPriorityCoefficient(std::vector<Element>& array)
{
    ushint length = static_cast<uShInt>(array.size());

    ushint MergeIterator;
    ushint LeftBorder;
    ushint MidBorder;
    ushint RightBorder;

    for (ushint BlockSizeIterator = 1; BlockSizeIterator < length; BlockSizeIterator *= 2)
    {
	ushint LeftBlockIterator;
	ushint RightBlockIterator;

	for (ushint BlockIterator = 0; BlockIterator < length - BlockSizeIterator; BlockIterator += 2 * BlockSizeIterator)
	{
	    LeftBlockIterator = 0;
	    RightBlockIterator = 0;
	    LeftBorder = BlockIterator;
	    MidBorder = BlockIterator + BlockSizeIterator;
	    RightBorder = BlockIterator + 2 * BlockSizeIterator;
	    RightBorder = (RightBorder < length) ? RightBorder : length;

	    std::vector<Element> SortedBlock(RightBorder - LeftBorder);

	    while (LeftBorder + LeftBlockIterator < MidBorder && MidBorder + RightBlockIterator < RightBorder)
	    {
		if (array[LeftBorder + LeftBlockIterator].m_priorityCoefficient > array[MidBorder + RightBlockIterator].m_priorityCoefficient)
		{
		    SortedBlock[LeftBlockIterator + RightBlockIterator] = array[LeftBorder + LeftBlockIterator];
		    LeftBlockIterator += 1;
		}
		else
		{
		    SortedBlock[LeftBlockIterator + RightBlockIterator] = array[MidBorder + RightBlockIterator];
		    RightBlockIterator += 1;
		}
	    }
	    while (LeftBorder + LeftBlockIterator < MidBorder)
	    {
		SortedBlock[LeftBlockIterator + RightBlockIterator] = array[LeftBorder + LeftBlockIterator];
		LeftBlockIterator += 1;
	    }
	    while (MidBorder + RightBlockIterator < RightBorder)
	    {
		SortedBlock[LeftBlockIterator + RightBlockIterator] = array[MidBorder + RightBlockIterator];
		RightBlockIterator += 1;
	    }

	    for (MergeIterator = 0; MergeIterator < LeftBlockIterator + RightBlockIterator; MergeIterator++)
	    {
		array[LeftBorder + MergeIterator] = SortedBlock[MergeIterator];
	    }
	}
    }

}
void Elements::push_back(const Element& object)
{
    m_data.push_back(object);
}
void Elements::pop_back()
{
    m_data.pop_back();
}
void Elements::clear()
{
    m_data.clear();
}
void Elements::resize(int size)
{
    assert(size > 0 && "Size will be positve");
    m_data.resize(size);
}
//Operators
Elements& Elements::operator= (const Elements& drob)
{
    m_data = drob.m_data;
    return *this;
}

std::vector<ElementsList>		Elements::algorithm_knapsack(int Length)
{
    std::vector <std::vector<Element>> elementList(Length + 1);
    std::vector<double> arrayForMaxValue(Length + 1);

    ushint size = static_cast<ushint>(m_data.size());

    double reservMaxValue = 0;
    arrayForMaxValue[0] = 0;

    for (ushint start = 1; start <= Length; ++start)
    {
	arrayForMaxValue[start] = arrayForMaxValue[start - 1];
	elementList[start] = elementList[start - 1];
	for (ushint index = 0; index < size; ++index)
	{
	    if (m_data[index].m_length <= start)
	    {
		if (arrayForMaxValue[start] < arrayForMaxValue[start - m_data[index].m_length] + m_data[index].m_value)
		{
		    arrayForMaxValue[start] = arrayForMaxValue[start - m_data[index].m_length] + m_data[index].m_value;

		    const double lastValue = arrayForMaxValue[start - m_data[index].m_length];
		    const ushint lastValueIndex = static_cast<ushint>(start - m_data[index].m_length);
		    if (reservMaxValue > lastValue)
		    {
			elementList[start] = elementList[lastValueIndex];
			reservMaxValue = arrayForMaxValue[lastValueIndex];
		    }
		    reservMaxValue += m_data[index].m_value;
		    elementList[start].push_back(m_data[index]);
		    assert(reservMaxValue == arrayForMaxValue[start]);
		}
	    }
	}
    }

    std::vector<ElementsList> result;


    result.push_back(elementList[Length][0]);
    for (ushint start = 1; start < elementList[Length].size(); ++start)
    {
	bool key = true;
	for (ushint index = 0; index < result.size(); ++index)
	{
	    if (result[index].m_element == elementList[Length][start])
	    {
		key = false;
		++result[index].m_count;
		break;
	    }
	}
	if (key)
	{
	    ElementsList object;
	    object.m_count = 1;
	    object.m_element = elementList[Length][start];
	    result.push_back(object);
	}
    }


    return result;
}
double				Elements::algorithm_knapsack_ReturnMaxValue(int Length)
{
    size_t n = m_data.size();

    std::vector<double> arrayForMaxValue(Length + 1);
    arrayForMaxValue[0] = 0;

    for (ushint start = 1; start <= Length; ++start)
    {
	arrayForMaxValue[start] = arrayForMaxValue[start - 1];

	for (ushint index = 0; index < n; ++index)
	{
	    if (m_data[index].m_length <= start)
	    {
		arrayForMaxValue[start] = std::max(arrayForMaxValue[start], arrayForMaxValue[start - m_data[index].m_length] + m_data[index].m_value);
	    }
	}
    }
    return arrayForMaxValue[Length];
}
std::vector<ElementsList>	Elements::algorithm_greedy(int length)
{
    std::vector<ElementsList> reservElements;
    sortByPriorityCoefficient(m_data);
    for (ushint start = 0; start < m_data.size(); ++start)
    {
	if (m_data[start].m_length <= length)
	{
	    ushint count = static_cast<ushint>(length / m_data[start].m_length);
	    if (count > 0)
	    {
		ElementsList object;
		object.m_count = count;
		object.m_element = m_data[start];
		reservElements.push_back(object);
		length -= count * m_data[start].m_length;
	    }
	}
    }
    return (reservElements);
}
double				Elements::algorithm_greedy_ReturnMaxValue(int length)
{
    double maxValue = 0;
    sortByPriorityCoefficient(m_data);
    for (ushint index = 0; index < m_data.size() && length > 0; ++index)
    {
	if (m_data[index].m_length <= length)
	{
	    ushint count = static_cast<ushint>(length / m_data[index].m_length);
	    maxValue += count * m_data[index].m_value;
	    length -= count * m_data[index].m_length;
	}
    }
    return (maxValue);
}
std::vector<ElementsList>	Elements::knapsack_intermediate(int length)
{
    //Determine the preference coefficients for all elements
    decidePreferenceCoefficients();
    std::vector<Element> temporaryData = m_data;

    //Sort by lengths
    sortByLenght(temporaryData);

    //We subtract all the elements whose length is greater than the length of the line.
    while (temporaryData.back().m_length > length)
    {
	temporaryData.pop_back();
    }
    if (temporaryData[0].m_length > length)
    {
	excludeLongElement(temporaryData, length);
	if (temporaryData.size() == 0)
	{
	    std::vector<ElementsList> forNotError;
	    return forNotError;
	}
    }
    //If the elements are the same size, the item with the highest cost is selected
    deleteRepetitionsLength(temporaryData);

    //We find the greatest cost 
    double maxVale = returnGreatCost(temporaryData);
    //If the largest element in size does not have the greatest value, then that element is meaningless
    while (temporaryData.back().m_value < maxVale)
	temporaryData.pop_back();
    //deleteMaxLengthNotMaxElements(temporaryData, maxVale);

    //Sort by preferences coefficient and lengths.
    sortByPriorityCoefficient(temporaryData);

    //If Priority Coefficients are the same, the one with shorter length is selected
    deleteRepetitionsPriorityCoefficients(temporaryData);

    std::vector<ElementsList> resultElementListFromGreedy = knapsack_forIntermediate_Greedy(temporaryData, length);
    std::vector<ElementsList> resultElementListFromDynamicProgramming = knapsack_forIntermediate_DynamicProgramming(temporaryData, length);

    if (resultElementListFromGreedy.size() == 0 && resultElementListFromDynamicProgramming.size() == 0)
    {
	std::vector<ElementsList> resultIsEmpty;
	return resultIsEmpty;
    }
    else if (resultElementListFromGreedy.size() == 0)
	return (resultElementListFromDynamicProgramming);
    else if (resultElementListFromDynamicProgramming.size() == 0)
	return (resultElementListFromGreedy);

    for (ushint start = 0; start < resultElementListFromDynamicProgramming.size(); ++start)
    {
	bool key = true;
	for (ushint index = 0; index < resultElementListFromGreedy.size(); ++index)
	{
	    if (resultElementListFromGreedy[index].m_element == resultElementListFromDynamicProgramming[start].m_element)
	    {
		resultElementListFromGreedy[index].m_count += resultElementListFromDynamicProgramming[start].m_count;
		key = false;
		break;
	    }
	}
	if (key)
	{
	    resultElementListFromGreedy.push_back(resultElementListFromDynamicProgramming[start]);
	}
    }

    std::vector<ElementsList>& result = resultElementListFromGreedy;

    return result;
}
std::vector<ElementsList>	Elements::knapsack_forIntermediate_Greedy(std::vector<Element>& temporaryData, int& length)
{
    //Varibles
    std::vector<ElementsList> reservElements;

    if (length % temporaryData[0].m_length == 0)
    {
	ElementsList object;
	ushint count = length / temporaryData[0].m_length;
	object.m_count = count;
	object.m_element = temporaryData[0];
	reservElements.push_back(object);
	length = 0;
	return reservElements;
    }

    const ushint maxLenght = returnMaxLengthFromSecondElement(temporaryData);
    ushint Length = length - maxLenght;

    const ushint size = static_cast<ushint>(temporaryData.size());
    for (ushint start = 0; start < size; ++start)
    {
	ushint count = Length / temporaryData[start].m_length;
	if (count > 0)
	{
	    ElementsList object;
	    object.m_count = count;
	    object.m_element = temporaryData[start];
	    reservElements.push_back(object);
	    Length -= count * temporaryData[0].m_length;
	}
	else
	{
	    length = Length + maxLenght;
	    return reservElements;
	}
    }
    return reservElements;
}
std::vector<ElementsList>	Elements::knapsack_forIntermediate_DynamicProgramming(const std::vector<Element>& data, int& length)
{
    std::vector <std::vector<ElementsList>> elementList(length + 1);

    std::vector<Element> temporaryData;
    for (ushint start = 0; start < data.size(); ++start)
	if (data[start].m_length <= length)
	    temporaryData.push_back(data[start]);

    if (length == 0)
	return elementList[0];

    std::vector<double> arrayForMaxValue(length + 1);

    const ushint size = static_cast<ushint>(temporaryData.size());

    double reservMaxValue = 0;
    arrayForMaxValue[0] = 0;

    for (ushint start = 1; start <= length; ++start)
    {
	arrayForMaxValue[start] = arrayForMaxValue[start - 1];
	elementList[start] = elementList[start - 1];
	for (ushint index = 0; index < size; ++index)
	{
	    if (temporaryData[index].m_length <= start)
	    {
		if (arrayForMaxValue[start] < arrayForMaxValue[start - temporaryData[index].m_length] + temporaryData[index].m_value)
		{
		    arrayForMaxValue[start] = arrayForMaxValue[start - temporaryData[index].m_length] + temporaryData[index].m_value;

		    const double lastValue = arrayForMaxValue[start - temporaryData[index].m_length];
		    const ushint lastValueIndex = static_cast<ushint>(start - temporaryData[index].m_length);
		    if (reservMaxValue > lastValue)
		    {
			elementList[start] = elementList[lastValueIndex];
			reservMaxValue = arrayForMaxValue[lastValueIndex];
		    }
		    reservMaxValue += temporaryData[index].m_value;

		    if (elementList[start].size() == 0)
		    {
			ElementsList object;
			object.m_count = 1;
			object.m_element = temporaryData[index];
			elementList[start].push_back(object);
		    }
		    else if (elementList[start].back().m_element != temporaryData[index])
		    {
			ElementsList object;
			object.m_count = 1;
			object.m_element = temporaryData[index];
			elementList[start].push_back(object);
		    }
		    else
			++elementList[start].back().m_count;

		    assert(reservMaxValue == arrayForMaxValue[start]);
		}
	    }
	}
    }

    return (elementList.back());
}

bool Elements::			isMemberDataNumberEmpty()
{
    for (ushint index = 0; index < size(); ++index)
	if (m_data[index].m_number != 0)
	    return false;
    return true;
}
std::vector<ElementsList>	Elements::knapasck_LimitElement(int length)
{
    assert(length > 0 && "Length is not posytive");

    if (isMemberDataNumberEmpty())
    {
	std::vector<ElementsList> ForNotError;
	return ForNotError;
    }

    struct State
    {
	double				m_maxValue = 0;
	std::vector<Element>		m_temporaryData;
	std::vector<Element>		m_bestResult;
    };

    //Initealiation temporaryData
    std::vector<State>			states(length + 1);
    {
	ushint size = static_cast<ushint>(m_data.size());
	std::vector<Element>		temporaryData(size);
	for (ushint start = 0; start < size; ++start)
	{
	    if (m_data[start].m_length <= length)
	    {
		temporaryData[start] = (m_data[start]);
	    }
	}
	states[0].m_maxValue = 0;
	states[0].m_temporaryData = temporaryData;
    }

    double reservMaxValue = 0;

    for (ushint start = 1; start <= length; ++start)
    {
	states[start] = states[start - 1];

	//std::vector<Element>& temporaryData= states[start].m_temporaryData;
	ushint size = static_cast<ushint>(states[start].m_temporaryData.size());
	for (ushint index = 0; index < size; ++index)
	{
	    const Element& object = states[start].m_temporaryData[index];
	    if (object.m_number <= 0)
		continue;
	    if (object.m_length <= start)
	    {
		if (states[start].m_maxValue < states[start - object.m_length].m_maxValue + object.m_value)
		{
		    if (states[start - object.m_length].m_temporaryData[index].m_number <= 0)
			continue;
		    states[start] = states[start - object.m_length];

		    states[start].m_maxValue += object.m_value;
		    --states[start].m_temporaryData[index].m_number;
		    states[start].m_bestResult.push_back(object);
		}
	    }
	}
    }

    //save data
    for (ushint start = 0; start < static_cast<ushint>(states[length].m_temporaryData.size()); ++start)
    {
	for (ushint index = 0; index < m_data.size(); ++index)
	{
	    if (states[length].m_temporaryData[start] == m_data[index])
	    {
		m_data[index].m_number = states[length].m_temporaryData[start].m_number;
		break;
	    }
	}
    }
    
    if (states[length].m_bestResult.size() == 0)
    {
	std::vector<ElementsList> ForNotError;
	return ForNotError;
    }

    std::vector<ElementsList> result;
    result.push_back(states[length].m_bestResult[0]);

    for (ushint start = 1; start < static_cast<ushint>(states[length].m_bestResult.size()); ++start)
    {
	bool key = true;
	for (ushint index = 0; index < result.size(); ++index)
	{
	    if (states[length].m_bestResult[start] == result[index].m_element)
	    {
		key = false;
		++result[index].m_count;
		break;
	    }
	}
	if (key)
	{
	    result.push_back(states[length].m_bestResult[start]);
	}
    }

    return result;
}

void	Elements::excludeLongElement(std::vector<Element>& temporaryData, int length)
{
    assert(temporaryData.size() != 0 && "Data is empty");

    int size = temporaryData.size();
    std::vector<ushint> reservIndex;
    for (ushint start = 0; start < size; ++start)
	if (temporaryData[start].m_length <= length)
	    reservIndex.push_back(start);

    if (size == reservIndex.size())
	return;

    size = reservIndex.size();
    std::vector<Element> reservData = temporaryData;
    temporaryData.clear();
    temporaryData.shrink_to_fit();
    temporaryData.resize(size);

    for (ushint start = 0; start < size; ++start)
	temporaryData[start] = reservData[reservIndex[start]];
}
void	Elements::deleteRepetitionsLength(std::vector<Element>& temporaryData)
{
    std::vector<ushint> reservIndex;
    reservIndex.push_back(0);

    for (ushint start = 1; start < temporaryData.size(); ++start)
    {
	if (temporaryData[start].m_length == temporaryData[reservIndex.back()].m_length)
	{
	    if (temporaryData[start].m_value > temporaryData[reservIndex.back()].m_value)
		reservIndex.back() = start;
	}
	else
	    reservIndex.push_back(start);
    }

    if (reservIndex.size() == 0)
	return;

    std::vector<Element> reservData;

    for (ushint start = 0; start < reservIndex.size(); ++start)
	reservData.push_back(temporaryData[reservIndex[start]]);

    temporaryData = reservData;
    temporaryData.shrink_to_fit();
}
void	Elements::deleteRepetitionsPriorityCoefficients(std::vector<Element>& temporaryData)
{
    std::vector<ushint> reservIndex;
    reservIndex.push_back(0);

    for (ushint start = 1; start < temporaryData.size(); ++start)
    {
	if (temporaryData[start].m_priorityCoefficient == temporaryData[reservIndex.back()].m_priorityCoefficient)
	{
	    if (temporaryData[start].m_length < temporaryData[reservIndex.back()].m_length)
		reservIndex.back() = start;
	}
	else
	    reservIndex.push_back(start);
    }

    if (reservIndex.size() == 0)
	return;

    std::vector<Element> reservData;

    for (ushint start = 0; start < reservIndex.size(); ++start)
	reservData.push_back(temporaryData[reservIndex[start]]);

    temporaryData = reservData;
    temporaryData.shrink_to_fit();
}
double	Elements::returnGreatCost(std::vector<Element>& temporaryData)
{
    double maxValue = temporaryData[0].m_value;
    ushint size = static_cast<ushint>(temporaryData.size());

    for (ushint start = 1; start < size; ++start)
    {
	if (maxValue < temporaryData[start].m_value)
	{
	    maxValue = temporaryData[start].m_value;
	}
    }
    return (maxValue);
}
void	Elements::deleteMaxLengthNotMaxElements(std::vector<Element>& temporaryData, double maxValue)
{
    ushint rememberIndex = 0;
    ushint size = static_cast<ushint>(temporaryData.size());

    for (ushint start = 0; start < size; ++start)
    {
	if (temporaryData[start].m_value == maxValue)
	{
	    rememberIndex = start;
	    break;
	}
    }

    std::vector<Element> reservData = temporaryData;
    temporaryData.clear();
    temporaryData.shrink_to_fit();

    for (ushint start = rememberIndex; start < reservData.size(); ++start)
	temporaryData.push_back(reservData[start]);
}
void	Elements::decidePreferenceCoefficients()
{
    if (m_data[0].m_priorityCoefficient > 0)
	return;
    for (ushint start = 0; start < m_data.size(); ++start)
	m_data[start].m_priorityCoefficient = m_data[start].m_value / m_data[start].m_length;
}
ushint	Elements::returnMaxLengthFromSecondElement(std::vector<Element>& temporaryData)
{
    ushint maxLenght = temporaryData[1].m_length;
    const ushint size = static_cast<ushint>(temporaryData.size());
    for (ushint start = 2; start < size; ++start)
    {
	if (maxLenght < temporaryData[start].m_length)
	{
	    maxLenght = temporaryData[start].m_length;
	}
    }
    return maxLenght;
}

std::vector<int>			giveLinesLengths(std::string filename)
{
    //varible
    std::ifstream				variableForInputtingDataFromFile(filename);
    std::vector<std::string>	reservStringsFromFile;
    std::vector<int>			linesLength;

    //is file not open
    if (!variableForInputtingDataFromFile)
    {
	std::cerr << "File " << filename << " is not found" << std::endl;
    }

    //input form file
    while (!variableForInputtingDataFromFile.eof())
    {
	std::string line;
	getline(variableForInputtingDataFromFile, line);
	reservStringsFromFile.push_back(line);
    }

    uShInt size = static_cast<uShInt>(reservStringsFromFile.size());
    linesLength.resize(size);

    //input m_data from "reservStringsFromFile"
    for (uShInt start = 0; start < size; ++start)
    {
	std::string reservNumber = "";
	for (uShInt index = 0; index < reservStringsFromFile[start].size(); ++index)
	{
	    reservNumber += reservStringsFromFile[start][index];
	}
	linesLength[start] = std::stoi(reservNumber);
    }

    return (linesLength);
}