#pragma once

#include "Package.h"

class Area {
private:
	int m_X;
	int m_Y;
	float m_rad;
	unsigned int m_width;
	unsigned int m_height;

	vector<Package> m_packages;
public:
	Area();
	Area(const Area &p);

	void display(ostream &o);
	
	int isHavePackage(int, int);
	bool deletePackage(int, int);

	bool insertPackage(Package package);

	friend istream& operator >> (istream &in, Area &p);
	friend void move(vector<Area> &p, string command);
};