#include "Pravougaonik.h"

void Pravougaonik::Cita() {
	cout << this->x << " " << this->y << endl;
}

void Pravougaonik::Upis(float x, float y) {
	this->x = x;
	this->y = y;
}

float Pravougaonik::Povrsina() {
	return this->x * this->y;
}

float Pravougaonik::Obim() {
	return 2 * (this->x + this->y);
}