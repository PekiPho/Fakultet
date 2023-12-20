#include "FileSystemElement.h"
#include "File.h"
#include "Folder.h"

void main()
{
    Folder* root = new Folder("Root");
    Folder* documents = new Folder("Documents", root);
    Folder* pictures = new Folder("Pictures", documents);
    File* file1 = new File("Document1", "txt", documents);
    File* file2 = new File("Image1", "jpg", pictures);
    File* file3 = new File("Image2", "png", pictures);

    // Dodavanje fajlova u odgovarajuće foldere
    documents->dodajPodelement(file1);
    pictures->dodajPodelement(file2);
    pictures->dodajPodelement(file3);

    // Testiranje PrintList metoda
    std::cout << "Printanje liste za Root folder:" << std::endl;
    root->PrintList();

    std::cout << "\nPrintanje liste za Documents folder:" << std::endl;
    documents->PrintList();

    std::cout << "\nPrintanje liste za Pictures folder:" << std::endl;
    pictures->PrintList();

    std::cout << "\nPrintanje liste za Document1 fajl:" << std::endl;
    file1->PrintList();

    std::cout << "\nPrintanje liste za Image1 fajl:" << std::endl;
    file2->PrintList();

    // Oslobađanje alocirane memorije
    delete root;
    delete documents;
    delete pictures;
    delete file1;
    delete file2;
    delete file3;
}