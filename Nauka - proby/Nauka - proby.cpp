// Nauka - proby.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include "Plik.h"

int main()
{
	try
	{
		Plik baza("dane.dat", 'r');
		baza.print();
		Plik wart("dane2.dat", 'r');
		wart.print();
		Plik wynik("wynik.dat", 'w');

		//wynik.add(baza,wart);
		wynik.dif(baza, wart);
		wynik.print();
		/*std::fstream plik("dane.dat",std::ios::in | std::ios::out);
		Plik wynik("wynik.dat", 'w');
		Plik wynik2(plik,'r');
		wynik = wynik2;*/

	}
	catch (const std::exception &ex)
	{
		std::cout << "\nException occured: " << ex.what() << "\n";
		exit(1);
	}

	return 0;
}