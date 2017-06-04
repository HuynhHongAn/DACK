#include "Package.h"

Package::Package()
{
	m_row = 0;
	m_col = 0;
	m_size = 0;
	m_code = "";
	m_price = 0;
	m_date = "";
}

Package::Package(const Package & p)
{
	m_row = p.m_row;
	m_col = p.m_col;
	m_size = p.m_size;
	m_code = p.m_code;
	m_price = p.m_price;
	m_date = p.m_date;
}

istream & operator >> (istream &i, Package &p)
{
	i >> p.m_row >> p.m_col >> p.m_size >> p.m_code >> p.m_price >> p.m_date;
	return i;
}
