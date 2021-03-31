#include "Elements.h" 
//#include "TestForElements.h"


void testingAndPrint(std::string filename, int length)
{
	Elements elements(filename);
	std::vector<Element> result = elements.algorithm_knapsack(length);

	double maxValue = 0;
	for (ushint index = 0; index < result.size(); ++index)
		maxValue += result[index].m_value;
	double realMaxValue = elements.algorithm_knapsack_ReturnMaxValue(length);

	std::cout << maxValue << " == " << realMaxValue << std::endl;
	assert(maxValue == realMaxValue);

	for (ushint index = 0; index < result.size(); ++index)
		std::cout << "Element[" << index << "]\n" << result[index] << std::endl;
	std::cout << std::endl << std::endl;
}

void test_my()
{
	testingAndPrint("data0.txt", 15);
	testingAndPrint("data1.txt", 37);
	testingAndPrint("data2.txt", 109);
	testingAndPrint("data3.txt", 17);
	testingAndPrint("data4.txt", 600);
	testingAndPrint("data5.txt", 111);
}

void testtingWhit(std::string filename, std::vector<int> linesLenght)
{
	Elements elements(filename);
	for (ushint start = 0; start < linesLenght.size(); ++start)
	{
		double resultMaxValue = elements.algorithm_greedy_ReturnMaxValue(linesLenght[start]);

		std::vector<ElementsList> result = elements.algorithm_greedy(linesLenght[start]);
		double value = 0;
		for (ushint start = 0; start < result.size(); ++start)
		{
			for (ushint index = 0; index < result[start].m_count; ++index)
				value += result[start].m_element.m_value;
		}
		if (value != resultMaxValue)
		{
			std::cout << "Error" << std::endl;
			std::cout << "	Result :: " << resultMaxValue << std::endl;
			std::cout << "	Value  :: " << value << std::endl;
		}
	}
}

int main()
{
	
	//test_my();

	

	//Stanum en file, togheri erkarutyunneri masin. 

	//std::vector<int> resultLineLength = giveLinesLengths("lines.txt");
	//testtingWhit("data0.txt", resultLineLength);
	 
	std::string filename = "data0.txt";
	Elements elements(filename);
	std::vector<ElementsList> result = elements.knapsack_intermediate(150);
	for (ushint start = 0; start < result.size(); ++start)
	{
		std::cout << result[start].m_count << "\t:: " <<
			result[start].m_element.m_value << ", " <<
			result[start].m_element.m_length << ", " <<
			result[start].m_element.m_priorityCoefficient << std::endl;
	}

	//Element unit;
	//Elements elements("data0.txt");
	//elements.print();
	//elements.sortn2();
	//elements.print();
	//
	//
	//std::cout<< "\n\nMax value " << elements.knapsack_ReturnMaxValue(15)<<std::endl;

	//std::vector<Element> result = elements.knapsack(15);
	//for (ushint index = 0; index < result.size(); ++index)
	//	std::cout << "Element[" << index << "] :: \n" << result[index] << std::endl;

	//my_TestForElements::InputAndOutput::test();
	//my_TestForElements::InputAndOutput::test();

	return 0;
}