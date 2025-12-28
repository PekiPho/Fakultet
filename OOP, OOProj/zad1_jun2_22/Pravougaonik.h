#pragma once
#include "Figura.h"

class Pravougaonik:public Figura
{
private:
	float a;
	float b;
public:
	Pravougaonik() {
		this->a = 0;
		this->b = 0;
	}
	Pravougaonik(float a, float b) :Figura(a, b) {}

	void Upis(float x,float y);
	void Cita();

	float Povrsina();
	float Obim();
};

