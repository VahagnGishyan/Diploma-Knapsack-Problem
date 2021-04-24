#include "Interface.h"

using namespace Interface;

static std::string s_fileWay;

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