#pragma once
#include <stdio.h>
#include <iostream>
using namespace std;

//forward declaration -15 minuta
class Node;
class Edge;

class Node
{
public:
	int node;
	Edge* adj;
	Node* next;
	int status;


	void Visit() {
		cout << node << endl;
	}

	Node() {
		this->next = NULL;
		this->adj = NULL;
		this->status = 0;
	}

	Node(int nodeA) {
		this->node = nodeA;
		this->adj = NULL;
		this->next = NULL;
		this->status = 0;
	}

	Node(int nodeA, Edge* adjA, Node* nextA, int statusA) {
		this->node = nodeA;
		this->adj = adjA;
		this->next = nextA;
		this->status = statusA;
	}

	
};



class Edge {
public:
	Node* src;
	Node* dest;
	Edge* link;
	int weight;
	bool mandatory;



	Edge() {
		this->src = NULL;
		this->dest = NULL;
		this->link = NULL;
	}

	Edge(Node* destA, Edge* linkA,int weightA,Node* srcA,bool mand) {
		this->dest = destA;
		this->link = linkA;
		this->weight = weightA;
		this->src = srcA;
		this->mandatory = mand;
	}

	
	

	
};

class Compare {
public:
	bool operator()(Edge* prvi, Edge* drugi) {
		return prvi->weight > drugi->weight;
	}
};


