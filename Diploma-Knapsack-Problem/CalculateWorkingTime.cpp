#include "CalculateWorkingTime.h"

InputCharacteristic::InputCharacteristic()
{
    m_elementsCount    = 0;

    m_elementsLength   = 0;
    m_elementsValue    = 0;
    m_elementsNumber   = 0;

    m_lineCount        = 0;
    m_lineLength       = 0;

    m_cycle            = 0;
}
InputCharacteristic::InputCharacteristic(int eCount, int eLength, int eValue, int eNumber, int lCount, int lLength, int cycle)
{
    m_elementsCount  = eCount;

    m_elementsLength = eLength;
    m_elementsValue  = eValue;
    m_elementsNumber = eNumber;

    m_lineCount      = lCount;
    m_lineLength     = lLength;

    m_cycle          = cycle;
}

void InputCharacteristic::setElementsCount(int count)
{
    m_elementsCount = count;
}
void InputCharacteristic::setElementsLength(int length)
{
    m_elementsLength = length;
}
void InputCharacteristic::setElementsValue(int value)
{
    m_elementsValue = value;
}
void InputCharacteristic::setElementsNumber(int number)
{
    m_elementsNumber = number;
}
void InputCharacteristic::setLineCount(int count)
{
    m_lineCount = count;
}
void InputCharacteristic::setLineLength(int length)
{
    m_lineLength = length;
}
void InputCharacteristic::setCycle(int cycle)
{
    m_cycle = cycle;
}

uint InputCharacteristic::getElementsCount() const 
{
    return m_elementsCount;
}
uint InputCharacteristic::getElementsLength() const
{
    return m_elementsLength;
}
uint InputCharacteristic::getElementsValue() const
{
    return m_elementsValue;
}
uint InputCharacteristic::getElementsNumber() const
{
    return m_elementsNumber;
}
uint InputCharacteristic::getLineCount() const
{
    return m_lineCount;
}
uint InputCharacteristic::getLineLength() const
{
    return m_lineLength;
}
uint InputCharacteristic::getCycle() const
{
    return m_cycle;
}

void OutputCharacteristic::setElementsLimit(bool answer)
{
    m_elementsLimit = answer;
}
void OutputCharacteristic::setResultList(bool answer)
{
    m_resultList = answer;
}

bool                 OutputCharacteristic::  getElementsLimit() const 
{
    return m_elementsLimit;
}
bool                 OutputCharacteristic::  getResultList() const
{
    return m_resultList;
}

void                 RandomGeneration::      ForHollow(std::string filename, ushint size, ushint seed)
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
	ushint length = rand() % 1500;
	if (length == 0)
	{
	    length = 1500;
	}
	file << length;
	if(size != 1)
	    file << std::endl;
    }     
    while (--size);
}
std::vector<ushint>  RandomGeneration::      ForHollow(ushint size, ushint seed)
{
    srand(seed);

    std::vector<ushint> hollow;

    hollow.resize(size);

    for(ushint index = 0; index < size; ++index)
    {
	hollow[index] = rand() % 1500;
	if (hollow[index] == 0)
	{
	    hollow[index] = 1500;
	}
    }

    return hollow;
}
std::vector<ushint>  RandomGeneration::      ForHollow(const inputChars& inputArgument, ushint seed)
{
    srand(seed);

    std::vector<ushint> hollow;
    size_t size = static_cast<size_t>(inputArgument.getLineCount());
    int maxLineLength = inputArgument.getLineLength();

    hollow.resize(size);

    for (ushint index = 0; index < size; ++index)
    {
	hollow[index] = rand() % maxLineLength;
	if (hollow[index] == 0)
	{
	    hollow[index] = maxLineLength;
	}
    }

    return hollow;
}


