#pragma once


class Element{

private:
	unsigned int order_ = 0;		// the order of the element (smallest k such that e^k = 1 mod p in the group Z_p*) 
	unsigned int symbol_ = 0;		// the symbol of the element (typically a number)
	bool isGenerator_ = false;		// is the element a generator in the given group?

public:
	Element(unsigned int symbol);
	~Element();

	void setOrder(unsigned int o);
	void setIsGenerator(bool b);
	
	bool isGenerator();
	unsigned int getOrder();
	unsigned int getSymbol();


};