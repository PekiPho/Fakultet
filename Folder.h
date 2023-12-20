#pragma once
#include "FileSystemElement.h"

class Folder : public FileSystemElement {
private:
    static const int maxel = 2018;
    FileSystemElement* podelementi[maxel];
    int brojElemenata;

public:
    Folder(const char* ime, FileSystemElement* roditelj = nullptr)
        : FileSystemElement(ime, "") {
        for (int i = 0; i < maxel; i++) {
            podelementi[i] = nullptr;
        }
        brojElemenata = 0;
        setRoditeljskiElement(roditelj);
    }

    void dodajPodelement(FileSystemElement* element) {
        if (brojElemenata < maxel) {
            podelementi[brojElemenata++] = element;
            element->setRoditeljskiElement(this);
        }
        else {
            cout << "folder pun" << endl;
        }
    }

    void ukloniPodelement(int indeks) {
        if (indeks >= 0 && indeks < brojElemenata) {
            podelementi[indeks]->setRoditeljskiElement(nullptr);
            for (int i = indeks; i < brojElemenata - 1; i++) {
                podelementi[i] = podelementi[i + 1];
            }
            podelementi[brojElemenata - 1] = nullptr;
            brojElemenata--;
        }
        else {
            cout << "los index" << endl;
        }
    }
    virtual const char* getPunoKvalifikovanoIme() const override {
        string punoIme = "";
        const FileSystemElement* trenutni = this;
        while (trenutni != nullptr) {
            punoIme = string(trenutni->getIme()) + "/" + punoIme;
            trenutni = trenutni->getRoditeljskiElement();
        }
        char* rezultat = new char[punoIme.length() + 1];
        strcpy(rezultat, punoIme.c_str());
        return rezultat;
    }

    virtual void PrintList() const override {
        for (int i = 0; i < brojElemenata; i++) {
            cout << podelementi[i]->getPunoKvalifikovanoIme() << endl;
        }
    }
};

