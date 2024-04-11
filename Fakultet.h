#pragma once
#include <iostream>
#include "Ucionica.h"

using namespace std;

class Fakultet
{
private:
	char* ime;
	static Fakultet* instanca;
	static int brojUc;
	Ucionica** ucionice;
	Fakultet();

public:
	static Fakultet* GetInstanca();
	void PostaviParametre(const char* naziv);
	void dodajUcionicu(Ucionica* u);
	void izvestajRacunar();
	void izvestajUcionica();
};

