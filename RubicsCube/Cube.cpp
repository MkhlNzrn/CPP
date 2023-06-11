#include "Cube.h"
#include <string>


Cube::Cube() { //создаем то что будем считать кубиком рубика, в данном случае реализовано как ансайнд чар указатели
	cube = new unsigned char*[6];
	for (int i = 0; i < 6; i++) {
		cube[i] = new unsigned char[9];
		for (int j = 0; j < 9; j++) {
			if (i == 0) {
				cube[i][j] = 'y';
			}
			else if (i == 1) {
				cube[i][j] = 'r';
			}
			else if (i == 2) {
				cube[i][j] = 'g';
			}
			else if (i == 3) {
				cube[i][j] = 'o';
			}
			else if (i == 4) {
				cube[i][j] = 'w';
			}
			else {
				cube[i][j] = 'b';
			}
		}
	}
	str = "";
}

void Cube::Save() //сохран€ет текущую позицию куба
{
	ofstream fout;
	fout.open("rubik.out");
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 9; j += 3)
		{
			if (i == 0 || i == 4 || i == 5)
			{
				fout << "        ";
			}
			if (i == 1)
			{
				fout << cube[i][j] << " " << cube[i][j + 1] << " " << cube[i][j + 2] << " | " << cube[i + 1][j] << " " << cube[i + 1][j + 1] << " " << cube[i + 1][j + 2] << " | " << cube[i + 2][j] << " " << cube[i + 2][j + 1] << " " << cube[i + 2][j + 2] << "\n" << cube[i][j + 3] << " " << cube[i][j + 4] << " " << cube[i][j + 5] << " | " << cube[i + 1][j + 3] << " " << cube[i + 1][j + 4] << " " << cube[i + 1][j + 5] << " | " << cube[i + 2][j + 3] << " " << cube[i + 2][j + 4] << " " << cube[i + 2][j + 5] << "\n" << cube[i][j + 6] << " " << cube[i][j + 7] << " " << cube[i][j + 8] << " | " << cube[i + 1][j + 6] << " " << cube[i + 1][j + 7] << " " << cube[i + 1][j + 8] << " | " << cube[i + 2][j + 6] << " " << cube[i + 2][j + 7] << " " << cube[i + 2][j + 8] << "\n";
				i += 2;
				break;
			}
			else
			{
				fout << cube[i][j] << " " << cube[i][j + 1] << " " << cube[i][j + 2] << "\n";
			}
		}
		if (i == 0 || i == 3 || i == 4)
		{
			fout << "        - - -\n";
		}
	}
	fout.close();
}


void Cube::Read() //считывание с файла
{
	ifstream fin;
	fin.open("rubik.in");
	unsigned char c;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			fin >> c;
			if (c == '-' || c == '|')
			{
				j--;
			}
			else if (i == 0 || i == 4 || i == 5)
			{
				cube[i][j] = c;
			}
			else if (i == 1)
			{
				cube[i][j] = c;
				fin >> c;
				cube[i][j + 1] = c;
				fin >> c;
				cube[i][j + 2] = c;
				fin >> c;
				fin >> c;
				cube[i + 1][j] = c;
				fin >> c;
				cube[i + 1][j + 1] = c;
				fin >> c;
				cube[i + 1][j + 2] = c;
				fin >> c;
				fin >> c;
				cube[i + 2][j] = c;
				fin >> c;
				cube[i + 2][j + 1] = c;
				fin >> c;
				cube[i + 2][j + 2] = c;
				fin >> c;
				cube[i][j + 3] = c;
				fin >> c;
				cube[i][j + 4] = c;
				fin >> c;
				cube[i][j + 5] = c;
				fin >> c;
				fin >> c;
				cube[i + 1][j + 3] = c;
				fin >> c;
				cube[i + 1][j + 4] = c;
				fin >> c;
				cube[i + 1][j + 5] = c;
				fin >> c;
				fin >> c;
				cube[i + 2][j + 3] = c;
				fin >> c;
				cube[i + 2][j + 4] = c;
				fin >> c;
				cube[i + 2][j + 5] = c;
				fin >> c;
				cube[i][j + 6] = c;
				fin >> c;
				cube[i][j + 7] = c;
				fin >> c;
				cube[i][j + 8] = c;
				fin >> c;
				fin >> c;
				cube[i + 1][j + 6] = c;
				fin >> c;
				cube[i + 1][j + 7] = c;
				fin >> c;
				cube[i + 1][j + 8] = c;
				fin >> c;
				fin >> c;
				cube[i + 2][j + 6] = c;
				fin >> c;
				cube[i + 2][j + 7] = c;
				fin >> c;
				cube[i + 2][j + 8] = c;
				i += 2;
				break;
			}
		}
	}
	fin.close();
}


