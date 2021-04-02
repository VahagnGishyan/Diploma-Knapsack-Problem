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
	void sortn2();
	void swapElement(Element& object1, Element& object2);

	void	sortByLenght(std::vector<Element>& temporaryData);				// Սորթավորել ըստ երկարության
	void	sortByPriorityCoefficient(std::vector<Element>& temporaryData);	// Սորթավորել ըստ նախընտրելիության գործակիցի

public:
	//Դեֆոլտ պետք ա գործակիցը և ամեն ինչը լինի բացասական եթե չի արժեքավորվել
	Elements(std::string filename);

	//For Work
	void print();
	void print(std::vector<Element> printData);

	//Operators
	Elements& operator= (const Elements& drob);

	//Lconum
	std::vector<Element>		algorithm_knapsack(int Length);
	double						algorithm_knapsack_ReturnMaxValue(int length);
	std::vector<ElementsList>	algorithm_greedy(int length);
	double						algorithm_greedy_ReturnMaxValue(int length);

	std::vector<ElementsList>	knapsack_intermediate(int length);
	std::vector<ElementsList>	knapsack_forIntermediate_Greedy(std::vector<Element>& temporaryData, int& length);
	std::vector<ElementsList>	knapsack_forIntermediate_DynamicProgramming(const std::vector<Element>& temporaryData, int& length);
	std::vector<ElementsList>	knapsack_forIntermediate_DynamicProgrammingForTest(std::vector<Element>& temporaryData, int& length);

	std::vector<ElementsList>	knapasck_onlyOneElement(int length);

private:
	////If the length is a multiple of the element with the highest coefficient					
	// Ջնջում ենք մեծ տարրերը
	void	excludeLongElement(std::vector<Element> &temporaryData, int lenght);	
	// Ջնջում ենք կրկնությունները ըստ երկարությունների
	void	deleteRepetitionsԼenght(std::vector<Element>& temporaryData);			
	// Գտնում ենք մեծագույն արժեքը
	double  returnGreatCost(std::vector<Element>& temporaryData);				
	// Եթե չափերով ամենամեծ տարրը ամենամեծ ինքարժեքը չունի, ապա էդ տարրը անիմաստ ա
	void	deleteMaxLengthMiniNotMaxElements(std::vector<Element>& temporaryData, double maxValue);														
	// որոշել նախընտրելիության գործակիցները
	void decidePreferenceCoefficients();	
	// Վերադարձնել մեծագույն երկարությունը սկսած երկրորդն տարրից
	ushint returnMaxLengthFromSecondElement(std::vector<Element>& temporaryData);
			
	//fortest
	//void randomElementsNumber();
	void twoElementsNumber();


	//int							maxCoefficientElementIsCorrect(int length);
	////correct the elements
	//std::vector<Element>		correct_elementlengthIsGreaterLength();
	//std::vector<Element>		correct_elementLengtheSame();
	//std::vector<Element>		correct_elementIsNotPreferable();
};

std::vector<int>			giveLinesLengths(std::string filename);

//class ElementsList
//{
//	std::vector<ElementsAndCount> m_data;
//
//
//
//};