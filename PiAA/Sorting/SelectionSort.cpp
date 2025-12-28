#include <stdio.h>
#include <math.h>
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

int* SelectionSort(int *niz, int length) {

	int temp;
	int min;
	for (int i = 0; i < length - 1; i++) {
		min = i;

		for (int j = i + 1; j < length; j++) {
			if (niz[min] > niz[j])
				min = j;
		}

		temp = niz[i];
		niz[i] = niz[min];
		niz[min] = temp;

	}

	return niz;
}

void main() {


	srand((unsigned int)time(NULL));

	//100
	/*int* niz = new int[100];
	int length = 100;
	for (int i = 0; i < 100; i++) {
		
		niz[i] = rand() % 10000;
	}*/

	//1000
	/*int* niz = new int[1000];
	int length = 1000;
	for (int i = 0; i < 1000; i++) {

		niz[i] = rand() % 10000;
	}*/

	//10000
	/*int* niz = new int[10000];
	int length = 10000;
	for (int i = 0; i < 10000; i++) {

		niz[i] = rand() % 10000;
	}*/
	
	//100000
	/*int* niz = new int[100000];
	int length = 100000;
	for (int i = 0; i < 100000; i++) {

		niz[i] = rand() % 10000;
	}*/
	
	//1000000
	int* niz = new int[1000000];
	int length = 1000000;
	for (int i = 0; i < 1000000; i++) {

		niz[i] = rand() % 10000;
	}
	
	//10000000
	/*int* niz = new int[10000000];
	int length = 10000000;
	for (int i = 0; i < 10000000; i++) {

		niz[i] = rand() % 10000;
	}*/



	/*for (int i = 0; i < length; i++) {
		cout << niz[i] << endl;
	}*/
	

	auto start = high_resolution_clock::now();

	
	niz= SelectionSort(niz,length);

	auto end = high_resolution_clock::now();
	auto time = duration_cast<microseconds>(end - start);

	/*for (int i = 0; i < length; i++) {
		cout << niz[i] << endl;
	}*/

	cout <<endl <<  time.count() << endl;
}