#include "FiniteGroup.h"
#include <math.h>
#include <MathUtils.h>

/*
	Default ctor to construct a finite group when a modulo is given
*/
FiniteGroup::FiniteGroup(unsigned int modulo, Operator op)
	: operator_(op), modulo_(modulo)
{
	switch (op)
	{
	case Operator::ADDITION:
		inverse_ = 0;									// Inverse = 0
		order_ = modulo;								// Get the order of the additive finite group		
		
		// get the elements of the group
		for (unsigned int i = 0; i < modulo; i++)
			elements_.push_back(Element(i));

		break;
	case Operator::EXPONENTIATION : case Operator::MULTIPLICATION:
		inverse_ = 1;
		order_ = MathUtils::phi(modulo);				// the order of a multiplicative group equals the eulers totient function

		// get the elements of the group (rel. prime numbers)
		for (unsigned int i = 1; i < modulo; i++){
			if (MathUtils::gcd(i, modulo) == 1){				
				elements_.push_back(Element(i));
			}
		}
		break;
	default:
		throw std::logic_error("Unknown operator!");
	}
	
	// set the order of every element
	calculateElementOrder();	
}


/*
	Alternative ctor which takes a list of elements as an argument; is used to construct subgroups
*/
FiniteGroup::FiniteGroup(std::vector<unsigned int> elements, unsigned int modulo, Operator op)
	: operator_(op), modulo_(modulo)
{

	switch (op)
	{
	case Operator::ADDITION:
		inverse_ = 0;									// Inverse = 0	
		break;
	case Operator::EXPONENTIATION: case Operator::MULTIPLICATION:
		inverse_ = 1;
	
		break;
	default:
		throw std::logic_error("Unknown operator!");
	}

	if (elements.size() <= 0)
		throw std::logic_error("Empty set");
	else
		order_ = elements.size();

	for (unsigned int i : elements)	
		elements_.push_back(Element(i));
	
	calculateElementOrder();
}


/*
  Calculate the element order of every element of the group
*/
void FiniteGroup::calculateElementOrder(){
	for (std::vector<Element>::iterator it = elements_.begin(); it != elements_.end(); ++it)
	{
		Element & el= *it;

		for (unsigned int exp = 1; exp <= modulo_; exp++){
			if (MathUtils::modpow(el.getSymbol(), exp, modulo_) == 1){
				el.setOrder(exp);
				break;
			}
		}				
		
		el.setIsGenerator(el.getOrder() == this->getOrder());	// check if element is a generator of G
	}
}

FiniteGroup::~FiniteGroup(){

}

unsigned int FiniteGroup::getOrder(){
	return order_;
}

FiniteGroup::Operator FiniteGroup::getOperator(){
	return operator_;
}

unsigned int FiniteGroup::getModulo(){
	return modulo_;
}


std::vector<Element> FiniteGroup::getElements(){
	return elements_;
}

Element FiniteGroup::getElement(int i){
	if (elements_.size() <= i)
		throw std::logic_error("GetElement Index out of range!");

	return elements_[i];
}

unsigned int FiniteGroup::getInverseElement(){
	return inverse_;
}