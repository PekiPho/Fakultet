#pragma once
#include <iostream>
using namespace std;
class Poklon
{
protected:
	float cena;
	int brMasnica;
public:
	//Poklon();
	Poklon(double c, int brm) {
		this->cena = c;
		this->brMasnica = brm;
	}
	virtual void print() {};
};

