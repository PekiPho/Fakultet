#pragma once
#include <iostream>
#include <string.h>
using namespace std;

class FileSystemElement
{
	protected:
		char* ime;
		char* ekstenzija;
		FileSystemElement* roditeljskiEl;

	public:
		FileSystemElement(const char* ime, const char* ekstenzija);
		virtual ~FileSystemElement();
		void setRoditeljskiElement(FileSystemElement* roditelj) {
			roditeljskiEl = roditelj;
		}
		virtual const char* getPunoKvalifikovanoIme() const = 0;
		virtual void PrintList() const = 0;

		const char* getIme() const {
			return ime;
		}

		FileSystemElement* getRoditeljskiElement() const {
			return roditeljskiEl;
		}

		const char* getEkstenzija() const {
			return ekstenzija;
		}
};

