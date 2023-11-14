#include "minesweeper.h"
#include <iostream>

minesweeper::minesweeper()
{
	n = m = 10;
	a = new int* [n];

	for (int i = 0; i < n; i++)
		a[i] = new int[m];
}
minesweeper::minesweeper(int brVr, int brKol)
	:n(brVr),m(brKol)
{
	a = new int* [n];

	for (int i = 0; i < n; i++)
		a[i] = new int[m];
}

minesweeper::~minesweeper()
{
	if (a != 0)
	{
		for (int i = 0; i < n; i++)
			delete[] a[i];
		delete[] a;
	}
}

minesweeper::minesweeper(const minesweeper& v)
{
	this->n = v.n;
	this->m = v.m;
	this->a = new int* [v.n];

	for (int i = 0; i < v.n; i++)
	{
		this->a[i] = new int[v.m];
	}
	for (int i = 0; i < v.n; i++)
	{
		for (int j = 0; j < v.m; j++)
		{
			this->a[i][j] = v.a[i][j];
		}
	}
}


void minesweeper::izbacuje()
{
	//b[k]=i-k;
	int z,k=0,p=0;
	int b[15];

	//redovi
	for (int i = 0; i < n; i++)
	{
		z = 0;
		for (int j = 0; j < m; j++)
		{
			if (a[i][j] != 0)
				z = 1;
		}
		if (z == 0)
		{
			b[k] = i - k;
			k++;
		}
	}
	
	while (p < k)
	{
		for (int i = b[p]; i < n-1; i++)
		{
			for (int j = 0; j < m; j++)
			{
				a[i][j] = a[i + 1][j];
			}
		}
		p++;
		this->n=n--;
	}
	//radi fala bogu 4 ujutro je
		/*1 0
		1 1
		1 0
		0 0
		0 1
		0 0*/


	//kolone
	int g = 0;
	for (int i = 0; i < m; i++)
	{
		z = 0;
		for (int j = 0; j < n; j++)
		{
			if (a[j][i] != 0)
				z = 1;
		}
		if (z == 0)
		{
			b[g] = i - g;
			g++;
		}
	}
	p = 0;
	while (p < g)
	{
		for (int i = b[p]; i < m-1; i++)
		{
			for (int j = 0; j < n; j++)
			{
				a[j][i] = a[j][i+1];
			}
		}
		p++;
		this->m = m--;
	}
	//radi i za kolone
	/*0 0 0 0 1 1
	0 0 1 1 1 1*/
}


int minesweeper::broji(int x, int y)
{
	int z = 0;
	if (a[x][y] != 0)
		return -1;
	else {
		int index = x - 1;
		for (int k = -1; k < 2; k++)
		{
			if (index > -1 && (y + k) > -1 && index < n && (y + k) < m)
			{
				if (a[index][y + k] != 0)
				{
					z++;
				}
			}
			

		}
		index = x;
		for (int k = -1; k < 2; k += 2)
		{
			if (index > -1 && (y + k) > -1 && index < n && (y + k) < m)
			{
				if (a[index][y + k] != 0)
				{
					z++;
				}
			}
			
		}
		index = x + 1;
		for (int k = -1; k < 2; k++)
		{
			if (index > -1 && (y + k) > -1 && index < n && (y+k) <m)
			{
				if (a[index][y + k] != 0)
				{
					z++;
				}
			}
		}
		return z;
	}
}

void minesweeper::desno()
{
	for (int i = 0;i<n; i++)
	{
		int temp = a[i][m - 1];
		for (int j = m - 1; j > 0; j--)
		{
			a[i][j] = a[i][j - 1];
		}
		a[i][0] = temp;
	}
}

void minesweeper::levo()
{
	for (int i = 0; i < n; i++)
	{
		int temp = a[i][0];
		for (int j = 0; j < m; j++)
		{
			a[i][j] = a[i][j + 1];
		}
		a[i][m-1] = temp;
	}
}

void minesweeper::gore()
{
	for (int i = 0; i < m; i++)
	{
		int temp = a[0][i];
		for (int j = 0; j < n-1; j++)
		{
			a[j][i] = a[j+1][i];
		}
		a[n-1][i] = temp;
	}
}

void minesweeper::dole()
{
	for (int i = m-1; i >= 0; i--)
	{
		int temp = a[n-1][i];
		for (int j = n-1; j > 0; j--)
		{
			a[j][i] = a[j - 1][i];
		}
		a[0][i] = temp;
	}
}

void minesweeper::menja(int z)
{
	int temp = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (a[i][j] == 0)
			{
				if (temp % z == 0)
				{
					a[i][j] = 1;
				}
				temp++;
			}
		}
	}
}

//1 1 0 1 0
//0 0 0 0 0
//1 1 1 0 0
//0 0 0 0 0
//1 1 0 1 1

istream& operator>>(istream& ulaz, minesweeper& v)
{
	for (int i = 0; i < v.n; i++)
	{
		for (int j = 0; j < v.m; j++)
		{
			ulaz >> v.a[i][j];
			if (v.a[i][j] == 0)
				v.a[i][j] = false;
			else v.a[i][j] = true;
		}
	}
	return ulaz;
}

ostream& operator<<(ostream& izlaz, minesweeper& v)
{
	for (int i = 0; i < v.n; i++)
	{
		for (int j = 0; j < v.m; j++)
			izlaz << v.a[i][j] << " ";
		izlaz << endl;
	}
	return izlaz;
}