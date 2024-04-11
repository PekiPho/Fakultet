#pragma once
#include <string.h>

class Monitor
{
private:
	float dijagonala;
	char* rezolucija;
	char* marka;
public:
	Monitor(float dijagonala,const char* rezolucija,const char* marka) {
		this->dijagonala = dijagonala;
		this->marka = new char[strlen(marka) + 1];
		strcpy(this->marka, marka);
		this->rezolucija = new char[strlen(rezolucija) + 1];
		strcpy(this->rezolucija, rezolucija);
	}
	~Monitor() {
		delete rezolucija;
		delete marka;
	}
};

