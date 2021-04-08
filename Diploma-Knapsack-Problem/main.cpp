#include "Elements.h" 

int main()
{
    std::string filename = "data1.txt";
    Elements elements(filename);


    std::vector<ElementsList> result = elements.knapsack_intermediate(150);

    for (ushint start = 0; start < result.size(); ++start)
    {
	std::cout << result[start].m_count << "\t:: " <<
	    result[start].m_element.m_value << ", " <<
	    result[start].m_element.m_length << ", " <<
	    result[start].m_element.m_priorityCoefficient << std::endl;
    }

    return 0;
}