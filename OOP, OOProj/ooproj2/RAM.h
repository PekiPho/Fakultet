#pragma once
#include <string.h>
class RAM
{
private:
	int takt;
	int kolicina;
	char* tip;
public:
	RAM(int takt, int kolicina, char* tip) {
		this->kolicina = kolicina;
		this->takt = takt;
		this->tip = new char[strlen(tip) + 1];
		this->tip = tip;
	}
	~RAM() {
		delete tip;
	}
};

