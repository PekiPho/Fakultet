#pragma once
#include "Figura.h"

class Kvadrat:public Figura
{
private:
	float a;
public:
	Kvadrat() {
		this->a = 0;
	}
	Kvadrat(float a) :Figura(a, a) {}
	void Upis(float a,float b);
	void Cita();
	float Povrsina();
	float Obim();
};

