#include "Elements.h" 
#include "Interface.h"

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


	if(key)
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

int main()
{
    std::cout << "Start main()" << std::endl;

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

    return 0;
}