void                 RandomGeneration::      ForElements(std::string filename, ushint size, ushint seed)
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
	    if (length == 0)
		length = 64;
	    file << length;
	    if (count != 1)
		file << " ";
	}
	if (size != 1)
	    file << std::endl;
    }     
    while (--size);
}
Elements             RandomGeneration::      ForElements(ushint size, ushint seed)
{
    srand(seed);

    Elements data;
    data.resize(size);

    for (ushint index = 0; index < size; ++index)
    {
	Element object;

	ushint length = rand() % 64;
	if (length == 0)
	    length = 64;
	object.m_length = length;
    
	ushint value = rand() % 64;
	if (value == 0)
	    value = 64;
	object.m_value = value;

	ushint number = rand() % 64;
	if (number == 0)
	    number = 64;
	object.m_number = number;

	object.m_priorityCoefficient = static_cast<double>(value) / static_cast<double>(length);

	data[index] = object;
    }

    return data;
}
Elements             RandomGeneration::      ForElements(const inputChars& inputArgument, ushint seed)
{
    srand(seed);

    const int    elementsLength = static_cast<int>(inputArgument.getElementsLength());
    const int    elementsValue  = static_cast<int>(inputArgument.getElementsValue());
    const int    elementsNumber = static_cast<int>(inputArgument.getElementsNumber());
    const size_t elementsCount  = static_cast<size_t>(inputArgument.getElementsCount());
    Elements data;
    data.resize(elementsCount);

    for (ushint index = 0; index < elementsCount; ++index)
    {
	Element object;

	ushint length = rand() % elementsLength;
	if (length == 0)
	    length = elementsLength;
	object.m_length = length;

	ushint value = rand() % elementsValue;
	if (value == 0)
	    value = elementsValue;
	object.m_value = value;

	ushint number = rand() % elementsNumber;
	if (number == 0)
	    number = elementsNumber;
	object.m_number = number;

	object.m_priorityCoefficient = static_cast<double>(value) / static_cast<double>(length);

	data[index] = object;
    }

    return data;
}

