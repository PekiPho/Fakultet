#pragma once
#include "Poklon.h"
class Igracka:public Poklon
{
private:
	char tip[20]; // 0-plisana, 1-plasticna, 2-gumena
public:
	//Igracka();
	Igracka(double c, int brm,const char t[]) :Poklon(c, brm) {
		int i = 0;
		while (t[i] != '\0')
		{
			tip[i] = t[i];
			i++;
		}
		tip[i] = '\0';
	}
	void print() {
		cout << this->cena << " " << this->brMasnica << " " << this->tip << endl;
	}
};

