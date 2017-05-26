#pragma once
#ifndef PLIK_H
#define PLIK_H

#include <fstream>

class Plik
{
	std::fstream plik;
	int len;
	char m;
	std::string name;
	Plik(std::fstream&, char direc = 'f');
	Plik();
	void odejmij(Plik&, Plik&);
public:
	Plik(const std::string&, const char&);
	~Plik();
	Plik& operator=(Plik&);
	Plik& operator=(std::fstream&);
	Plik& operator!();
	//Plik& operator*(const int&);
	void print();
	char getC(const int&);
	void putC(const char&, const int&);
	void add(Plik&, Plik&);
	void multiply(Plik&, Plik&);
	void dif(Plik&, Plik&);
	void divide(Plik&, Plik&);
};

#endif // !PLIK_H


