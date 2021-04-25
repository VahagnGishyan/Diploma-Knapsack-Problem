#include "Interface.h"
#include <cstdlib>

using namespace Interface;

static std::string s_fileWay;

void Interface::defaultWork()
{
    std::cout << "Initealization Elements form file(data1.txt)" << std::endl;
    std::string filename = "data1.txt";
    Elements elements(filename);

    //std::vector<ushint> data = Interface::Hollow::manualImport();
    std::vector<ushint> data = Interface::Hollow::completefileInport("data0.txt");

    for (ushint index = 0; index < static_cast<ushint>(data.size()); ++index)
	std::cout << data[index] << std::endl;
    std::cout << std::endl;

    Interface::StartWork(elements, data);
    //bool key = false;
    //outputResult(elements, data, key);
}



void		    Interface::	StartWork(Elements& elements, std::vector<ushint>& hollow)
{
    ushint number = static_cast<ushint>(hollow.size());
    std::cout << "Start Work" << std::endl;
    for (ushint index = 0; index < number; ++index)
    {
	std::vector<ElementsList> result = elements.knapasck_LimitElement(hollow[index]);
	std::cout << std::endl;
	if (result.size() == 0)
	{
	    std::cout << "result is Empty" << std::endl;
	}
	for (ushint start = 0; start < result.size(); ++start)
	{
	    std::cout << result[start].m_count << "\t:: " <<
		result[start].m_element.m_value << ", " <<
		result[start].m_element.m_length << ", " <<
		result[start].m_element.m_priorityCoefficient << std::endl;
	}
    }
}


std::vector<ushint> Hollow::	manualImport()
{
    std::cout << "Input length number ::";
    int number = 0;
    std::cin >> number;
    std::vector<ushint> data(number);
    std::cout << "Input sizes" << std::endl;
    for (ushint index = 0; index < number; ++index)
    {
	std::cin >> data[index];
    }
    std::cout << "Over inputing" << std::endl << std::endl;
    return data;
}
std::vector<ushint> Hollow::	completefileInport(std::string filename)
{
    std::ifstream variableForInputtingDataFromFile(filename);
    std::vector<std::string> reservStringsFromFile;

    //is file not open
    if (!variableForInputtingDataFromFile)
    {
	std::cerr << "File " << filename << " is not found" << std::endl;
    }

    while (!variableForInputtingDataFromFile.eof())
    {
	std::string line;
	getline(variableForInputtingDataFromFile, line);
	reservStringsFromFile.push_back(line);
    }

    std::vector<ushint> data;
    uShInt size = static_cast<uShInt>(reservStringsFromFile.size());
    data.resize(size);

    for (uShInt start = 0; start < size; ++start)
    {
	std::string reservNumber = "";
	for (uShInt index = 0; index < reservStringsFromFile[start].size(); ++index)
	{
	    reservNumber += reservStringsFromFile[start][index];
	}
	data[start] = std::stoi(reservNumber);
    }

    return data;
}


void		    ForOutput::	setFileWay(const std::string& FileWay)
{
    s_fileWay = FileWay;
}
std::string	    ForOutput::	getFileWay()
{
    return s_fileWay;
}
void		    ForOutput::	output(const std::vector<ElementsList>& object)
{
    std::string temporaryData;
    for (ushint start = 0; start < object.size(); ++start)
    {
	//kody kisat a
    }
}

void outputResult(Elements& elements, std::vector<ushint>& hollow, const bool key)
{
    std::ofstream dataForOutput("dataResult.txt");
    if (!dataForOutput)
    {
	std::cerr << "File " << "dataResult.txt" << " is not found" << std::endl;
    }

    for (int index = 0; index < static_cast<int>(elements.size()); ++index)
	dataForOutput << "Elements[" << index << "]" << "\n" <<
	"\t" << "Value = " << elements[index].m_value << "\n" <<
	"\t" << "Length = " << elements[index].m_length << std::endl;
    dataForOutput << "\n\n";

    ushint number = static_cast<ushint>(hollow.size());

    for (ushint index = 0; index < number; ++index)
    {
	std::vector<ElementsList> result;


	if (key)
	    result = elements.knapasck_LimitElement(hollow[index]);
	else
	    result = elements.knapsack_intermediate(hollow[index]);

	dataForOutput << "Line size = " << hollow[index] << std::endl;

	if (!result.size())
	{
	    dataForOutput << "result is Empty" << std::endl << std::endl;
	    continue;
	}

	for (int start = 0; start < static_cast<int>(result.size()); ++start)
	{
	    for (int index = 0; index < static_cast<int>(elements.size()); ++index)
	    {
		if (result[start].m_element == elements[index])
		{
		    dataForOutput << result[start].m_count << "*(Element[" << index << "])" << std::endl;
		    break;
		}
	    }
	}
	dataForOutput << "\n";
    }
}



//std::vector<ushint> Elements::manualImport()
//{
//
//}
//std::vector<ushint> Elements::completefileInport(std::string filename)
//{
//    std::cout << "Start Work" << std::endl;
//    for (ushint index = 0; index < number; ++index)
//    {
//	std::vector<ElementsList> result = elements.knapasck_LimitElement(data[index]);
//	std::cout << std::endl;
//	if (result.size() == 0)
//	{
//	    std::cout << "result is Empty" << std::endl;
//	}
//	for (ushint start = 0; start < result.size(); ++start)
//	{
//	    std::cout << result[start].m_count << "\t:: " <<
//		result[start].m_element.m_value << ", " <<
//		result[start].m_element.m_length << ", " <<
//		result[start].m_element.m_priorityCoefficient << std::endl;
//	}
//    }
//}