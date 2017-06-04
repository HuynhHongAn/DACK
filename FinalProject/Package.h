#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Package {
	friend class Area;
	friend void move(vector<Area> &p, string command);
private:
	int m_row;
	int m_col;
	int m_size;
	string m_code;
	int m_price;
	string m_date;
public:
	Package();
	Package(const Package &p);

	friend istream& operator >> (istream &in, Package &p);
};