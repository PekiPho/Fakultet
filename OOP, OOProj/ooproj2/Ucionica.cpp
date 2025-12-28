#include "Ucionica.h"

Ucionica::Ucionica(const char* oznaka) {
	this->oznaka = new char[strlen(oznaka) + 1];
	strcpy(this->oznaka, oznaka);
	this->rac = nullptr;
	this->brojTrenutnih = 0;
}

void Ucionica::dodajRacunar(Racunar* r) {
	if (rac == nullptr)
		rac = new Racunar * [20];
	rac[brojTrenutnih++] = r;
}

int Ucionica::brojNeispravnih() {

	int temp = 0;

	for (int i = 0; i < brojTrenutnih; i++)
	{
		if (!(rac[i]->DalRadi()))
			temp++;
	}
	return temp;
}

int Ucionica::ukupanBroj() {
	return brojTrenutnih;
}
