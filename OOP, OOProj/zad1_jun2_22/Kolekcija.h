#pragma once
#include "Figura.h"
#include "Kvadrat.h"
#include "Pravougaonik.h"

class Kolekcija
{
private:
	Figura** niz;
	int maxBr;
	int trenutni;

public:
	Kolekcija();
	Kolekcija(int max);
	~Kolekcija();
	void Dodaj(Figura* f);
	void Povrsina();
	void Obim();
	void Sortira();
};

