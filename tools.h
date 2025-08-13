#include <iostream>
#include <stdlib.h>
#include <limits>
#include <ctime>
#include <windows.h>
using namespace std;

void setcolor(int color)
{	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int chose()
{
	int Choice;	
	do
	{	
	   cin>>Choice;
		if (cin.fail())
		{
			setcolor(4);
			cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "\t\t\t   ! Invalid input... !\n";
		}
		else if (Choice < 1 || Choice> 12)
		{
			setcolor(4);
			cout << "\t\t\t! THE CHOSE NUMBER IS ARROR !\n";
			cin.clear();
		}
	} while (Choice< 1 || Choice > 12);
	return Choice;
}
short chose2()
{
	int Choice = 0;
	do
	{
		cin >> Choice;
		if (cin.fail())
		{
			setcolor(4);
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\t\t\t   ! Invalid input... !\n";
		}
		else if (Choice < 0 || Choice > 6)
		{
			setcolor(4);
			cout << "\t\t\t! THE CHOSE NUMBER IS ARROR !\n";
		}
	} while (Choice < 1 || Choice > 6);
	return Choice;
}
int chose3()
{
	int Choice = 0;
	do
	{
		cin >> Choice;
		if (cin.fail())
		{
			setcolor(4);
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\t\t\t   ! ID NUMBER IS ERROR ... !\n";
		}
		else if (Choice < 0 || Choice > 999999)
		{
			setcolor(4);
			cout << "\t\t\t! THE ID NUMBER IS ARROR !\n";
		}
	} while (Choice < 0 || Choice > 999999);
	setcolor(3);
	return Choice;
}
