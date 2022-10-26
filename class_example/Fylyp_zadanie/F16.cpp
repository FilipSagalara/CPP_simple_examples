#include "F16.h"
#include "Rakieta.h"


F16::F16() :pilot{"Andrzej","Kowalski","oficer"},masa_samolotu(50.0),masa_ekwipunku(50.0)
{
	std::cout << "UWAGA WYWOLUJE KONSTRUKTOR DLA F16" << std::endl;


}


F16::~F16()
{
	std::cout << "UWAGA WYWOLUJE DESTRUKTOR DLA F16" << std::endl;
}

void F16::set()
{
	std::cout << "Podaj imie pilota" << std::endl;
	std::cin >> pilot.imie;
	std::cout << "Podaj nazwisko pilota" << std::endl;
	std::cin >> pilot.nazwisko;
	std::cout << "Jaki stopien" << std::endl;
	std::cin >> pilot.stopien;
	std::cout << "Podaj mase samolotu" << std::endl;
	std::cin >> masa_samolotu;
	std::cout << "Podaj mase ekwipunku" << std::endl;
	std::cin >> masa_ekwipunku;

}
void F16::display()
{
	std::cout << pilot.imie << std::endl;
	std::cout << pilot.nazwisko << std::endl;
	std::cout << pilot.stopien << std::endl;
	std::cout << masa_samolotu << std::endl;
	std::cout << masa_ekwipunku << std::endl;	
	if (rakiety.empty()==true)
	{
		std::cout << "Brak informacji o rakiecie" << std::endl;
	}
	else
	{
		int count = 1;
		for (auto it =rakiety.begin(); it !=rakiety.end(); it++)
		{
			std::cout << "Rakieta: " << count << std::endl;
			it->display();
			count++;
		}
	}


}
bool F16::check(double arg)
{
	
	double masa_calkowita = masa_ekwipunku + masa_samolotu;
	double masa_rakiet = 0;
	for (auto it =rakiety.begin(); it !=rakiety.end(); it++)
	{
		masa_rakiet+=it->rocket_mass();
	}
	masa_calkowita += masa_rakiet;
	if (arg>=masa_calkowita)
	{
		return true;
	}
	if (arg<masa_calkowita)
	{
		return false;
	}


}
void F16::add_rocket()
{
	Rakieta nowa;
	nowa.set();
	rakiety.push_back(nowa);
	


}
