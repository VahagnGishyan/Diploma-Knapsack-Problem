#pragma once
#include "Header.h"



struct Element
{
	double				m_value;
	ushint				m_length;
	double				m_priorityCoefficient;
	int 				m_number = 0;

	Element(int			length = 1, double value = 0);
	Element(const		Element&	copyObject);
	Element(Element&&	copyObject) noexcept;

	//Operators
	friend std::ostream& operator<< (std::ostream& out, const Element& object);
	Element& operator= (const Element& drob);
	bool operator==	(const Element& drob);
	bool operator!=	(const Element& drob);


};

struct ElementsList
{
	int		m_count = 1;
	Element m_element;
	ElementsList()
	{

	}
	ElementsList(const Element& object) : m_element(object)
	{

	}
	ElementsList(const Element&& object) : m_element(object)
	{

	}
};

class Elements
{
private:
	std::vector<Element> m_data;

	//For Sort
	void mergSort(std::vector<Element>& Data);
	void swapElement(Element& object1, Element& object2);

	void	sortByLenght(std::vector<Element>& temporaryData);
	void	sortByPriorityCoefficient(std::vector<Element>& temporaryData);	

public:
    void mergSortTest()
    {
	std::vector<Element> data = m_data;
	mergSort(data);
    }
	
    //The default must be the coefficient and everything must be negative if it is not initialized
    Elements();
    Elements(std::string filename);

    //For Work
    void print();
    void print(std::vector<Element> printData);
    void setNumbers()
    {
	for (ushint index = 0; index < m_data.size(); ++index)
	{
	    m_data[index].m_number = 1;
	}
    }
    void setNumbers(int index, int number = 2)
    {
	m_data[index].m_number = number;
    }
    ushint size() const 
    {
	return static_cast<ushint>(m_data.size());
    }
    void push_back(const Element& object);
    void pop_back();
    void clear();
    void resize(int size);

    //Operators
    Elements& operator= (const Elements& drob);
    Element& operator[](int index)
    {
	return m_data[index];
    }

	//Lconum
	std::vector<Element>		algorithm_knapsack(int Length);
	double				algorithm_knapsack_ReturnMaxValue(int length);
	std::vector<ElementsList>	algorithm_greedy(int length);
	double				algorithm_greedy_ReturnMaxValue(int length);

	std::vector<ElementsList>	knapsack_intermediate(int length);
	std::vector<ElementsList>	knapsack_forIntermediate_Greedy(std::vector<Element>& temporaryData, int& length);
	std::vector<ElementsList>	knapsack_forIntermediate_DynamicProgramming(const std::vector<Element>& temporaryData, int& length);

	std::vector<ElementsList>	knapasck_LimitElement(int length);

private:
	////If the length is a multiple of the element with the priority coefficient					
	//We delete large elements
	void	excludeLongElement(std::vector<Element> &temporaryData, int lenght);	
	// We delete repetitions by length
	void	deleteRepetitionsԼenght(std::vector<Element>& temporaryData);			
	// We find the greatest value
	double  returnGreatCost(std::vector<Element>& temporaryData);				
	// If the largest element in size does not have the greatest value, then that element is meaningless
	void	deleteMaxLengthMiniNotMaxElements(std::vector<Element>& temporaryData, double maxValue);														
	// determine the priority coefficients  
	void decidePreferenceCoefficients();	
	// Return the largest length starting from the second element
	ushint returnMaxLengthFromSecondElement(std::vector<Element>& temporaryData);
	bool isMemberDataNumberEmpty();
};

std::vector<int>			giveLinesLengths(std::string filename);
