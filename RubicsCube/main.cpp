#include <iostream>
#include "menu.h"
#include "Algo.h"
#include <string>

using namespace std;



int main()
{

	Algo cube;
	int var;
	bool flag = true;
	do {
		var = menu();
		if (var == 1)
		{
			int cmd;
			cmd = secmenu();
			if (cmd == 1)
			{
				cube.Save();
			}
			else if (cmd == 2)
			{
				cube.Read();
			}
		}
		else if (var == 2)
		{
			flag = cube.Check();
			if (flag == false)
			{
				cout << endl << "No! :(" << endl << endl;
			}
			else
			{
				flag = cube.find(0, 0);
				if (flag == true)
				{
					cout << endl << "Yes" << endl << endl;
				}
				else
				{
					cout << endl << "No! :(" << endl << endl;
				}
			}
		}
		else if (var == 3)
		{
			cube.Show();
		}
		else if (var == 4)
		{
			spinmenu();
			string tmp;
			cin >> tmp;
			if (tmp == "U")cube.UR();
			if (tmp == "U'")cube.UL();
			if (tmp == "L")cube.LR();
			if (tmp == "L'")cube.LL();
			if (tmp == "F")cube.FR();
			if (tmp == "F'")cube.FL();
			if (tmp == "R")cube.RR();
			if (tmp == "R'")cube.RL();
			if (tmp == "D")cube.DR();
			if (tmp == "D'")cube.DL();
			if (tmp == "B")cube.BR();
			if (tmp == "B'")cube.BL();
		}
		else if (var == 5)
		{
			cube.RandomSpin();
		}
		else if (var == 6)
		{
			cube.setString();
			flag = cube.Check();
			if (flag == true)
			{
				flag = cube.find(0, 0);
				if (flag == true)
				{
					cout << endl << "solution" << endl;
					cube.getString();
					cout << endl;
				}
				else
				{
					cout << "wrong angle or edge!" << endl;
				}
			}
			else
			{
				cout << "no solution!" << endl;
			}
		}
		if (var != 7)
		{

			cout << "click ENTER" << endl;
			getchar();
			getchar();
		}
	}


	while (var != 7);
	return 0;



}
