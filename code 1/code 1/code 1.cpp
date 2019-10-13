#include "Header.h"
#include <vector>
#include <time.h>

struct axes
{
	int x;
	int y;
};
typedef struct axes Axes;

bool operator == (Axes& a, Axes& b)
{
	if (a.x == b.x && a.y == b.y)
	{
		return true;
	}
	else return false;
}

int Random_Number(int a, int b)
{
	srand(time(NULL));
	int t = a + rand() % (b + 1 - a);
	return t;
}

void Set_Up(vector<Axes> map)
{
	for (int a = map[0].x - 1; a <= 51; a++)
	{
		gotoxy(a, map[0].y - 1);
		cout << "x";
		gotoxy(a, 21);
		cout << "x";
	}
	for (int b = map[0].y - 1; b <= 21; b++)
	{
		gotoxy(map[0].x - 1, b);
		cout << "x";
		gotoxy(51, b);
		cout << "x";
	}
}

bool OnePlace(int xf, int yf, vector<Axes> map, int e)
{
	int OP = 0;
	for (int i = 0; i <= e; i++)
	{
		if (xf == map[i].x && yf == map[i].y)
		{
			OP++;
			break;
		}
	}
	if (OP != 0) return true; else return false;
}

void Food(vector<Axes> &map, int &food, int &xf, int &yf, int &t, int &xe, int &ye, int &e, int &boost, int &xb, int &yb)
{
	if (food == 0)
	{
		do 
		{
			xf = Random_Number(3, 50), yf = Random_Number(2, 20);
		} while (OnePlace(xf, yf, map, e));
		gotoxy(xf, yf);
		cout << '+';
		food++;
	}
	else if (map[0].x == xf && map[0].y == yf)
	{
		food--;
		t++;
	}

	if (e > 0 && e % 12 == 0 && boost == 0)
	{
		do
		{
			xb = Random_Number(4, 49), yb = Random_Number(3, 19);
		} while (OnePlace(xb, yb, map, e));
		gotoxy(xb, yb);
		cout << '#';
		boost++;
	}
	else if (map[0].x == xb && map[0].y == yb)
	{
		boost--;
		t = t + 5;
		xb = 0; yb = 0;
	}
	
	if (t > 0)
	{
		map.push_back({1,1});
		t--;
		e++;
	}
	else
	{
		xe = map[e].x; ye = map[e].y;
	}
	for (int i = e; i > 0; i--)
	{
		map[i] = map[i - 1];
	}
}

void Return(int &x, int &y)
{
	if (x < 3) x += 48;
	if (x > 50) x -= 48;
	if (y < 2) y += 19;
	if (y > 20) y -= 19;
}

float Speed_Level(int e)
{
	float a = 50;
	a -= ((float)e / 1.75);
	return a;
}

void Losing_Condition(vector<Axes> map, int e, int &condition)
{
	for (int i = 1; i < e; i++)
	{
		if (map[0] == map[i + 1]) condition++;
	}
}

void Controll(vector<Axes> &map, int &check)
{
	int xe = map[0].x, ye = map[0].y, food = 0, xf, yf, t = 0, e = 0, condition = 0, boost = 0, xb, yb, s = 50;
	while (condition < 1)
	{
		gotoxy(map[0].x, map[0].y);
		if (check == 0) { cout << "<"; map[0].x--;}
		if (check == 1) { cout << "^"; map[0].y--;}
		if (check == 2) { cout << ">"; map[0].x++;}
		if (check == 3) { cout << "v"; map[0].y++;}
		while (_kbhit())
		{
			char a = _getch();
			if (check != 2) { if (a == 'a') check = 0; }
			if (check != 3) { if (a == 'w') check = 1; }
			if (check != 0) { if (a == 'd') check = 2; }
			if (check != 1) { if (a == 's') check = 3; }
		}
		Sleep(Speed_Level(e));
		gotoxy(xe, ye); cout << " ";
		Return(map[0].x, map[0].y);
		Food(map, food, xf, yf, t, xe, ye, e, boost, xb, yb);
		Losing_Condition(map, e, condition);
		gotoxy(3, 23); cout << "Score: " << e << "\t\t\t   Speed x " << 50/Speed_Level(e);
	}
}

int main()
{	
	vector<Axes> map = { {3,2} };; gotoxy(map[0].x, map[0].y);
	int check = 4;
	Set_Up(map);
	Controll(map, check);

	_getch();
	return 0;
}