#pragma once
#include <iostream>
#include <list>
#include <Windows.h>
class Rakieta
{
public:
	Rakieta();
	~Rakieta();
	void display();
	void set();
	double rocket_mass();
private:

	double masa_rakiety;
};

