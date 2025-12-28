#pragma once
#include "Racunar.h"

class Ucionica
{
private:
	char* oznaka;
	int brojTrenutnih;
	Racunar** rac;
public:
	Ucionica(const char* oznaka);
	void dodajRacunar(Racunar* r);
	int brojNeispravnih();
	int ukupanBroj();
};

