#include "stdafx.h"

#include <fstream>
#include <iostream>
#include "Plik.h"


Plik::Plik(std::fstream &wart, char direc)
	:m('t')
{
	plik.open("temp.dat", std::ios::in | std::ios::out | std::ios::trunc);
	if (!plik)
		throw std::runtime_error("Cannot create temp file");
	char a;
	if (direc == 'f')
	{
		wart.seekg(0, std::ios::beg);
		while (wart.get(a))
		{
			std::cout << a;
			plik.put(a);
			++len;
		}
	}
	else
	{
		wart.seekg(-1, std::ios::end);
		while (wart.tellg() >= 0)
		{
			wart.get(a);
			std::cout << a;
			plik.put(a);
			++len;
			wart.seekg(-2, std::ios::cur);
		}
	}
	wart.clear();
	std::cout << "\n";
}

Plik::Plik()
	:len(0),m('t')
{
	plik.open("temp.dat", std::ios::in | std::ios::out | std::ios::trunc);
}

void Plik::odejmij(Plik &baza, Plik &wart)
{
	char b, w, r(0);
	int ans;
	baza.plik.seekg(-1, std::ios::end);
	wart.plik.seekg(-1, std::ios::end);
	plik.seekp(0, std::ios::beg);
	for (int i = 0;i < wart.len;++i)
	{
		baza.plik.get(b);
		wart.plik.get(w);
		ans = b - w - r;
		if (ans < 0)
		{
			r = 1;
			ans += 10;
		}
		else
			r = 0;
		plik.put(static_cast<char>(ans + 48));
		++len;
		wart.plik.seekg(-2, std::ios::cur);
		baza.plik.seekg(-2, std::ios::cur);
	}
	for (int i = wart.len;i < baza.len;++i)
	{
		baza.plik.get(b);
		ans = b -48 - r;
		if (ans < 0)
		{
			r = 1;
			ans += 10;
		}
		else
			r = 0;
		plik.put(static_cast<char>(ans + 48));
		++len;
		baza.plik.seekg(-2, std::ios::cur);
	}
	!*this;
}

Plik::Plik(const std::string &name_, const char &mode)
	:len(0), m(mode), name(name_)
{
	if (m != 'r' && m != 'w')
		throw std::runtime_error("File can only be in read/write mode!");
	if (m == 'r')
		plik.open(name, std::ios::in);
	else
		plik.open(name, std::ios::in | std::ios::out | std::ios::trunc);
	if (!plik)
		throw std::runtime_error("Cannot open this file");
	if (m == 'r')
	{
		char a;
		while (plik.get(a))
		{
			++len;
			if (a < 48 || a>57)
				break;
		}
		plik.clear();
		plik.seekg(0, std::ios::cur);
	}
}

Plik::~Plik() 
{ 
	plik.close(); 
	if (m == 't')
		std::remove("temp.dat");
}

Plik& Plik::operator=(Plik &wart)
{
	plik.seekp(0, std::ios::beg);
	wart.plik.seekg(0, std::ios::beg);
	for (int i = 0;i < wart.len;++i)
	{
		char a;
		wart.plik.get(a);
		std::cout << a << " ";
		plik.put(a);
		++len;
	}
	std::cout << "\n";
	return *this;
}

Plik& Plik::operator=(std::fstream &wart)
{
	char a;
	while (wart.get(a))
		plik.put(a);
	wart.clear();
	return *this;
}

Plik& Plik::operator!()
{
	int end = len / 2;
	char a,a2;
	for (int i = 0;i < end;++i)
	{
		plik.seekg(i, std::ios::beg);
		plik.get(a);
		plik.seekg(-i-1, std::ios::end);
		plik.get(a2);
		plik.seekp(-1, std::ios::cur);
		plik.put(a);
		plik.seekp(i, std::ios::beg);
		plik.put(a2);
	}
	return *this;
}

void Plik::print()
{
	plik.seekg(0, std::ios::beg);
	for (int i = 0;i < len;++i)
	{
		char a;
		plik.get(a);
		std::cout << a << " ";
	}
	std::cout << "\n";
}

char Plik::getC(const int &index)
{
	char a;
	plik.seekg(plik.tellg(), std::ios::cur);
	plik.seekg(index, std::ios::beg);
	plik.get(a);
	return a;
}

void Plik::putC(const char&a, const int&index)
{
	plik.seekg(plik.tellg(), std::ios::cur);
	plik.seekp(index, std::ios::beg);
	plik.put(a);
}

