#include "CalculateWorkingTime.h"

void RandomGeneration::ForHollow(std::string filename, ushint size, ushint seed)
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
std::vector<ushint> RandomGeneration::ForHollow(ushint size, ushint seed)
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
Elements RandomGeneration::ForElements(ushint size, ushint seed)
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