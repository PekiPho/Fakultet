#include "Racunar.h"

Racunar::Racunar(bool radi,const char* MACadr,Tastatura* t,Monitor* m) {
	this->radi = radi;
	this->MACadr = new char[strlen(MACadr) + 1];
	strcpy(this->MACadr, MACadr);
	this->tast = t;
	this->monitor = m;
	procesor = nullptr;
	ssd = nullptr;
	hdd = nullptr;
	ram = nullptr;
}

Racunar::~Racunar() {
	delete MACadr;
}

void Racunar::dodajProcesor(Procesor* p) {
	if (procesor == nullptr) {
		procesor = new Procesor*[4];
	}
	int i = 0;
	while (procesor[i] != nullptr)
		i++;
	procesor[i] = p;
}

void Racunar::dodajHDD(HDD* h) {
	if (hdd == nullptr)
		hdd = new HDD * [6];
	int i = 0;
	while (hdd[i] != nullptr)
		i++;
	hdd[i] = h;
}

void Racunar::dodajRAM(RAM* r) {
	if (ram == nullptr)
		ram = new RAM * [8];
	int i = 0;
	while (ram[i] != nullptr)
		i++;
	ram[i] = r;
}
void Racunar::dodajSSD(SSD* s) {
	if (ssd == nullptr)
		ssd = new SSD * [6];
	int i = 0;
	while (ssd[i] != nullptr)
		i++;
	ssd[i] = s;
}

bool Racunar::DalRadi() {
	return radi;
}

char* Racunar::getMAC() {
	return MACadr;
}


// this-> = new char[strlen() + 1];