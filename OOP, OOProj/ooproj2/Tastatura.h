#pragma once
#include <string.h>

class Tastatura
{
private:
	char* tip;
	char* port;
public:
	Tastatura(const char* tip,const char* port);
	~Tastatura();
};

