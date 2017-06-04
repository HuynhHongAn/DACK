#include "Area.h"

void input(char *fileName)
{
	fstream f(fileName, ios_base::in);

	int nArea;
	f >> nArea;

	vector<Area> areas(nArea);

	for (int i = 0; i < nArea; i++)
		f >> areas[i];

	char choose;
	do {
		system("cls");
		for (int i = 0; i < areas.size(); i++) {
			cout << "[" << i + 1 << "]" << endl;
			areas[i].display(cout);
			cout << endl;
		}

		cout << "Input command to move: ";
		string command;
		getline(cin, command);
		move(areas, command);
		
		cout << "Press 'Y' to continue, 'N' to exit: ";
		cin >> choose;
		cin.ignore();
	} while (choose == 'Y' || choose == 'y');
}

void main()
{
	input("input.txt");
	//This is changed
}