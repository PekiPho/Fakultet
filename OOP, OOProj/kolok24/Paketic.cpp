#include "Paketic.h"

Paketic Paketic::operator+(const Paketic& obj) {
	Paketic* res = new Paketic();
	res->brPoklona = this->brPoklona + obj.brPoklona;
	res->niz = new Poklon * [res->brPoklona];
	res->trenutni = 0;
	int i = 0;
	while (i < this->trenutni)
	{
		res->niz[res->trenutni++] = this->niz[i++];
	}
	i = 0;
	while (i < obj.trenutni)
	{
		res->niz[res->trenutni++] = obj.niz[i++];
	}
	return *res;
}