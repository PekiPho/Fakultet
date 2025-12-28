#include <stdio.h>
#include <iostream>
#include <chrono>
#include <math.h>

using namespace std;
using namespace std::chrono;

//int Parent(int i) {
//	return floor((i-1) / 2);
//}

int Left(int i) {
	return i * 2+1;
}

int Right(int i) {
	return i * 2 + 2;
}

void Heapify(int* niz, int i, int length) {
	int l = Left(i);
	int r = Right(i);

	int najveci;

	if (l < length && niz[l] > niz[i])
		najveci = l;
	else najveci = i;

	if (r < length && niz[r] > niz[najveci])
		najveci = r;
	if (najveci != i)
	{
		int temp = niz[i];
		niz[i] = niz[najveci];
		niz[najveci] = temp;

		Heapify(niz, najveci, length);
	}
}

void BuildHeap(int* niz,int length) {

	for (int i = floor(length)/2 - 1; i>=0; i--)
		Heapify(niz, i, length);
}

int* HeapSort(int* niz, int length) {

	BuildHeap(niz, length);

	for (int i = length-1; i >= 1; i--) {

		int temp = niz[0];
		niz[0] = niz[i];
		niz[i] = temp;

		length--;
		Heapify(niz,0,length);
	}

	return niz;
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
//	niz = HeapSort(niz, length);
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