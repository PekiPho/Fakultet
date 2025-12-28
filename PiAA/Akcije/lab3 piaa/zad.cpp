#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <queue>
using namespace std;

struct akcija {
	int cena;
	int brAkcija;
};

bool operator<(const akcija& a,const akcija& b) {
	return a.cena > b.cena;
}

void main() {

	priority_queue<akcija> pq;

	int cena[] = { 10,7,19 };
	int k = 45;

	/*int cena[] = { 7,10,4 };
	int k = 100;*/

	
	int n = sizeof(cena) / sizeof(*cena);
	akcija* a = new akcija[n];
	for (int i = 0; i < n; i++) {
		a[i].cena = cena[i];
		a[i].brAkcija = i+1;
		pq.push(a[i]);
	}

	int pom2;
	int suma = 0;
	akcija b;
	int temp = k;
	while (!pq.empty()) {
		b = pq.top();
		if (b.brAkcija * b.cena < temp) {
			temp -= b.brAkcija * b.cena;
			suma += b.brAkcija;
		}
		else {
			pom2 = temp / b.cena;
			temp -= b.cena * pom2;
			suma += pom2;
			break;
		}
		pq.pop();
	}

	cout << suma << endl;
 
}