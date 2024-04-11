#include "Tastatura.h"


Tastatura::Tastatura(const char* tip,const char* port) {
	this->tip = new char[strlen(tip) + 1];
	strcpy(this->tip, tip);
	this->port = new char[strlen(port) + 1];
	strcpy(this->port, port);
}

Tastatura::~Tastatura() {
	delete tip;
	delete port;
}