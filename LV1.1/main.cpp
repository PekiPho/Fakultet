#include "minesweeper.h"


void main()
{
	/*minesweeper a(2,6);
	cin >> a;
	int x1, x2;
	cin >> x1;
	cin >> x2;
	if (a.broji(x1,x2) == -1)
	{
		cout << a;
	}
	else {
		cout << a.broji(x1,x2);
	}*/

	minesweeper* b = new minesweeper(6,2);
	cin >> *b;
	b->izbacuje();
	cout << *b;
	
	
	
}