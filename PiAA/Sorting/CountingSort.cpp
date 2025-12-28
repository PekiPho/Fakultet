#include <stdio.h>
#include <iostream>
#include <chrono>
#include <math.h>

using namespace std;
using namespace std::chrono;


int* CountingSort(int* niz, int length,int opseg) {

	int* noviNiz = new int[length];
	int* pomocniNiz = new int[opseg];

	for (int i = 0; i <= opseg; i++) {
		pomocniNiz[i] = 0;
	}
	for (int i = 0; i < length; i++) {
		pomocniNiz[niz[i]]++;
	}

	for (int i = 1; i <=opseg; i++) {
		pomocniNiz[i] += pomocniNiz[i - 1];
	}

	for (int i = length-1; i >=0; i--) {
		noviNiz[pomocniNiz[niz[i]]-1] = niz[i];
		pomocniNiz[niz[i]]--;
	}
	
	return noviNiz;
}


//void main() {
//
//
//	srand((unsigned int)time(NULL));
//
//	//100
//	/*int* niz = new int[100];
//	int length = 100;
//	for (int i = 0; i < 100; i++) {
//
//		niz[i] = rand() % 10000;
//	}*/
//
//	//1000
//	/*int* niz = new int[1000];
//	int length = 1000;
//	for (int i = 0; i < 1000; i++) {
//
//		niz[i] = rand() % 10000;
//	}*/
//
//	//10000
//	/*int* niz = new int[10000];
//	int length = 10000;
//	for (int i = 0; i < 10000; i++) {
//
//		niz[i] = rand() % 10000;
//	}*/
//
//	//100000
//	/*int* niz = new int[100000];
//	int length = 100000;
//	for (int i = 0; i < 100000; i++) {
//
//		niz[i] = rand() % 10000;
//	}*/
//
//	//1000000
//	/*int* niz = new int[1000000];
//	int length = 1000000;
//	for (int i = 0; i < 1000000; i++) {
//
//		niz[i] = rand() % 10000;
//	}*/
//
//	//10000000
//	int* niz = new int[10000000];
//	int length = 10000000;
//	for (int i = 0; i < 10000000; i++) {
//
//		niz[i] = rand() % 10000;
//	}
//
//
//
//	/*for (int i = 0; i < length; i++) {
//		cout << niz[i] << endl;
//	}*/
//
//	//cout << endl << endl;
//	auto start = high_resolution_clock::now();
//
//
//	niz = CountingSort(niz, length,10000);
//
//	auto end = high_resolution_clock::now();
//	auto time = duration_cast<microseconds>(end - start);
//
//	/*for (int i = 0; i < length; i++) {
//		cout << niz[i] << endl;
//	}*/
//
//	cout << endl << time.count() << endl;
//}