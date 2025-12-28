#pragma once
#include "Paragraf.h"
#include <iostream>
using namespace std;

class Tekst
{
private:
	Paragraf** t;
	int maxBr;
	int trenutni;
public:
	Tekst(int max);
	void Dodaj(Paragraf* p);
	void Stampa();
};

