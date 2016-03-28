#include <Element.h>

Element::Element(unsigned int symbol)
: symbol_(symbol)
{

}

Element::~Element(){

}

void Element::setOrder(unsigned int o){
	order_ = o;
}

unsigned int Element::getOrder(){
	return order_;
}
unsigned int Element::getSymbol(){
	return symbol_;
}

void Element::setIsGenerator(bool b){
	isGenerator_ = b;
}

bool Element::isGenerator(){
	return isGenerator_;
}