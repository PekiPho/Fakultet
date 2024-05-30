#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class Poklon
{
protected:
	double cena;
	int brMasnica;
public:
	//Poklon();
	Poklon(double c, int brm) {
		this->cena = c;
		this->brMasnica = brm;
	}
	virtual void print() {};
	virtual void Upis(ofstream& of) {};
};