void Cube::Show() { //вывод текущего состо€ни€ куба в консоль, реализовано как сейв только в файл не сохран€ем
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 9; j += 3) {
			if (i == 0 || i == 4 || i == 5) {
				cout << "        ";
			}
			if (i == 1) {
				cout << cube[i][j] << " " << cube[i][j + 1] << " " << cube[i][j + 2] << " | " << cube[i + 1][j] << " " << cube[i + 1][j + 1] << " " << cube[i + 1][j + 2] << " | " << cube[i + 2][j] << " " << cube[i + 2][j + 1] << " " << cube[i + 2][j + 2] << "\n" << cube[i][j + 3] << " " << cube[i][j + 4] << " " << cube[i][j + 5] << " | " << cube[i + 1][j + 3] << " " << cube[i + 1][j + 4] << " " << cube[i + 1][j + 5] << " | " << cube[i + 2][j + 3] << " " << cube[i + 2][j + 4] << " " << cube[i + 2][j + 5] << "\n" << cube[i][j + 6] << " " << cube[i][j + 7] << " " << cube[i][j + 8] << " | " << cube[i + 1][j + 6] << " " << cube[i + 1][j + 7] << " " << cube[i + 1][j + 8] << " | " << cube[i + 2][j + 6] << " " << cube[i + 2][j + 7] << " " << cube[i + 2][j + 8] << "\n";
				i += 2;
				break;
			}
			else {
				cout << cube[i][j] << " " << cube[i][j + 1] << " " << cube[i][j + 2] << "\n";
			}
		}
		if (i == 0 || i == 3 || i == 4) {
			cout << "        - - -\n";
		}
	}
}

void Cube::RandomSpin() { //рандомим число count - количество спинов которое будет сделано. ј потом рандомим от 1 до 12 какой именно спин будем делать каждый раз из count.
	int count = rand() % 1000 + 200;
	for (int i = 0; i < count; i++) {
		int now = rand() % 12;
		//cout << now << " ";
		if (now == 0) {
			UR();
		}
		else if (now == 1) {
			UL();
		}
		else if (now == 2) {
			LR();
		}
		else if (now == 3) {
			LL();
		}
		else if (now == 4) {
			FR();
		}
		else if (now == 5) {
			FL();
		}
		else if (now == 6) {
			RR();
		}
		else if (now == 7) {
			RL();
		}
		else if (now == 8) {
			DR();
		}
		else if (now == 9) {
			DL();
		}
		else if (now == 10) {
			BR();
		}
		else if (now == 11) {
			BL();
		}
	}
}

void Cube::setString()
{
	str = "";
}

void Cube::getString()
{
	str += "END";
	cout << ": " << str.length() / 3 - 1 << endl << " : " << str;
}

Cube :: ~Cube() {
	cout << " delete ";
}



void Cube::Right(int turn) //ѕоворот грани turn по часовой стрелке
{
	unsigned char c;
	c = cube[turn][0];
	cube[turn][0] = cube[turn][6];
	cube[turn][6] = cube[turn][8];
	cube[turn][8] = cube[turn][2];
	cube[turn][2] = c;
	c = cube[turn][1];
	cube[turn][1] = cube[turn][3];
	cube[turn][3] = cube[turn][7];
	cube[turn][7] = cube[turn][5];
	cube[turn][5] = c;
}

