#include <iostream>
#include <string>
#include "F16.h"
#include "Rakieta.h"
#include <Windows.h>
using namespace std;





int main()
{
	F16 samolot; //Tworze obiekt klasy F16 - wywolanie konstruktora F16()
	samolot.set();
	samolot.add_rocket(); //Dodaje rakiete w funkcji add_rocket() wywolany jest konstruktor dla nowo utworzonego obiektu
	samolot.display();
	
	cout << "Nie wysypalo" << endl;
	

	system("pause");
	return 0;
}