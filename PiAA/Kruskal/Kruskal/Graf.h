#pragma once
#include <iostream>
#include "Node.h"
#include <queue>
#include <chrono>

using namespace std;
using namespace std::chrono;


class Graf
{
protected:
	Node* start;
	int brojCvorova;
	int brojGrana;

public:
	Graf() {
		start = NULL;
		brojCvorova = 0;
		brojGrana = 0;
	}

	void print() {
		Node* ptr = start;

		while (ptr != NULL) {
			cout << ptr->node << " -> ";
			Edge* pom = ptr->adj;

			while (pom != NULL) {
				cout << pom->dest->node << " | ";
				pom = pom->link;
			}
			cout << "\r\n";
			ptr = ptr->next;
		}

		cout << endl << this->brojGrana << endl;
	}

	Node* findNode(int pod) {
		
		Node* ptr = start;

		while (ptr != NULL && ptr->node != pod)
			ptr = ptr->next;

		return ptr;
	}

	Edge* findEdge(int a, int b) {

		Node* ptr1 = findNode(a);
		Node* ptr2 = findNode(b);

		if (ptr1 == NULL || ptr2 == NULL)
			return NULL;

		Edge* pom = ptr1->adj;
		while (pom != NULL && pom->dest != ptr2)
			pom = pom->link;

		return pom;
	}

	bool insertNode(int pod) {
		Node* novi = new Node(pod, NULL, this->start, 0);

		if (novi == NULL)
			return false;
		this->start = novi;
		this->brojCvorova++;

		return true;
	}

	bool insertEdge(int a, int b,int w,bool mandatory) {

		Node* ptr1 = findNode(a);
		Node* ptr2 = findNode(b);

		if (ptr1 == NULL || ptr2 == NULL)
			return NULL;

		Edge* pom = new Edge(ptr2, ptr1->adj, w,ptr1,mandatory);
		if (pom == NULL)
			return false;
		ptr1->adj = pom;

		pom = new Edge(ptr1, ptr2->adj, w,ptr2,mandatory);
		if (pom == NULL)
			return false;
		ptr2->adj = pom;

		this->brojGrana += 2;
		return true;
	}

	bool insertEdge2(int a, int b, int w, bool mandatory) {

		Node* ptr1 = findNode(a);
		Node* ptr2 = findNode(b);

		if (ptr1 == NULL || ptr2 == NULL)
			return NULL;

		Edge* pom = new Edge(ptr2, ptr1->adj, w, ptr1, mandatory);
		if (pom == NULL)
			return false;
		ptr1->adj = pom;
		this->brojGrana++;
		return true;
	}

	bool deleteEdge(int a,int b) {

		Edge* pom = findEdge(a, b);//V+E

		if (pom == NULL)
			return false;


		Node* ptr1 = findNode(a); //V

		if (pom == ptr1->adj) {
			ptr1->adj = pom->link;
			delete pom;
			this->brojGrana--;
			return true;
		}
		Edge* pom2 = ptr1->adj;


		//moram da testiram jos tmrw
		while (pom2->link != pom)
			pom2 = pom2->link;
		pom2 = pom->link;
		delete pom;
		this->brojGrana--;
		return true;
	}

	bool isCyclic() {

		setStatus(0);

		Node* ptr = this->start;

		while (ptr != NULL) {
			if (ptr->status == 0) {
				if (isCyclicPom(ptr,NULL))
					return true;
			}
			ptr = ptr->next;
		}
		return false;
	}

	bool isCyclicPom(Node* ptr, Node* roditelj) {

		ptr->status = 3;
		Edge* pom = ptr->adj;
		queue<Edge*> listaCvorova;

		while (pom != NULL) {
			listaCvorova.push(pom);
			pom = pom->link;
		}

		while (!listaCvorova.empty()) {
			pom = listaCvorova.front();
			listaCvorova.pop();

			if (pom->dest->status == 0) {
				if (isCyclicPom(pom->dest, ptr))
					return true;
			}
			else if (pom->dest != roditelj)
				return true;
			
		}
		return false;
	}

	void setStatus(int a) {
		Node* pom = this->start;

		while (pom != NULL) {
			pom->status = a;
			pom = pom->next;
		}
	}

	bool areAllVisited() {
		Node* ptr = this->start;

		while (ptr != NULL) {

			if (ptr->status != 0) {
				return false;
			}

			ptr = ptr->next;
		}

		return true;
	}

	void changeState(Edge* grana) {

		grana->mandatory = true;
	}

	void printBrojGrana() {
		cout << this->brojGrana << endl;
	}

	Graf* Kruskal() {
		Graf* novi = new Graf();

		priority_queue<Edge*,vector<Edge*>,Compare> pq;
		priority_queue<Edge*, vector<Edge*>, Compare> pqMandatory;

		Node* ptr = this->start;
		Edge* pom;


		//dodajemo cvorove i ubacujemo grane u obavezan min heap i ne obavezan min heap
		while (ptr != NULL) {
			novi->insertNode(ptr->node);
			pom= ptr->adj;

			while (pom != NULL) {
				if (!pom->mandatory)
					pq.push(pom);
				else
					pqMandatory.push(pom);

				pom = pom->link;
			}

			ptr = ptr->next;
		}


		//ubacujemo prvo sve mandatory grane u novi graf
		while (!pqMandatory.empty()) {
			pom = pqMandatory.top();
			pqMandatory.pop();

			novi->insertEdge2(pom->src->node, pom->dest->node, pom->weight, pom->mandatory);

		}


		//zatim ubacujemo najmanje grane koje nisu obavezne, ali ako dolazi do ciklusa ne ubacujemo ih
		while (!pq.empty() && novi->brojGrana!=2*(novi->brojCvorova-1)) { //E
			pom = pq.top();
			pq.pop(); //logE

			//cout << pom->weight << endl;
			if(!novi->findEdge(pom->src->node,pom->dest->node)) //E
				novi->insertEdge(pom->src->node, pom->dest->node, pom->weight,pom->mandatory);//V
			if (novi->isCyclic())//V+E
			{
				novi->deleteEdge(pom->src->node, pom->dest->node);//E
				novi->deleteEdge(pom->dest->node, pom->src->node);//E
			}
			//cout << novi->brojGrana << endl;
		}

		return novi;
	}

};



