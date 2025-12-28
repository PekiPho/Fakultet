#include <iostream>
#include "Paragraf.h"
#include "Tekst.h"
using namespace std;

void main() {
	char niz[] = "Test 1";
	char niz2[] = "test 2";
	char niz3[] = "TEST 3";
	Paragraf* p = new Paragraf(niz, false);
	Paragraf* p1 = new Paragraf(niz2, true);
	Paragraf* p2 = new Paragraf(niz3, true);


	Tekst* tekst = new Tekst(2);
	tekst->Dodaj(p);
	tekst->Dodaj(p1);
	tekst->Dodaj(p2);

	tekst->Stampa();
	//p->Modifikuje();

}