void Cube::Left(int turn) //ѕоворот грани turn против часовой стрелки
{
	unsigned char c;
	c = cube[turn][0];
	cube[turn][0] = cube[turn][2];
	cube[turn][2] = cube[turn][8];
	cube[turn][8] = cube[turn][6];
	cube[turn][6] = c;
	c = cube[turn][1];
	cube[turn][1] = cube[turn][5];
	cube[turn][5] = cube[turn][7];
	cube[turn][7] = cube[turn][3];
	cube[turn][3] = c;
}

void Cube::UR()
{
	unsigned char c;
	Right(0);
	c = cube[5][6];
	cube[5][6] = cube[1][2];
	cube[1][2] = cube[2][2];
	cube[2][2] = cube[3][2];
	cube[3][2] = c;
	c = cube[5][8];
	cube[5][8] = cube[1][0];
	cube[1][0] = cube[2][0];
	cube[2][0] = cube[3][0];
	cube[3][0] = c;
	c = cube[5][7];
	cube[5][7] = cube[1][1];
	cube[1][1] = cube[2][1];
	cube[2][1] = cube[3][1];
	cube[3][1] = c;
}

void Cube::UL()
{
	unsigned char c;
	Left(0);
	c = cube[5][6];
	cube[5][6] = cube[3][2];
	cube[3][2] = cube[2][2];
	cube[2][2] = cube[1][2];
	cube[1][2] = c;
	c = cube[5][8];
	cube[5][8] = cube[3][0];
	cube[3][0] = cube[2][0];
	cube[2][0] = cube[1][0];
	cube[1][0] = c;
	c = cube[5][7];
	cube[5][7] = cube[3][1];
	cube[3][1] = cube[2][1];
	cube[2][1] = cube[1][1];
	cube[1][1] = c;
}

void Cube::LR()
{
	unsigned char c;
	Right(1);
	c = cube[0][0];
	cube[0][0] = cube[5][0];
	cube[5][0] = cube[4][0];
	cube[4][0] = cube[2][0];
	cube[2][0] = c;
	c = cube[0][6];
	cube[0][6] = cube[5][6];
	cube[5][6] = cube[4][6];
	cube[4][6] = cube[2][6];
	cube[2][6] = c;
	c = cube[0][3];
	cube[0][3] = cube[5][3];
	cube[5][3] = cube[4][3];
	cube[4][3] = cube[2][3];
	cube[2][3] = c;
}

void Cube::LL()
{
	unsigned char c;
	Left(1);
	c = cube[0][0];
	cube[0][0] = cube[2][0];
	cube[2][0] = cube[4][0];
	cube[4][0] = cube[5][0];
	cube[5][0] = c;
	c = cube[0][6];
	cube[0][6] = cube[2][6];
	cube[2][6] = cube[4][6];
	cube[4][6] = cube[5][6];
	cube[5][6] = c;
	c = cube[0][3];
	cube[0][3] = cube[2][3];
	cube[2][3] = cube[4][3];
	cube[4][3] = cube[5][3];
	cube[5][3] = c;
}

void Cube::FR()
{
	unsigned char c;
	Right(2);
	c = cube[0][6];
	cube[0][6] = cube[1][8];
	cube[1][8] = cube[4][2];
	cube[4][2] = cube[3][0];
	cube[3][0] = c;
	c = cube[0][8];
	cube[0][8] = cube[1][2];
	cube[1][2] = cube[4][0];
	cube[4][0] = cube[3][6];
	cube[3][6] = c;
	c = cube[0][7];
	cube[0][7] = cube[1][5];
	cube[1][5] = cube[4][1];
	cube[4][1] = cube[3][3];
	cube[3][3] = c;
}

void Cube::FL()
{
	unsigned char c;
	Left(2);
	c = cube[0][6];
	cube[0][6] = cube[3][0];
	cube[3][0] = cube[4][2];
	cube[4][2] = cube[1][8];
	cube[1][8] = c;
	c = cube[0][8];
	cube[0][8] = cube[3][6];
	cube[3][6] = cube[4][0];
	cube[4][0] = cube[1][2];
	cube[1][2] = c;
	c = cube[0][7];
	cube[0][7] = cube[3][3];
	cube[3][3] = cube[4][1];
	cube[4][1] = cube[1][5];
	cube[1][5] = c;
}

