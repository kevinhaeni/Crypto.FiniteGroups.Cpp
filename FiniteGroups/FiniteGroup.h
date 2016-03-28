#pragma once

#include <vector>
#include <Element.h>

class FiniteGroup{
public:
	enum Operator { ADDITION = 0, MULTIPLICATION, EXPONENTIATION };

private:
	unsigned int modulo_;
	unsigned int order_;
	Operator operator_;
	std::vector<Element> elements_;	
	unsigned int inverse_;

	void calculateElementOrder();

public:
	FiniteGroup(unsigned int order, Operator op);
	FiniteGroup(std::vector<unsigned int> elements, unsigned int modulo, Operator op);
	~FiniteGroup();

	// group methods
	FiniteGroup::Operator getOperator();
	unsigned int getOrder();
	unsigned int getModulo();
	
	// element methods
	Element getElement(int i);
	unsigned int getInverseElement();
	std::vector<Element> getElements();

};