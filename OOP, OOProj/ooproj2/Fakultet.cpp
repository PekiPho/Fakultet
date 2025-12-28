#include "Fakultet.h"
#include <string.h>

Fakultet* Fakultet::instanca;
int Fakultet::brojUc = 0;

Fakultet::Fakultet()
{
}

Fakultet* Fakultet::GetInstanca()
{
	if (instanca == nullptr)
		instanca = new Fakultet();

	return instanca;
}

void Fakultet::PostaviParametre(const char* naziv) {
	this->ime = new char[strlen(naziv) + 1];
	strcpy(this->ime, naziv);
}

void Fakultet::dodajUcionicu(Ucionica* u) {
	if (ucionice == nullptr) {
		ucionice = new Ucionica * [20];
	}
	/*while (ucionice[i] != nullptr)
		i++;*/
	ucionice[brojUc++] = u;
}
void Fakultet::izvestajUcionica() {
	int i = 0;
	while (i<brojUc)
	{
		int a = ucionice[i++]->brojNeispravnih();
		cout << a << endl;
	}
}

void Fakultet::izvestajRacunar() {
	int i = 0;
	while (i<brojUc)
	{
		int a = ucionice[i++]->ukupanBroj();
		cout << a << endl;
	}
}