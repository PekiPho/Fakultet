#include "Paragraf.h"

Paragraf::Paragraf(char n[], bool t) {
	int i = 0;
	while (n[i] != '\0')
	{
		this->niz[i] = n[i];
		i++;
	}
	this->niz[i] = '\0';
	this->tip = t;
}

Paragraf::~Paragraf() {
	delete[] niz;
}

void Paragraf::Modifikuje() {
	int i = 0,j=0;
	char temp[100];
	if (tip)
	{
		while (niz[i] != '\0')
		{
			if (niz[i] > 'a' && niz[i] < 'z')
				temp[i] = niz[i] - 'a' + 'A';
			else if (niz[i] > 'A' && niz[i] < 'Z')
				temp[i] = niz[i] + 'a' - 'A';
			else temp[i] = niz[i];
			i++;
		}
		temp[i] = '\0';
	}
	else {
		while (niz[i] != '\0')
		{
			i++;
		}
		while (i > 0) {
			temp[j++] = niz[i-1];
			i--;
		}
		temp[j] = '\0';
	}

	cout << temp << endl;
	//delete[] temp;
}

void Paragraf::Stampa()
{
	cout << niz << endl;
}