#include "Area.h"

Area::Area()
{
	m_X = 0;
	m_Y = 0;
	m_rad = 0;
	m_width = 0;
	m_height = 0;
}

Area::Area(const Area &p)
{
	m_X = p.m_X;
	m_Y = p.m_Y;
	m_rad = p.m_rad;
	m_width = p.m_width;
	m_height = p.m_height;
	m_packages = p.m_packages;
}

void Area::display(ostream &o)
{
	vector<vector<int> > p(m_height);
	for (int i = 0; i < p.size(); i++)
		p[i].resize(m_width);

	for (int i = 0; i < m_packages.size(); i++) {
		int row = m_packages[i].m_row;
		int collum = m_packages[i].m_col;

		for (int j = 0; j < m_packages[i].m_size; j++) {
			if (collum + j >= m_width) {		//Kích thược không hợp lệ
				cout << "Error!!";
				return;
			}
			p[row][collum + j] = m_packages[i].m_size;
		}
	}
	
	for (int i = 0; i < p.size(); i++) {
		for (int j = 0; j < p[i].size(); j++)
			if (p[i][j] == 0)
				o << "- ";
			else
				o << p[i][j] << " ";
		cout << endl;
	}
}

int Area::isHavePackage(int p, int q)
{
	for (int i = 0; i < m_packages.size(); i++)
		if (m_packages[i].m_row == p) {
			if (q >= m_packages[i].m_col && q < m_packages[i].m_col + m_packages[i].m_size)
				return i;
		}
	return -1;
}

bool Area::deletePackage(int p, int q)
{
	for (int i = 0; i < m_packages.size(); i++)
		if (m_packages[i].m_row == p) {
			if (q >= m_packages[i].m_col && q < m_packages[i].m_col + m_packages[i].m_size) {
				m_packages.erase(m_packages.begin() + i, m_packages.begin() + i + 1);
				return true;
			}
		}

	return false;
}

bool Area::insertPackage(Package package)
{
	for (int i = 0; i < package.m_size; i++)
		if (isHavePackage(package.m_row, package.m_col + i) >= 0)
			return false;

	m_packages.push_back(package);

	return true;
}

istream & operator >> (istream &in, Area &p)
{
	int nPackage;

	in >> p.m_X >> p.m_Y >> p.m_rad >> p.m_height >> p.m_width >> nPackage;
	p.m_packages.resize(nPackage);
	for (int i = 0; i < nPackage; i++)
		in >> p.m_packages[i];

	return in;
}

string standardize(string p)
{
	while (p[0] == ' ')
		p.erase(0, 1);
	while (p[p.size() - 1] == ' ')
		p.pop_back();

	string res;
	for (int i = 0; i < p.size(); i++) {
		if (p[i] == ' ') {
			if (res.size() > 0 && res[res.size() - 1] != ' ')
				res.push_back(p[i]);
		}
		else
			res.push_back(p[i]);
	}

	return res;
}

string getToken(string p, int nToken)
{
	int temp(nToken - 1);

	int index;

	if (temp > 0) {
		for (int i = 0; i < p.size(); i++) {
			if (p[i] == ' ')
				temp--;
			if (temp == 0) {
				index = i + 1;
				break;
			}
		}
	}

	if (temp > 0)
		return "";

	string res;
	while (p[index] != ' ' && p[index] != '\0')
		res.push_back(p[index]), index++;
	return res;
}

int getArea(string p)
{
	p.erase(0, 1);
	p.pop_back();	//Xóa dấu ngoặc vuông
	return atoi(p.c_str());
}

pair<int, int> getLocal(string p)
{
	p.erase(0, 1);
	p.pop_back();
	pair<int, int> local;
	string x, y;

	int i = 0;
	while (p[i] != ',')
		x.push_back(p[i]), i++;

	i++;
	while (p[i] != '\0')
		y.push_back(p[i]), i++;

	return{ atoi(x.c_str()), atoi(y.c_str()) };
}
void move(vector<Area>& p, string command)
{
	command = standardize(command);

	if (command[0] != 'M') {		//Cú pháp không đúng
		cout << "Error !!" << endl;
		return;
	}

	int area0, area1;
	int r0, r1, c0, c1;

	area0 = getArea(getToken(command, 2));
	area1 = getArea(getToken(command, 4));
	r0 = getLocal(getToken(command, 3)).first;
	c0 = getLocal(getToken(command, 3)).second;
	r1 = getLocal(getToken(command, 5)).first;
	c1 = getLocal(getToken(command, 5)).second;

	if (area0 <= 0 || area0 > p.size() || area1 <= 0 || area1 > p.size()) {
		cout << "Error !!" << endl;			//Khu vực không tồn tại
		return;
	}

	if (r0 < 0 || c0 < 0 || r1 < 0 || c1 < 0 || r0 >= p[area0 - 1].m_height ||
			c0 >= p[area0 - 1].m_width || r1 >= p[area1 - 1].m_height || c1 >= p[area1 - 1].m_width) {
		cout << "Error !!" << endl;			//Kiện hàng không tồn tại
		return;
	}

	if (p[area0 - 1].isHavePackage(r0, c0) < 0 || p[area1 - 1].isHavePackage(r1, c1) >= 0) {		//Đã có kiện hàng
		cout << "Error !!" << endl;			//Kiện hàng không tồn tại
		return;
	}
	
	Package k(p[area0 - 1].m_packages[p[area0 - 1].isHavePackage(r0, c0)]);
	k.m_row = r1;
	k.m_col = c1;
	if (!p[area1 - 1].insertPackage(k)) {
		cout << "Erorr !!" << endl;
		return;
	}
	else {
		p[area0 - 1].deletePackage(r0, c0);
	}

	cout << "Successfully" << endl;
}
