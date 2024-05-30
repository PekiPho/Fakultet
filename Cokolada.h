#pragma once
#include "Poklon.h"
class Cokolada:public Poklon
{
private:
	int kakao;
public:
	//Cokolada();
	Cokolada(double c, int brm, int k) :Poklon(c, brm) {
		this->kakao = k;
	}
	void print() {
		cout << this->cena << " " << this->brMasnica << " " << this->kakao << endl;
	}
};

