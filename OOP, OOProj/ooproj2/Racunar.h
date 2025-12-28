#pragma once
#include "Tastatura.h"
#include "Monitor.h"
#include "Procesor.h"
#include "RAM.h"
#include "HDD.h"
#include "SSD.h"

class Racunar
{
private:
	bool radi;
	char* MACadr;
	Tastatura* tast;
	Monitor* monitor;
	RAM** ram;
	HDD** hdd;
	SSD** ssd;
	Procesor** procesor;
public:
	Racunar(bool radi,const char* MACadr,Tastatura* t, Monitor* m);
	~Racunar();
	void dodajProcesor(Procesor* p);
	void dodajRAM(RAM* r);
	void dodajSSD(SSD* s);
	void dodajHDD(HDD* h);
	bool DalRadi();
	char* getMAC();
};