void Cube::RR()
{
	unsigned char c;
	Right(3);
	c = cube[0][2];
	cube[0][2] = cube[2][2];
	cube[2][2] = cube[4][2];
	cube[4][2] = cube[5][2];
	cube[5][2] = c;
	c = cube[0][8];
	cube[0][8] = cube[2][8];
	cube[2][8] = cube[4][8];
	cube[4][8] = cube[5][8];
	cube[5][8] = c;
	c = cube[0][5];
	cube[0][5] = cube[2][5];
	cube[2][5] = cube[4][5];
	cube[4][5] = cube[5][5];
	cube[5][5] = c;
}

void Cube::RL()
{
	unsigned char c;
	Left(3);
	c = cube[0][2];
	cube[0][2] = cube[5][2];
	cube[5][2] = cube[4][2];
	cube[4][2] = cube[2][2];
	cube[2][2] = c;
	c = cube[0][8];
	cube[0][8] = cube[5][8];
	cube[5][8] = cube[4][8];
	cube[4][8] = cube[2][8];
	cube[2][8] = c;
	c = cube[0][5];
	cube[0][5] = cube[5][5];
	cube[5][5] = cube[4][5];
	cube[4][5] = cube[2][5];
	cube[2][5] = c;
}

void Cube::DR()
{
	unsigned char c;
	Right(4);
	c = cube[5][0];
	cube[5][0] = cube[3][8];
	cube[3][8] = cube[2][8];
	cube[2][8] = cube[1][8];
	cube[1][8] = c;
	c = cube[5][2];
	cube[5][2] = cube[3][6];
	cube[3][6] = cube[2][6];
	cube[2][6] = cube[1][6];
	cube[1][6] = c;
	c = cube[5][1];
	cube[5][1] = cube[3][7];
	cube[3][7] = cube[2][7];
	cube[2][7] = cube[1][7];
	cube[1][7] = c;
}

void Cube::DL()
{
	unsigned char c;
	Left(4);
	c = cube[5][0];
	cube[5][0] = cube[1][8];
	cube[1][8] = cube[2][8];
	cube[2][8] = cube[3][8];
	cube[3][8] = c;
	c = cube[5][2];
	cube[5][2] = cube[1][6];
	cube[1][6] = cube[2][6];
	cube[2][6] = cube[3][6];
	cube[3][6] = c;
	c = cube[5][1];
	cube[5][1] = cube[1][7];
	cube[1][7] = cube[2][7];
	cube[2][7] = cube[3][7];
	cube[3][7] = c;
}

void Cube::BR()
{
	unsigned char c;
	Right(5);
	c = cube[0][0];
	cube[0][0] = cube[3][2];
	cube[3][2] = cube[4][8];
	cube[4][8] = cube[1][6];
	cube[1][6] = c;
	c = cube[0][2];
	cube[0][2] = cube[3][8];
	cube[3][8] = cube[4][6];
	cube[4][6] = cube[1][0];
	cube[1][0] = c;
	c = cube[0][1];
	cube[0][1] = cube[3][5];
	cube[3][5] = cube[4][7];
	cube[4][7] = cube[1][3];
	cube[1][3] = c;
}

void Cube::BL()
{
	unsigned char c;
	Left(5);
	c = cube[0][0];
	cube[0][0] = cube[1][6];
	cube[1][6] = cube[4][8];
	cube[4][8] = cube[3][2];
	cube[3][2] = c;
	c = cube[0][2];
	cube[0][2] = cube[1][0];
	cube[1][0] = cube[4][6];
	cube[4][6] = cube[3][8];
	cube[3][8] = c;
	c = cube[0][1];
	cube[0][1] = cube[1][3];
	cube[1][3] = cube[4][7];
	cube[4][7] = cube[3][5];
	cube[3][5] = c;
}




