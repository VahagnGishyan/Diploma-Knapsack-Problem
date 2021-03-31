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
}
Element::Element(Element&& copyObject) noexcept
{
	m_value = copyObject.m_value;
	m_length = copyObject.m_length;
	m_priorityCoefficient = copyObject.m_priorityCoefficient;
	copyObject.m_length = 0;
	copyObject.m_priorityCoefficient = 0;
	copyObject.m_value = 0;
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

	m_length				= object.m_length;
	m_value					= object.m_value;
	m_priorityCoefficient	= object.m_priorityCoefficient;

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
Elements::Elements(std::string filename)
{
	//varible
	std::ifstream variableForInputtingDataFromFile(filename);
	std::vector<std::string> reservStringsFromFile;

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
	m_data.resize(size);

	//input m_data from "reservStringsFromFile"
	for (uShInt start = 0; start < size; ++start)
	{
		std::string reservNumber = "";
		for (uShInt index = 0; index < reservStringsFromFile[start].size(); ++index)
		{
			if (reservStringsFromFile[start][index] == ' ')
			{
				m_data[start].m_length = std::stoi(reservNumber);
				reservNumber = "";
				continue;
			}
			reservNumber += reservStringsFromFile[start][index];
		}
		m_data[start].m_value = std::stod(reservNumber);
		m_data[start].m_priorityCoefficient = m_data[start].m_value / m_data[start].m_length;
	}
}

//For Work
void						Elements::print()
{
	const uShInt size = static_cast<uShInt>(m_data.size());
	for (uShInt start = 0; start < size; ++start)
		std::cout << "Element " << start << "\n" << m_data[start] << std::endl;
	std::cout << std::endl;
}
void						Elements::print(std::vector<Element> printData)
{
	const uShInt size = static_cast<uShInt>(printData.size());
	for (uShInt start = 0; start < size; ++start)
		std::cout << "Element " << start << "\n" << printData[start] << std::endl;
	std::cout << std::endl;
}

//For Sort
void						Elements::sortn2()
{
	const uShInt size = static_cast<uShInt>(m_data.size());
	uShInt indexMaxElement = 0;
	for (uShInt start = 0; start < size - 1; ++start)
	{
		indexMaxElement = start;
		for (uShInt index = start + 1; index < size; ++index)
		{
			if (m_data[indexMaxElement].m_priorityCoefficient < m_data[index].m_priorityCoefficient)
				indexMaxElement = index;
		}
		swapElement(m_data[indexMaxElement], m_data[start]);
	}
}
void						Elements::swapElement(Element& object1, Element& object2)
{
	Element obj = object1;
	object1 = object2;
	object2 = obj;
}
void						Elements::sortByLenght(std::vector<Element>& temporaryData)
{
	const uShInt size = static_cast<uShInt>(temporaryData.size());
	uShInt indexMaxElement = 0;
	for (uShInt start = 0; start < size - 1; ++start)
	{
		indexMaxElement = start;
		for (uShInt index = start + 1; index < size; ++index)
		{
			if (temporaryData[indexMaxElement].m_length < temporaryData[index].m_length)
				indexMaxElement = index;
		}
		swapElement(temporaryData[indexMaxElement], temporaryData[start]);
	}
}
void						Elements::sortByPriorityCoefficient(std::vector<Element>& temporaryData)
{
	const uShInt size = static_cast<uShInt>(temporaryData.size());
	uShInt indexMaxElement = 0;
	for (uShInt start = 0; start < size - 1; ++start)
	{
		indexMaxElement = start;
		for (uShInt index = start + 1; index < size; ++index)
		{
			if (temporaryData[indexMaxElement].m_priorityCoefficient < temporaryData[index].m_priorityCoefficient)
				indexMaxElement = index;
		}
		swapElement(temporaryData[indexMaxElement], temporaryData[start]);
	}
}
//Operators
Elements&					Elements::operator= (const Elements& drob)
{
	m_data = drob.m_data;
	return *this;
}

//Lconum
//Ըստ n*w սկզբունքի
std::vector<Element>		Elements::algorithm_knapsack(int Length)
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
	return elementList[Length];
}
double						Elements::algorithm_knapsack_ReturnMaxValue(int Length)
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
//Ըստ Ագահ Ալգորիթմի
std::vector<ElementsList>	Elements::algorithm_greedy(int length)
{
	std::vector<ElementsList> reservElements;
	sortn2();
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
double						Elements::algorithm_greedy_ReturnMaxValue(int length)
{
	double maxValue = 0;
	sortn2();
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
////Միջանկյան Ալգորիթմ
std::vector<ElementsList>	Elements::knapsack_intermediate(int length)
{
	//Determine the preference coefficients for all elements
	decidePreferenceCoefficients();
	std::vector<Element> temporaryData = m_data;
	//print(temporaryData);

	//Sort by lengths
	sortByLenght(temporaryData);
	//print(temporaryData);

	//We subtract all the elements whose length is greater than the length of the line.
	if (temporaryData.back().m_length > length)
	{
		temporaryData.clear();
		temporaryData.shrink_to_fit();

		std::vector<ElementsList> forNotError;
		return forNotError;
	}
	if (temporaryData[0].m_length > length)
	{
		excludeLongElement(temporaryData, length);
		if (temporaryData.size() == 0)
		{
			std::vector<ElementsList> forNotError;
			return forNotError;
		}
		print(temporaryData);
	}

	//If the elements are the same size, the item with the highest cost is selected
	deleteRepetitionsԼenght(temporaryData);
	//print(temporaryData);

	//We find the greatest cost 
	double maxVale = returnGreatCost(temporaryData);
	//If the largest element in size does not have the greatest value, then that element is meaningless
	deleteMaxLengthMiniNotMaxElements(temporaryData, maxVale);
	//print(temporaryData);

	//Sort by preferences coefficient and lengths.
	sortByPriorityCoefficient(temporaryData);
	//print(temporaryData);

	//Մնում ա ագահ և դինամիկ լցունումները 

	//Task fulfillment
	std::vector<ElementsList> resultElementListFromGreedy = knapsack_forIntermediate_Greedy(temporaryData, length);
	std::vector<ElementsList> resultElementListFromDynamicProgramming = knapsack_forIntermediate_DynamicProgramming(temporaryData, length);
	//resultElementListFromGreedy += resultElementListFromDynamicProgramming;

	//for test
	std::vector<ElementsList> resultElementListFroTest = knapsack_forIntermediate_DynamicProgrammingForTest(temporaryData, length);
	if (resultElementListFroTest.size() != resultElementListFromDynamicProgramming.size())
	{
		std::cout << "Reult 1 :: " << resultElementListFroTest.size() << std::endl;
		std::cout << "Reult 1 :: " << resultElementListFroTest.size() << std::endl;
		assert(resultElementListFroTest.size() == resultElementListFromDynamicProgramming.size());
	}
	const ushint sizeFortest = static_cast<ushint>(resultElementListFroTest.size());
	for (ushint start = 0; start < sizeFortest; ++start)
	{
		bool key = false;
		for (ushint index = 0; index < sizeFortest; ++index)
		{
			if ((resultElementListFroTest[start].m_element == resultElementListFromDynamicProgramming[index].m_element) &&
				(resultElementListFroTest[start].m_count == resultElementListFromDynamicProgramming[index].m_count))
			{
				key = true;
				break;
			}
		}
		assert(key && "resultElementListFromDynamicProgramming is not working correct");
	}

	if (resultElementListFromGreedy.size() == 0 && resultElementListFromDynamicProgramming.size() == 0)
	{
		std::vector<ElementsList> resultIsEmpty;
		return resultIsEmpty;
	}
	else if (resultElementListFromGreedy.size() == 0)
		return (resultElementListFromDynamicProgramming);
	else if(resultElementListFromDynamicProgramming.size() == 0)
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
//Ագահ ալգորիթմ Միջանկյալի համար
std::vector<ElementsList>	Elements::knapsack_forIntermediate_Greedy(std::vector<Element>& temporaryData, int& length)
{
	//Varibles
	std::vector<ElementsList> reservElements;

	//Ստուգում ենք, երկարությունը հո առաջին նախընտրելիության տարրի բազմապատիկը չի
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

	//Առաջին նախընտրելիության տարրից բացի մյուս բոլոր տարրերի միջից ամենամեծ երկարությունը
	const ushint maxLenght = returnMaxLengthFromSecondElement(temporaryData);
	//Գտնում ենք այն երկարությունը որը պետք է լցոնենք
	ushint Length = length - maxLenght;

	//Կատարում ենք լցոնում
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
std::vector<ElementsList>	Elements::knapsack_forIntermediate_DynamicProgrammingForTest(std::vector<Element>& temporaryData, int& length)
{
	std::vector<ElementsList> reservElements;

	if (length == 0)
		return reservElements;

	std::vector <std::vector<Element>> elementList(length + 1);
	std::vector<double> arrayForMaxValue(length + 1);

	const ushint size = static_cast<ushint>(m_data.size());

	double reservMaxValue = 0;
	arrayForMaxValue[0] = 0;

	for (ushint start = 1; start <= length; ++start)
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

	if (elementList.size() == 0)
		return (result);

	const ushort sizeResult = static_cast<ushint>(elementList[length].size());

	{
		ElementsList object;
		object.m_count = 1;
		object.m_element = elementList[length][0];
		result.push_back(object);
	}

	for (ushort start = 1; start < sizeResult; ++start)
	{
		if (elementList[length][start] != result.back().m_element)
		{
			ElementsList object;
			object.m_count = 1;
			object.m_element = elementList[length][start];
			result.push_back(object);
		}
		else
		{
			++result.back().m_count;
		}
	}

	return (result);
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
void	Elements::deleteRepetitionsԼenght(std::vector<Element>& temporaryData)
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
void	Elements::deleteMaxLengthMiniNotMaxElements(std::vector<Element>& temporaryData, double maxValue)
{
	ushint rememberIndex;
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
	if (m_data[0].m_priorityCoefficient >= 0)
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
//void Elements::sortByPreferenceCoefficients(std::vector<Element*> elementSortLenght)
//{
//	elementSortLenght.resize(m_data.size());
//	for
//}

//int							Elements::maxCoefficientElementIsCorrect(int length)
//{
//	if (length % m_data[0].m_length)
//		return 0;
//	return length / m_data[0].m_length;
//}
////correct the elements
//std::vector<Element>		Elements::correct_elementlengthIsGreaterLength()
//{
//	std::vector<Element> newData = m_data;
//	shint size = newData.size();
//	for(ushint start = 0; start < size; ++start)
//	{
//		if(newData[start].m_length >)
//}
//void 						Elements::correct_elementLengtheSame()
//{
//
//}
//void 						Elements::correct_elementIsNotPreferable()
//{
//
//}

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