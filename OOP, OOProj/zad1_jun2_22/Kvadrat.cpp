#include "Kvadrat.h"
#include <iostream>

void Kvadrat::Cita() {
	cout << this->x << " " << this->y << endl;
}

void Kvadrat::Upis(float a,float b) {
	this->x = a;
	this->y = a;
}

float Kvadrat::Povrsina() {
	return this->x * this->y;
}

float Kvadrat::Obim() {
	return 4 * this->x;
}
