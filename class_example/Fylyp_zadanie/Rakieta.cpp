#include "Rakieta.h"



Rakieta::Rakieta():masa_rakiety(50.0)
{
	std::cout << "UWAGA WYWOLUJE KONSTRUKTOR DLA RAKIETY" << std::endl;
	
}


Rakieta::~Rakieta()
{
	std::cout << "UWAGA WYWOLUJE DESTRUKTOR DLA RAKIETY" << std::endl;
	
}

void Rakieta::display()
{
	std::cout << masa_rakiety << std::endl;


}
void Rakieta::set()
{
	std::cout << "Podaj mase rakiety" << std::endl;
	std::cin >> masa_rakiety;
}
double Rakieta::rocket_mass()
{
	return masa_rakiety;
}