void Plik::add(Plik &baza, Plik &wart)
{
	plik.seekp(0, std::ios::beg);
	baza.plik.seekg(-1, std::ios::end);
	wart.plik.seekg(-1, std::ios::end);
	int end = (baza.len < wart.len) ? baza.len : wart.len;
	char x1, x2;
	int t(0), sum;
	for (int i = 0;i < end;++i)
	{
		baza.plik.get(x1);
		wart.plik.get(x2);
		sum = t + x1 + x2 - 96;
		if (sum >= 10)
		{
			sum -= 10;
			t = 1;
		}
		else
			t = 0;
		++len;
		//std::cout << sum << " ";
		plik.put(static_cast<char>(sum + 48));
		baza.plik.seekg(-2, std::ios::cur);
		wart.plik.seekg(-2, std::ios::cur);
	}
	if (baza.len > wart.len)
	{
		for (int i = end;i < baza.len;++i)
		{
			baza.plik.get(x1);
			sum = t + x1 - 48;
			if (sum >= 10)
			{
				sum -= 10;
				t = 1;
			}
			else
				t = 0;
			++len;
			//std::cout << sum << " ";
			plik.put(static_cast<char>(sum + 48));
			baza.plik.seekg(-2, std::ios::cur);
		}
	}
	else if (wart.len > baza.len)
	{
		for (int i = end;i < wart.len;++i)
		{
			wart.plik.get(x1);
			sum = t + x1 - 48;
			if (sum >= 10)
			{
				sum -= 10;
				t = 1;
			}
			else
				t = 0;
			++len;
			//std::cout << sum << " ";
			plik.put(static_cast<char>(sum + 48));
			wart.plik.seekg(-2, std::ios::cur);
		}
	}
	if (t)
	{
		plik.put(static_cast<char>(49));
		++len;
	}
	!*this;
}

void Plik::multiply(Plik &baza, Plik &wart)
{
	wart.plik.seekg(-1, std::ios::end);
	char w, b, temp;
	int x, y, ans, r;
	for (int i = 0;i < wart.len;++i)
	{
		plik.seekp(i, std::ios::beg);
		wart.plik.get(w);
		x = w - 48;
		r = 0;
		baza.plik.clear();
		baza.plik.seekg(-1, std::ios::end);
		for (int j = 0;j < baza.len;++j)
		{
			baza.plik.get(b);
			y = b - 48;
			ans = x*y + r;
			//std::cout << "x=" << x << " y=" << y << " r=" << r << " ans=" << ans << "\n";
			if (ans >= 10)
			{
				r = ans / 10;
				ans %= 10;
			}
			else
				r = 0;
			if (i + j < len)
			{
				plik.seekg(plik.tellg(), std::ios::beg);
				plik.get(temp);
				plik.seekp(-1+plik.tellp(), std::ios::beg);
				ans += temp-48;
				if (ans >= 10)
				{
					r += ans / 10;
					ans %= 10;
				}
			}
			else
			{
				++len;
			}
			plik.put(static_cast<char>(ans + 48));
			//std::cout << "End: - > i=" << i << " j=" << j << " r=" << r << " ans=" << ans << "\n";
			baza.plik.seekg(-2, std::ios::cur);
		}
		if (r > 0)
		{
			plik.put(static_cast<char>(r + 48));
			//std::cout << "i=" << i << " j=- r=" << r << "\n";
			r = 0;
			++len;
		}
		wart.plik.seekg(-2, std::ios::cur);
	}
	!*this;
}

void Plik::dif(Plik &baza, Plik &wart)
{
	if (baza.len > wart.len)
		odejmij(baza, wart);
	else if(baza.len < wart.len)
		odejmij(wart, baza);
	else
	{
		baza.plik.seekg(0, std::ios::beg);
		wart.plik.seekg(0, std::ios::beg);
		char b, w;
		int i = 0;
		int end = wart.len;
		while (i<end)
		{
			baza.plik.get(b);
			wart.plik.get(w);
			if (b > w)
			{
				odejmij(baza, wart);
				break;
			}
			else if (w > b)
			{
				odejmij(wart, baza);
				break;
			}
			++i;
		}
		if (i == end)
		{
			plik.seekp(0, std::ios::beg);
			plik.put('0');
			++len;
		}
	}
}

void Plik::divide(Plik &baza, Plik &wart)
{
	std::cout << "dzielenie";
}