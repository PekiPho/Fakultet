#include "Tekst.h"

Tekst::Tekst(int max) {
	this->maxBr = max;
	this->trenutni = 0;
	t = new Paragraf * [this->maxBr];
}

void Tekst::Dodaj(Paragraf* p) {
	if (trenutni == maxBr)
	{
		maxBr = maxBr * 2;
		Paragraf** temp = new Paragraf * [maxBr];
		for (int i = 0; i < trenutni; i++)
		{
			temp[i] = t[i];
		}
		t = temp;
	}

	t[trenutni++] = p;
}

void Tekst::Stampa() {
	for (int i = 0; i < trenutni; i++)
	{
		t[i]->Stampa();
	}
}
