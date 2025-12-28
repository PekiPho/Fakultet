#pragma once
#include <iostream>
using namespace std;

class minesweeper
{
private:
	int** a;
	int n;
	int m;

public:

	minesweeper();
	minesweeper(int brVr, int brKol);
	virtual ~minesweeper();

	minesweeper(const minesweeper& v);

	//druga
	void desno();
	void levo();
	void gore();
	void dole();
	void menja(int z);

	void izbacuje();
	int broji(int x, int y);

	inline int Duzina() { return n; }
	inline int Sirina() { return m; }

	friend istream& operator>>(istream& ulaz, minesweeper& v);
	friend ostream& operator<<(ostream& ulaz, minesweeper& v);
};

