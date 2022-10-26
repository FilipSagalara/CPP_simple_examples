#pragma once
#include <iostream>
#include <string>
#include <list>
#include "Rakieta.h"
#include<vector>
#include <Windows.h>
struct Pilot
{
	std::string imie, nazwisko, stopien;

};

class F16
{

public:
	F16();
	~F16();

	void set();
	void display();
	bool check(double arg);
	void add_rocket();


private:
	Pilot pilot;
	double masa_samolotu, masa_ekwipunku;
	std::list<Rakieta>rakiety;
	

};

