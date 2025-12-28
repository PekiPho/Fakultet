#include "FileSystemElement.h"
#include <string.h>

FileSystemElement::~FileSystemElement() {
	delete[] ime;
	delete[] ekstenzija;
}

FileSystemElement::FileSystemElement(const char* ime, const char* ekstenzija) {

    this->ime = new char[strlen(ime) + 1];
    strcpy(this->ime, ime);
    this->ekstenzija = new char[strlen(ekstenzija) + 1];
    strcpy(this->ekstenzija, ekstenzija);
    roditeljskiEl = nullptr;
}
