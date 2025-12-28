#pragma once
#include <iostream>
using namespace std;

class Paragraf
{
private:
	bool tip;
	char niz[100];
public:
	Paragraf(char n[], bool t);
	~Paragraf();
	void Modifikuje();
	void Stampa();
};

