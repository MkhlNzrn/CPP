#pragma once
#include <iostream>
using namespace std;

void spinmenu()
{
	cout << "Side:" << endl;
	cout << " Up - U" << endl;
	cout << " Down - D" << endl;
	cout << " Back - B" << endl;
	cout << " Front - F" << endl;
	cout << " Left - L" << endl;
	cout << " Right - R" << endl;
	cout << "Turn clockwise - U " << endl;
	cout << "Turn counter-clockwise - U' " << endl;
	cout << endl << "Ex: L' is a counter-clockwise rotation of the left side" << endl;
	cout << "Stop - 'e'" << endl;
}

int menu()
{
	cout << "1. Read or Save" << endl;
	cout << "2. invariant" << endl;
	cout << "3. Show Rubik's cube" << endl;
	cout << "4. Twist The Cube" << endl;
	cout << "5. Spin the Rubik's cube" << endl;
	cout << "6. Find a solution" << endl;
	cout << "7. Exit." << endl;

	cout << "Team: ";
	int var;
	cin >> var;
	return var;
}

int secmenu()
{
	cout << "1. save the file" << endl;
	cout << "2. read the file" << endl;

	cout << "Team : ";
	int cmd;
	cin >> cmd;
	return cmd;
}
