#pragma once


class Element{
public:

private:
	
	unsigned int order_ = 0;
	unsigned int symbol_ = 0;
	bool isGenerator_ = false;

public:
	Element(unsigned int symbol);
	~Element();

	void setOrder(unsigned int o);
	void setIsGenerator(bool b);
	
	bool isGenerator();
	unsigned int getOrder();
	unsigned int getSymbol();


};