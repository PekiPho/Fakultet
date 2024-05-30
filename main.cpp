#include "Figura.h"
#include "Kolekcija.h"
#include "Kvadrat.h"
#include "Pravougaonik.h"

void main() {
	Kolekcija* k;
	k = new Kolekcija(3);

	k->Dodaj(new Pravougaonik(3, 4));
	k->Dodaj(new Kvadrat(4));
	k->Dodaj(new Pravougaonik(5, 4));
	k->Dodaj(new Kvadrat(5));

	k->Obim();
	cout << endl;
	k->Povrsina();
	cout << endl;
	k->Sortira();
}