std::vector<double> CalculateWorkingTime::ForIntermediate(ushint cycle)
{
    double startTime = clock()/1000;
    double lastTime  = startTime;

    double resultTimeLine = 0.0;
    double resultTimeLineCount = 0;
    double resultTimeHollw = 0.0;

    //constexpr ushint dataMaxSize = 1000;
    //uint dataIndex = 0;
    //std::array<double,dataMaxSize> data;
    //std::vector<double> dataAssistent;

    for (ushint count = 0; count < 1; ++count)
    {

	//if (count != 0 && count % 5 == 0)
	//{
	//    std::cout << count << std::endl;
	//    double endTime = clock() / 1000;
	//    std::cout << "Global Work time :: " << endTime - startTime << std::endl;
	//    std::cout << "Local  Work time :: " << endTime - lastTime  << std::endl;
	//    lastTime = endTime;
	//}
	    
	double timeLine = 0.0;
	ushint timeLineCount = 0;

	double timeHollw = 0.0;
	ushint timeHollwCount = 0;

	ushint seed = static_cast<ushint>(time(0));

	for (ushint start = 0; start < 100; ++start)
	{
	    double HollowWorkTime = 0.0;

	    std::vector<ushint> hollow = RandomGeneration::ForHollow(100, seed);
	    Elements elements = RandomGeneration::ForElements(32, seed);

	    if (hollow.size() == 0)
		continue;

	    if (elements.size() == 0)
		continue;

	    for (ushint index = 0; index < hollow.size(); ++index)
	    {
		//std::cout << "\t\t" << index << std::endl;

		int lineLength = hollow.at(index);

		ulong start_time = clock();
		elements.knapsack_intermediate(lineLength);
		ulong end_time = clock();
		
		ulong timeChange = end_time - start_time;

		if (timeChange > 15)
		{
		    timeChange = 1;
		}

		HollowWorkTime += timeChange;



		timeLine += timeChange;
		++timeLineCount;

		//if (dataIndex < dataMaxSize)
		//    data[dataIndex] = timeChange;
		//else
		//    dataAssistent.push_back(timeChange);
		//++dataIndex;
	    }
	    
	    //double result = timeLine / timeLineCount;
	    //std::cout << "\ttimeLine" << timeLine << std::endl;
	    //std::cout << "\timeLineCount" << timeLineCount << std::endl;
	    //std::cout << "\tresult :: " << result << std::endl;
	    //std::cout << std::endl;
	 //   if (result > 5)
	 //   {
		//for (ushint start = 0; start < hollow.size(); ++start)
		//{
		//    std::cout << hollow[start] << ", ";
		//    if (start != 0 && start % 19 == 0)
		//    {
		//	std::cout << std::endl;
		//    }
		//}
		//std::cout << std::endl;
		//for (ushint start = 0; start < elements.size(); ++start)
		//{
		//    std::cout << elements[start] << std::endl;
		//}

		//std::vector<double> forNotError;
		//return forNotError;
	 //   }


	    timeHollw += (static_cast<double>(HollowWorkTime));
	    ++timeHollwCount;
	}

	timeLine /= timeLineCount;
	resultTimeLine += timeLine;
	++resultTimeLineCount;

	timeHollw /= timeHollwCount;
	resultTimeHollw = timeHollw;
    }

    resultTimeLine /= resultTimeLineCount;

    double endTime = clock() / 1000;
    std::cout << 100 << std::endl;
    std::cout << "Global Work time :: " << endTime - startTime << std::endl;
    std::cout << "Local  Work time :: " << endTime - lastTime  << std::endl;
    lastTime = endTime;

    std::cout << "\nResult" << std::endl;
    std::cout << "Work Line   time :: " << resultTimeLine << "ms"  << std::endl;
    std::cout << "Work Hollow time :: " << resultTimeHollw << "ms" << std::endl;

    std::cout << std::endl;
    double dataResult = 0;
   /* if (dataIndex >= dataMaxSize)
    {
	const ushint size = data.size();
	for (ushint index = 0; index < size; ++index)
	{
	    std::cout << data[index] << ", ";
	    if (index != 0 && index % 25 == 0)
		std::cout << std::endl;
	    dataResult += data[index];
	}
	for (ushint index = 0; index < dataAssistent.size(); ++index)
	{
	    std::cout << dataAssistent[index] << " ";
	    dataResult += dataAssistent[index];
	}
    }
    else
    {
	for (ushint index = 0; index < dataIndex; ++index)
	{
	    std::cout << data[index] << " ";
	    if (index != 0 && index % 25 == 0)
		std::cout << std::endl;
	    dataResult += data[index];
	}
    }*/


    //std::cout << "\nResult :: " << dataResult / dataIndex << std::endl;

    std::vector<double> forNotError;
    return forNotError;
}
std::vector<double> CalculateWorkingTime::ForDynamicProgramming(ushint cycle)
{
    double startTime = clock() / 1000;
    double lastTime = startTime;

    double resultTimeLine = 0.0;
    double resultTimeLineCount = 0;
    double resultTimeHollw = 0.0;

    //constexpr ushint dataMaxSize = 1000;
    //uint dataIndex = 0;
    //std::array<double,dataMaxSize> data;
    //std::vector<double> dataAssistent;

    for (ushint count = 0; count < 1; ++count)
    {

	//if (count != 0 && count % 5 == 0)
	//{
	//    std::cout << count << std::endl;
	//    double endTime = clock() / 1000;
	//    std::cout << "Global Work time :: " << endTime - startTime << std::endl;
	//    std::cout << "Local  Work time :: " << endTime - lastTime  << std::endl;
	//    lastTime = endTime;
	//}

	double timeLine = 0.0;
	ushint timeLineCount = 0;

	double timeHollw = 0.0;
	ushint timeHollwCount = 0;

	for (ushint start = 0; start < 100; ++start)
	{
	    double HollowWorkTime = 0.0;

	    std::vector<ushint> hollow = RandomGeneration::ForHollow(100);
	    Elements elements = RandomGeneration::ForElements(32);

	    if (hollow.size() == 0)
		continue;

	    if (elements.size() == 0)
		continue;


	    //double result = timeLine / timeLineCount;
	    //std::cout << "\ttimeLine" << timeLine << std::endl;
	    //std::cout << "\timeLineCount" << timeLineCount << std::endl;
	    //std::cout << "\tresult :: " << result << std::endl;
	    //std::cout << std::endl;
	 //   if (result > 5)
	 //   {
		//for (ushint start = 0; start < hollow.size(); ++start)
		//{
		//    std::cout << hollow[start] << ", ";
		//    if (start != 0 && start % 19 == 0)
		//    {
		//	std::cout << std::endl;
		//    }
		//}
		//std::cout << std::endl;
		//for (ushint start = 0; start < elements.size(); ++start)
		//{
		//    std::cout << elements[start] << std::endl;
		//}

		//std::vector<double> forNotError;
		//return forNotError;
	 //   }


	    timeHollw += (static_cast<double>(HollowWorkTime));
	    ++timeHollwCount;
	}

	timeLine /= timeLineCount;
	resultTimeLine += timeLine;
	++resultTimeLineCount;

	timeHollw /= timeHollwCount;
	resultTimeHollw = timeHollw;
    }

    resultTimeLine /= resultTimeLineCount;

    double endTime = clock() / 1000;
    std::cout << 100 << std::endl;
    std::cout << "Global Work time :: " << endTime - startTime << std::endl;
    std::cout << "Local  Work time :: " << endTime - lastTime << std::endl;
    lastTime = endTime;

    std::cout << "\nResult" << std::endl;
    std::cout << "Work Line   time :: " << resultTimeLine << "ms" << std::endl;
    std::cout << "Work Hollow time :: " << resultTimeHollw << "ms" << std::endl;

    std::cout << std::endl;
    double dataResult = 0;
    /* if (dataIndex >= dataMaxSize)
     {
	 const ushint size = data.size();
	 for (ushint index = 0; index < size; ++index)
	 {
	     std::cout << data[index] << ", ";
	     if (index != 0 && index % 25 == 0)
		 std::cout << std::endl;
	     dataResult += data[index];
	 }
	 for (ushint index = 0; index < dataAssistent.size(); ++index)
	 {
	     std::cout << dataAssistent[index] << " ";
	     dataResult += dataAssistent[index];
	 }
     }
     else
     {
	 for (ushint index = 0; index < dataIndex; ++index)
	 {
	     std::cout << data[index] << " ";
	     if (index != 0 && index % 25 == 0)
		 std::cout << std::endl;
	     dataResult += data[index];
	 }
     }*/


     //std::cout << "\nResult :: " << dataResult / dataIndex << std::endl;

    std::vector<double> forNotError;
    return forNotError;
}

