#include "FileSystemElement.h"
#include "File.h"
#include "Folder.h"
using namespace std;

void main()
{
    Folder* root = new Folder("glavni");
    Folder* documents = new Folder("Documents", root);
    Folder* pictures = new Folder("Pictures", documents);
    File* file1 = new File("Document1", "txt", documents);
    File* file2 = new File("Image1", "jpg", pictures);
    File* file3 = new File("Image2", "png", pictures);

    documents->dodajPodelement(file1);
    pictures->dodajPodelement(file2);
    pictures->dodajPodelement(file3);

    cout << "print za Root folder:" << endl;
    root->PrintList();

    cout << "\nprint za Documents folder:" << endl;
    documents->PrintList();

    cout << "\nprint za Pictures folder:" << endl;
    pictures->PrintList();

    cout << "\nprint za Document1 fajl:" << endl;
    file1->PrintList();

    cout << "\nprint za Image1 fajl:" << endl;
    file2->PrintList();

    delete root;
    delete documents;
    delete pictures;
    delete file1;
    delete file2;
    delete file3;
}