#pragma once
#include "FileSystemElement.h"

class File : public FileSystemElement {
public:
    File(const char* ime, const char* ekstenzija, FileSystemElement* roditelj = nullptr)
        : FileSystemElement(ime, ekstenzija) {
        setRoditeljskiElement(roditelj);
    }

    virtual const char* getPunoKvalifikovanoIme() const override {
        std::string punoIme = "";
        const FileSystemElement* trenutni = getRoditeljskiElement();

        if (trenutni != nullptr) {
            punoIme += trenutni->getPunoKvalifikovanoIme();
        }

        
        punoIme += getIme();
        punoIme += ".";
        punoIme += getEkstenzija();

        char* rezultat = new char[punoIme.length() + 1];
        strcpy(rezultat, punoIme.c_str());
        return rezultat;
    }

    virtual void PrintList() const override {
        FileSystemElement* roditelj = getRoditeljskiElement();
        if (roditelj != nullptr) {
            roditelj->PrintList(); 
        }
        else {
            std::cout << "File '" << getIme() << "' nema roditelja" << std::endl;
        }
    }
};