//Limithed
//double CalculateWorkingTime::ForGready(const inputChars& InputState)
//{
//    const ushint cycle = InputState.getCycle();
//
//    double HollowWorkTime = 0.0;
//    ulong  HollowWorkCount = 0;
//    double LineWorkTime = 0.0;
//    ulong  LineWorkCount = 0;
//
//    for (ushint start = 0; start < cycle; ++start)
//    {
//	std::vector<ushint> hollow = RandomGeneration::ForHollow(InputState);
//	Elements elements = RandomGeneration::ForElements(InputState);
//
//	if (hollow.size() == 0)
//	{
//	    std::cout << "Hollow size == 0" << std::endl;
//	    continue;
//	}
//	if (elements.size() == 0)
//	{
//	    std::cout << "Elements size == 0" << std::endl;
//	    continue;
//	}
//
//	for (ushint index = 0; index < hollow.size(); ++index)
//	{
//	    //std::cout << "\t\t" << index << std::endl;
//
//	    int lineLength = hollow.at(index);
//
//	    ulong start_time = clock();
//	    elements.knapasck_LimitGready(lineLength);
//	    ulong end_time = clock();
//
//	    ulong timeChange = end_time - start_time;
//
//	    HollowWorkTime += timeChange;
//
//	    LineWorkTime += timeChange;
//	    ++LineWorkCount;
//	}
//	++HollowWorkCount;
//    }
//
//    HollowWorkTime = HollowWorkTime / HollowWorkCount;
//    LineWorkTime = LineWorkTime / LineWorkCount;
//
//    std::cout << "\nResult" << std::endl;
//    std::cout << "Work Line   time :: " << LineWorkTime << "ms" << std::endl;
//    std::cout << "Work Hollow time :: " << HollowWorkTime << "ms" << std::endl;
//
//    return LineWorkTime;
//}
//double CalculateWorkingTime::ForNameDP(const inputChars& InputState)
//{
//
//}
double CalculateWorkingTime::ForLimitElement(const inputChars InputState)
{
    const ushint cycle = InputState.getCycle();

    double HollowWorkTime = 0.0;
    ulong  HollowWorkCount = 0;
    double LineWorkTime = 0.0;
    ulong  LineWorkCount = 0;

    for (ushint start = 0; start < cycle; ++start)
    {
	std::vector<ushint> hollow = RandomGeneration::ForHollow(InputState);
	Elements elements = RandomGeneration::ForElements(InputState);

	if (hollow.size() == 0)
	{
	    std::cout << "Hollow size == 0" << std::endl;
	    continue;
	}
	if (elements.size() == 0)
	{
	    std::cout << "Elements size == 0" << std::endl;
	    continue;
	}

	for (ushint index = 0; index < hollow.size(); ++index)
	{
	    //std::cout << "\t\t" << index << std::endl;

	    int lineLength = hollow.at(index);

	    ulong start_time = clock();
	    elements.knapasck_LimitElement(lineLength);
	    ulong end_time = clock();

	    ulong timeChange = end_time - start_time;

	    HollowWorkTime += timeChange;

	    LineWorkTime += timeChange;
	    ++LineWorkCount;
	}
	++HollowWorkCount;
    }

    HollowWorkTime = HollowWorkTime / HollowWorkCount;
    LineWorkTime = LineWorkTime / LineWorkCount;

    std::cout << "\nResult" << std::endl;
    std::cout << "Work Line   time :: " << LineWorkTime << "ms" << std::endl;
    std::cout << "Work Hollow time :: " << HollowWorkTime << "ms" << std::endl;

    return LineWorkTime;
}
//UnLimithed
double CalculateWorkingTime::ForGready(const inputChars InputState)
{
    const ushint cycle = InputState.getCycle();

    double HollowWorkTime = 0.0;
    ulong  HollowWorkCount = 0;
    double LineWorkTime = 0.0;
    ulong  LineWorkCount = 0;

    for (ushint start = 0; start < cycle; ++start)
    {
	std::vector<ushint> hollow = RandomGeneration::ForHollow(InputState);
	Elements elements = RandomGeneration::ForElements(InputState);

	if (hollow.size() == 0)
	{
	    std::cout << "Hollow size == 0" << std::endl;
	    continue;
	}
	if (elements.size() == 0)
	{
	    std::cout << "Elements size == 0" << std::endl;
	    continue;
	}

	for (ushint index = 0; index < hollow.size(); ++index)
	{
	    //std::cout << "\t\t" << index << std::endl;

	    int lineLength = hollow.at(index);

	    ulong start_time = clock();
	    elements.algorithm_greedy(lineLength);
	    ulong end_time = clock();

	    ulong timeChange = end_time - start_time;

	    HollowWorkTime += timeChange;

	    LineWorkTime += timeChange;
	    ++LineWorkCount;
	}
	++HollowWorkCount;
    }

    HollowWorkTime = HollowWorkTime / HollowWorkCount;
    LineWorkTime = LineWorkTime / LineWorkCount;

    std::cout << "\nResult" << std::endl;
    std::cout << "Work Line   time :: " << LineWorkTime << "ms" << std::endl;
    std::cout << "Work Hollow time :: " << HollowWorkTime << "ms" << std::endl;

    return LineWorkTime;
}
double CalculateWorkingTime::ForDynamicProgramming(const inputChars InputState)
{
    const ushint cycle = InputState.getCycle();

    double HollowWorkTime = 0.0;
    ulong  HollowWorkCount = 0;
    double LineWorkTime = 0.0;
    ulong  LineWorkCount = 0;

    for (ushint start = 0; start < cycle; ++start)
    {
	std::vector<ushint> hollow = RandomGeneration::ForHollow(InputState);
	Elements elements = RandomGeneration::ForElements(InputState);

	if (hollow.size() == 0)
	{
	    std::cout << "Hollow size == 0" << std::endl;
	    continue;
	}
	if (elements.size() == 0)
	{
	    std::cout << "Elements size == 0" << std::endl;
	    continue;
	}

	for (ushint index = 0; index < hollow.size(); ++index)
	{
	    //std::cout << "\t\t" << index << std::endl;

	    int lineLength = hollow.at(index);

	    ulong start_time = clock();
	    elements.knapsack_DynamicProgramming(lineLength);
	    ulong end_time = clock();

	    ulong timeChange = end_time - start_time;

	    HollowWorkTime += timeChange;

	    LineWorkTime += timeChange;
	    ++LineWorkCount;
	}
	++HollowWorkCount;
    }

    HollowWorkTime = HollowWorkTime / HollowWorkCount;
    LineWorkTime = LineWorkTime / LineWorkCount;

    std::cout << "\nResult" << std::endl;
    std::cout << "Work Line   time :: " << LineWorkTime << "ms" << std::endl;
    std::cout << "Work Hollow time :: " << HollowWorkTime << "ms" << std::endl;

    return LineWorkTime;
}
double CalculateWorkingTime::ForIntermediate(const inputChars InputState)
{
    const ushint cycle = InputState.getCycle();

    double HollowWorkTime = 0.0;
    ulong  HollowWorkCount = 0;
    double LineWorkTime = 0.0;
    ulong  LineWorkCount = 0;

    for (ushint start = 0; start < cycle; ++start)
    {
	std::vector<ushint> hollow = RandomGeneration::ForHollow(InputState);
	Elements elements = RandomGeneration::ForElements(InputState);

	if (hollow.size() == 0)
	{
	    std::cout << "Hollow size == 0" << std::endl;
	    continue;
	}
	if (elements.size() == 0)
	{
	    std::cout << "Elements size == 0" << std::endl;
	    continue;
	}

	for (ushint index = 0; index < hollow.size(); ++index)
	{
	    //std::cout << "\t\t" << index << std::endl;

	    int lineLength = hollow.at(index);

	    ulong start_time = clock();
	    elements.knapsack_intermediate(lineLength);
	    ulong end_time = clock();

	    ulong timeChange = end_time - start_time;

	    HollowWorkTime += timeChange;

	    LineWorkTime += timeChange;
	    ++LineWorkCount;
	}
	++HollowWorkCount;
    }

    HollowWorkTime = HollowWorkTime / HollowWorkCount;
    LineWorkTime   = LineWorkTime   / LineWorkCount;

    std::cout << "\nResult" << std::endl;
    std::cout << "Work Line   time :: " << LineWorkTime << "ms" << std::endl;
    std::cout << "Work Hollow time :: " << HollowWorkTime << "ms" << std::endl;

    return LineWorkTime;
}