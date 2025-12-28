#include <stdio.h>
#include "Node.h"
#include "Graf.h"
#include <chrono>


using namespace std;
using namespace std::chrono;


void main() {
	srand((unsigned int)time(NULL));

	//Test slika
	/*Graf* g = new Graf();
	g->insertNode(1);
	g->insertNode(2);
	g->insertNode(3);
	g->insertNode(4);
	g->insertNode(5);
	g->insertNode(6);

	g->insertEdge(1, 5, 6,true);
	g->insertEdge(1, 2, 5,false);
	g->insertEdge(1, 6, 7,false);
	g->insertEdge(2, 6, 4,false);
	g->insertEdge(3, 4, 3, false);
	g->insertEdge(3, 5, 6, false);
	g->insertEdge(4, 5, 4, false);
	g->insertEdge(5, 6, 5, false);
	g->insertEdge(4, 6, 8, false);
	g->insertEdge(1, 3, 3, false);*/
	
	//
	///*if (g->isCyclic())
	//	cout << "Ima ciklus" << endl;
	//else cout << "Nema ciklus" << endl;*/

	//Graf* p = g->Kruskal();

	//p->print();

	int N = 1000;
	int k = 50 * N;
	int obavezan =ceil(k / 100);

	bool tmp = true;
	int pom;
	Graf* g = new Graf();
	

	for (int i = 1; i <= N; i++) {
		g->insertNode(i);
	}

	//dodajemo obavezne
	int br = 0;
	Edge* grana;
	while (br < obavezan) {

		int a = ((rand() % k) + 1) % (N + 1);
		int b = ((rand() % (33 * k)) + 1) % (N + 1);
		grana = g->findEdge(a, b);
		if (grana == NULL) {
			g->insertEdge(a, b, rand() % N + 1, true);
			if (!g->isCyclic())
				br++;
			else {
				g->deleteEdge(a, b);
				g->deleteEdge(b, a);
			}
		}
	}

	//bira cvor koji ce biti povezan sa svakim drugim cvorom
	//for (int i = 1; i <= N; i++) {
	//	if (i == N && tmp) {
	//		pom = N;
	//	}
	//	if (rand() % N <10) {
	//		pom = i;
	//		break;
	//	}
	//}
	//
	////povezuje jedan cvor sa svim ostalim
	//for (int i = 1; i <= N; i++) {
	//	if (i != pom) {
	//		if(g->findEdge(i,pom)==NULL)
	//			g->insertEdge(i, pom, rand() % N + 1, false);
	//	}
	//}

	//Daisy chain
	for (int i = 2; i <= N; i++) {
		if(g->findEdge(i-1,i)==NULL)
			g->insertEdge(i - 1, i, rand() % N + 1, false);
	}
	if(g->findEdge(1,N)==NULL)
		g->insertEdge(1, N, rand() % N + 1, false);


	

	//Generise k grana
	while (br < k) {
		//nasumican prvi cvor npr
		int a = ((rand() % k)+1) % (N+1);
		

		int b = ((rand() % (33 * k))+1) % (N+1);

		//cout << a << " " << b << endl << endl;

		if (g->findEdge(a, b)==NULL) {
			g->insertEdge(a, b, rand() % N +1 , false);
			br++;
		}
	}


	//g->print();

	Graf* f = g->Kruskal();

	//f->printBrojGrana();
	//f->print();
	//if (f->isCyclic())
	//	cout << "Ima ciklus" << endl;
	//else cout << "Nema ciklus" << endl;
	//cout << rand() % N << endl;

}

