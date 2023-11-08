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

//int minesweeper::broji(int x, int y)
//{
//	int z = 0;
//	if (a[x][y] != 0)
//		return -1;
//	else {
//		int index = x - 1;
//		for (int k = -1; k < 2; k++)
//		{
//			if (index > -1 && (y + k) > -1 && index < n && (y + k) < m)
//			{
//				if (a[index][y + k] != 0)
//				{
//					if (index % n > 0 && ((y + k) % m) > 0)
//					{
//						z++;
//					}
//					if (index == 0 && ((y + k) % m) > 0)
//						z++;
//						if ((y + k) == 0 && index % n > 0)
//							z++;
//						if ((y + k) == 0 && index == 0)
//							z++;
//				}
//			}
//			
//
//		}
//		index = x;
//		for (int k = -1; k < 2; k += 2)
//		{
//			if (index > -1 && (y + k) > -1 && index < n && (y + k) < m)
//			{
//				if (a[index][y + k] != 0)
//				{
//					if (index % n > 0 && ((y + k) % m) > 0)
//					{
//						z++;
//					}
//					if (index == 0 && ((y + k) % m) > 0)
//						z++;
//					if ((y + k) == 0 && index % n > 0)
//						z++;
//					if ((y + k) == 0 && index == 0)
//						z++;
//				}
//			}
//			
//		}
//		index = x + 1;
//		for (int k = -1; k < 2; k++)
//		{
//			if (index > -1 && (y + k) > -1 && index < n && (y+k) <m)
//			{
//				if (a[index][y + k] != 0)
//				{
//					if (index % n > 0 && ((y + k) % m) > 0)
//					{
//						z++;
//					}
//					if (index == 0 && ((y + k) % m) > 0)
//						z++;
//					if ((y + k) == 0 && index % n > 0)
//						z++;
//					if ((y + k) == 0 && index == 0)
//						z++;
//				}
//			}
//		}
//		return z;
//	}
//}
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