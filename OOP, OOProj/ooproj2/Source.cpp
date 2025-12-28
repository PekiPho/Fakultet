#include <iostream>
#include "Fakultet.h"
#include "Ucionica.h"
#include "Racunar.h"
#include "Procesor.h"
#include "Tastatura.h"
#include "Monitor.h"

using namespace std;

void main() {
	Fakultet* f = Fakultet::GetInstanca();

	f->PostaviParametre("Elfak");

	Ucionica* uc1 = new Ucionica("Uc1");
	Ucionica* uc2 = new Ucionica("Uc2");

	Racunar* r1 = new Racunar(true, "1", new Tastatura("bezicna", "usb"), new Monitor(23.6,"1080p","ASUS"));
	Racunar* r2 = new Racunar(true, "2", new Tastatura("zicna", "ps2"), new Monitor(30., "2k", "Samsung"));
	Racunar* r3 = new Racunar(false, "3", new Tastatura("bezicna", "usb"), new Monitor(27., "1080p", "ASUS"));
	Racunar* r4 = new Racunar(true, "4", new Tastatura("zicna", "usb"), new Monitor(23.6, "720p", "Acer"));

	uc1->dodajRacunar(r1);
	uc1->dodajRacunar(r2);
	
	uc2->dodajRacunar(r3);
	uc2->dodajRacunar(r4);

	f->dodajUcionicu(uc1);
	f->dodajUcionicu(uc2);

	r1->dodajHDD(new HDD(20));
	r1->dodajHDD(new HDD(40));

	cout << uc1->ukupanBroj() << " " << uc1->brojNeispravnih() << endl;
	cout << uc2->ukupanBroj() << " " << uc2->brojNeispravnih() << endl;

	f->izvestajRacunar();
	f->izvestajUcionica();
}