#pragma once
#include "Poklon.h"
#include "Cokolada.h"
#include "Igracka.h"
using namespace std;

class Paketic
{
private:
	Poklon** niz;
	int brPoklona;
	int trenutni;
public:
	Paketic() {

	}

	Paketic(int brp) {
		niz = new Poklon * [brp];
		this->brPoklona = brp;
		this->trenutni = 0;
	}

	int BrojPoklona() {
		return this->brPoklona;
	}

	void Add(Poklon* p)
	{
		niz[trenutni++] = p;
	}

	void print() {
		for (int i = 0; i < trenutni; i++)
		{
			niz[i]->print();
		}
	}

	Paketic operator+(const Paketic& obj);
};

