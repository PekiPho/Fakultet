#include "Kolekcija.h"

Kolekcija::Kolekcija(int max) {
	this->maxBr = max;
	niz = new Figura*[max];
	trenutni = 0;
}

Kolekcija::~Kolekcija() {
	delete[] niz;
	this->maxBr = 0;
}

void Kolekcija::Dodaj(Figura* f) {
	if (trenutni == maxBr)
	{
		maxBr = maxBr * 2;
		Figura** temp = new Figura * [maxBr];
		for (int i = 0; i < trenutni; i++) {
			temp[i] = niz[i];
		}
		niz = temp;
	}
		
	niz[trenutni++] = f;
}

void Kolekcija::Povrsina() {
	for (int i = 0; i < trenutni; i++)
	{
		float pov = niz[i]->Povrsina();
		cout << pov << endl;
	}
}

void Kolekcija::Obim() {
	for (int i = 0; i < trenutni; i++)
	{
		float ob = niz[i]->Obim();
		cout << ob << endl;
	}
}

void Kolekcija::Sortira() {
	for (int i = 0; i < trenutni - 1; i++)
	{
		for (int j = i + 1; j < trenutni; j++)
		{
			if (niz[i]->Obim() > niz[j]->Povrsina())
			{
				Figura* temp = niz[i];
				niz[i] = niz[j];
				niz[j] = temp;
			}
		}
	}
}