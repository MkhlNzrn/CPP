#include "Algo.h"


bool Algo::Check() //собираем все в один общий метод проверку
{
	for (int i = 0; i < 6; i++) //проверка на то что каждый цвет мы встретили в кубе
	{
		for (int j = 0; j < 9; j++)
		{
			if (cube[i][j] != 'r' && cube[i][j] != 'o' && cube[i][j] != 'g' && cube[i][j] != 'b' && cube[i][j] != 'y' && cube[i][j] != 'w')
			{
				return false;
			}
		}
	}
	int* mas = new int[6];
	for (int i = 0; i < 6; i++)
	{
		mas[i] = 0;
	}
	bool flag = true;
	vector<pair<unsigned char, unsigned char>> reb;
	flag = checkreb(reb, cube[0][7], cube[2][1], flag, mas);
	flag = checkreb(reb, cube[0][5], cube[3][1], flag, mas);
	flag = checkreb(reb, cube[0][1], cube[5][7], flag, mas);
	flag = checkreb(reb, cube[0][3], cube[1][1], flag, mas);
	flag = checkreb(reb, cube[1][5], cube[2][3], flag, mas);
	flag = checkreb(reb, cube[2][5], cube[3][3], flag, mas);
	flag = checkreb(reb, cube[3][5], cube[5][5], flag, mas);
	flag = checkreb(reb, cube[5][3], cube[1][3], flag, mas);
	flag = checkreb(reb, cube[4][1], cube[2][7], flag, mas);
	flag = checkreb(reb, cube[4][3], cube[1][7], flag, mas);
	flag = checkreb(reb, cube[4][5], cube[3][7], flag, mas);
	flag = checkreb(reb, cube[4][7], cube[5][1], flag, mas);
	vector<pair<unsigned char, pair<unsigned char, unsigned char>>> cor;
	flag = checkcor(cor, cube[0][6], cube[1][2], cube[2][0], flag, mas);
	flag = checkcor(cor, cube[0][8], cube[2][2], cube[3][0], flag, mas);
	flag = checkcor(cor, cube[1][8], cube[2][6], cube[4][0], flag, mas);
	flag = checkcor(cor, cube[2][8], cube[3][6], cube[4][2], flag, mas);
	flag = checkcor(cor, cube[0][2], cube[3][2], cube[5][8], flag, mas);
	flag = checkcor(cor, cube[0][0], cube[1][0], cube[5][6], flag, mas);
	flag = checkcor(cor, cube[1][6], cube[4][6], cube[5][0], flag, mas);
	flag = checkcor(cor, cube[3][8], cube[4][8], cube[5][2], flag, mas);
	vector<unsigned char> cen;
	flag = checkcen(cen, cube[0][4], flag, mas);
	flag = checkcen(cen, cube[1][4], flag, mas);
	flag = checkcen(cen, cube[2][4], flag, mas);
	flag = checkcen(cen, cube[3][4], flag, mas);
	flag = checkcen(cen, cube[4][4], flag, mas);
	flag = checkcen(cen, cube[5][4], flag, mas);
	if (flag == false)
	{
		return flag;
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			if (mas[i] > 9)
			{
				return false;
			}
		}
		return flag;
	}
}


bool Algo::find(bool b, int count) //сборка всех эллементов алгоритма в один метод для нахождения решения
{
	unsigned char** tmp = (unsigned char**)malloc(sizeof(unsigned char*) * 6);
	for (int i = 0; i < 6; i++)
	{
		tmp[i] = (unsigned char*)malloc(sizeof(unsigned char) * 9);
		for (int j = 0; j < 9; j++)
		{
			tmp[i][j] = cube[i][j];
		}
	}
	krest(); 
	edgekrest(); 
	firstsloi(); 
	secondsloi(); 
	bool flag = ykrest();
	if (flag == true)
	{
		flag = ycor();
		if (flag == true)
		{
			lastcor();
			while (cube[2][0] != 'g')
			{
				str += "U ";
				UR();
			}
			flag = lastedge();
		}
	}
	if (b)
	{
		littlecheck(count);
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cube[i][j] = tmp[i][j];
		}
	}
	//Show();
	delete(tmp);
	return flag;
}

//все проверки последовательны и значение флага true на момент прохождения конкретной проверки говорит о том что все проверки до этого он прошел
void Algo::checkmas(int* mas, unsigned char c) { //Проверка количества квадратиков каждого цвета
	if (c == 'y') {
		mas[0]++;
	}
	else if (c == 'r') {
		mas[1]++;
	}
	else if (c == 'g') {
		mas[2]++;
	}
	else if (c == 'o') {
		mas[3]++;
	}
	else if (c == 'w') {
		mas[4]++;
	}
	else if (c == 'b') {
		mas[5]++;
	}
}

bool Algo::checkcol(unsigned char a, unsigned char b) { //проверка на верность цветов противоположных центров
	if ((a == 'w' && b == 'y') || (a == 'y' && b == 'w') || (a == 'b' && b == 'g') || (a == 'g' && b == 'b') || (a == 'r' && b == 'o') || (a == 'o' && b == 'r') || a == b)
	{
		return true;
	}
	return false;
}

bool Algo::checkcen(vector<unsigned char>& cen, unsigned char a, bool flag, int* mas) { //проверка центров
	if (flag == true)
	{
		for (unsigned int i = 0; i < cen.size(); i++)
		{
			if (cen[i] == a)
			{
				return false; //нашелся центр который совпадает с уже существующим в векторе центров
			}
		}
		checkmas(mas, a); //если все четко и такого центра еще нет в векторе центров то пушбекаем его в вектор
		cen.push_back(a);
		return true;
	}
	else
	{
		return false;
	}
}

bool Algo::checkreb(vector<pair<unsigned char, unsigned char>>& reb, unsigned char a, unsigned char b, bool flag, int* mas) { //reb это вектор ребер заданный двумя цветами на пересечении которых это ребро находится
	if (flag == true)
	{
		for (unsigned int i = 0; i < reb.size(); i++) //проверка на существование ребра
		{
			if ((reb[i].first == a && reb[i].second == b) || (reb[i].first == b && reb[i].second == a) || checkcol(a, b)/*проверяем на повтор ребра и противоположность цветов если противоположны ребер смежных быть не может*/)
			{
				return false;
			}
		}
		checkmas(mas, a);
		checkmas(mas, b);
		reb.push_back({ a, b }); //если все четко и в векторе ребра еще нет то пушбекаем его в вектор
		return true;
	}
	else
	{
		return false;
	}
}

bool Algo::checkcor(vector<pair<unsigned char, pair<unsigned char, unsigned char>>>& cor, unsigned char a, unsigned char b, unsigned char c, bool flag, int* mas) //cor это вектор уголков с тремя цветами в кубике
{
	if (flag == true)
	{
		for (unsigned int i = 0; i < cor.size(); i++) //проверка на повтор уголового эллемента
		{
			pair<unsigned char, unsigned char> now = cor[i].second;
			unsigned char first = cor[i].first, second = now.first, third = now.second;
			if ((first == a && second == b && third == c) || (first == a && second == c && third == b) || (first == b && second == a && third == c) || (first == b && second == c && third == a) || (first == c && second == a && third == b) || (first == c && second == b && third == a) || checkcol(a, b) || checkcol(a, c) || checkcol(b, c))
			{
				return false;
			}
		}
		checkmas(mas, a);
		checkmas(mas, b);
		checkmas(mas, c);
		cor.push_back({ a, {b, c} }); //если все четко и углового эллемента в векторе нет - заносим его туда
		return true;
	}
	else
	{
		return false;
	}
}

void Algo::goodw(int a) 
{
	while (cube[4][a] == 'w')
	{
		str += "D ";
		DR();
	}
}

void Algo::findkrest() { 
	for (int i = 0; i < 6; i++) {
		if (i != 4) {
			for (int j = 1; j < 9; j += 2) {
				if (cube[i][j] == 'w') {
					if (i == 0) {
						if (j == 1) {
							goodw(7);
							str += "B B ";
							BR();
							BR();
						}
						else if (j == 3) {
							goodw(3);
							str += "L L ";
							LR();
							LR();
						}
						else if (j == 5) {
							goodw(5);
							str += "R R ";
							RR();
							RR();
						}
						else if (j == 7) {
							goodw(1);
							str += "F F ";
							FR();
							FR();
						}
					}
					else if (i == 1) {
						if (j == 1) {
							goodw(3);
							str += "L D F' ";
							LR();
							DR();
							FL();
						}
						else if (j == 3) {
							goodw(7);
							str += "B ";
							BR();
						}
						else if (j == 5) {
							goodw(1);
							str += "F' ";
							FL();
						}
						else if (j == 7) {
							str += "L' D F' ";
							LL();
							DR();
							FL();
						}
					}
					else if (i == 2) {
						if (j == 1) {
							goodw(1);
							str += "F D R' ";
							FR();
							DR();
							RL();
						}
						else if (j == 3) {
							goodw(3);
							str += "L ";
							LR();
						}
						else if (j == 5) {
							goodw(5);
							str += "R ";
							RL();
						}
						else if (j == 7) {
							str += "F' D R' ";
							FL();
							DR();
							RL();
						}
					}
					else if (i == 3) {
						if (j == 1) {
							goodw(5);
							str += "R D B' ";
							RR();
							DR();
							BL();
						}
						else if (j == 3) {
							goodw(1);
							str += "F ";
							FR();
						}
						else if (j == 5) {
							goodw(7);
							str += "B' ";
							BL();
						}
						else if (j == 7) {
							str += "R' D B' ";
							RL();
							DR();
							BL();
						}
					}
					else if (i == 5) {
						if (j == 1) {
							str += "B D' R ";
							BR();
							DL();
							RR();
						}
						else if (j == 3) {
							goodw(3);
							str += "B' ";
							LL();
						}
						else if (j == 5) {
							goodw(5);
							str += "R ";
							RR();
						}
						else if (j == 7) {
							goodw(7);
							str += "B' D' R ";
							BL();
							DL();
							RR();
						}
					}
				}
			}
		}
	}
}

void Algo::krest() { 
	while (true) {
		if (cube[4][1] == 'w' && cube[4][3] == 'w' && cube[4][5] == 'w' && cube[4][7] == 'w') {
			break;
		}
		else {
			findkrest();
		}
	}
}

int Algo::count_edge_krest() {
	int count = 0;
	if (cube[2][4] == cube[2][7]) {
		count++;
	}
	if (cube[1][4] == cube[1][7]) {
		count++;
	}
	if (cube[3][4] == cube[3][7]) {
		count++;
	}
	if (cube[5][4] == cube[5][1]) {
		count++;
	}
	return count;
}

void Algo::edgekrest() {
	int count = count_edge_krest();
	while (count < 2) {
		str += "DR ";
		DR();
		count = count_edge_krest();
	}
	if (count == 2) {
		if (cube[2][4] == cube[2][7] && cube[5][4] == cube[5][1]) {
			str += "R D D R' D' D' R ";
			RR();
			DR();
			DR();
			RL();
			DL();
			DL();
			RR();
		}
		else if (cube[1][4] == cube[1][7] && cube[3][4] == cube[3][7]) {
			str += "F D D F' D' D' F ";
			FR();
			DR();
			DR();
			FL();
			DL();
			DL();
			FR();
		}
		else if (cube[3][4] == cube[3][7] && cube[5][4] == cube[5][1]) {
			str += "F D F' D' F ";
			FR();
			DR();
			FL();
			DL();
			FR();
		}
		else if (cube[3][4] == cube[3][7] && cube[2][4] == cube[2][7]) {
			str += "L D L' D' L ";
			LR();
			DR();
			LL();
			DL();
			LR();
		}
		else if (cube[1][4] == cube[1][7] && cube[2][4] == cube[2][7]) {
			str += "B D B' D' B ";
			BR();
			DR();
			BL();
			DL();
			BR();
		}
		else if (cube[1][4] == cube[1][7] && cube[5][4] == cube[5][1]) {
			str += "R D R' D' R ";
			RR();
			DR();
			RL();
			DL();
			RR();
		}
	}
}

void Algo::cornerwhile(int var) {
	if (var == 0) {
		while (cube[4][0] != 'w' || cube[2][6] != 'g') {
			str += "F U F' U' ";
			FR();
			UR();
			FL();
			UL();
		}
	}
	else if (var == 2) {
		while (cube[4][2] != 'w' || cube[3][6] != 'o') {
			str += "R U R' U' ";
			RR();
			UR();
			RL();
			UL();
		}
	}
	else if (var == 6) {
		while (cube[4][6] != 'w' || cube[1][6] != 'r') {
			str += "L U L' U' ";
			LR();
			UR();
			LL();
			UL();
		}
	}
	else {
		while (cube[4][8] != 'w' || cube[5][2] != 'b') {
			str += "B U B' U' ";
			BR();
			UR();
			BL();
			UL();
		}
	}
}

void Algo::R6perebor() {
	str += "L U L' U' ";
	LR();
	UR();
	LL();
	UL();
}

void Algo::G6perebor() {
	str += "F U F' U' ";
	FR();
	UR();
	FL();
	UL();
}

void Algo::O6perebor() {
	str += "R U R' U' ";
	RR();
	UR();
	RL();
	UL();
}

void Algo::B6perebor() {
	str += "B U B' U' ";
	BR();
	UR();
	BL();
	UL();
}

void Algo::find_corner() {
	for (int i = 0; i < 6; i++) {
		if (i != 4) {
			for (int j = 0; j < 9; j += 2) {
				if (cube[i][j] == 'w') {
					if (i == 0) {
						if (j == 0) {
							if (cube[1][0] == 'b') {
								cornerwhile(6);
							}
							else if (cube[1][0] == 'r') {
								str += "U' ";
								UL();
								cornerwhile(0);
							}
							else if (cube[1][0] == 'o') {
								str += "U ";
								UR();
								cornerwhile(8);
							}
							else {
								str += "U U ";
								UR();
								UR();
								cornerwhile(2);
							}
						}
						else if (j == 2) {
							if (cube[3][2] == 'b') {
								cornerwhile(8);
							}
							else if (cube[3][2] == 'o') {
								str += "U ";
								UR();
								cornerwhile(2);
							}
							else if (cube[3][2] == 'r') {
								str += "U' ";
								UL();
								cornerwhile(6);
							}
							else {
								str += "U U ";
								UR();
								UR();
								cornerwhile(0);
							}
						}
						else if (j == 6) {
							if (cube[2][0] == 'r') {
								cornerwhile(0);
							}
							else if (cube[2][0] == 'g') {
								str += "U' ";
								UL();
								cornerwhile(2);
							}
							else if (cube[2][0] == 'b') {
								str += "U ";
								UR();
								cornerwhile(6);
							}
							else {
								str += "U U ";
								UR();
								UR();
								cornerwhile(8);
							}
						}
						else if (j == 8) {
							if (cube[2][2] == 'o') {
								cornerwhile(2);
							}
							else if (cube[2][2] == 'g') {
								str += "U ";
								UR();
								cornerwhile(0);
							}
							else if (cube[2][2] == 'b') {
								str += "U' ";
								UL();
								cornerwhile(8);
							}
							else {
								str += "U U ";
								UR();
								UR();
								cornerwhile(6);
							}
						}
					}
					else if (i == 1) {
						if (j == 0)
						{
							if (cube[0][0] == 'r')
							{
								cornerwhile(6);
							}
							else if (cube[0][0] == 'b')
							{
								str += "U ";
								UR();
								cornerwhile(8);
							}
							else if (cube[0][0] == 'g')
							{
								str += "U' ";
								UL();
								cornerwhile(0);
							}
							else
							{
								str += "U U ";
								UR();
								UR();
								cornerwhile(2);
							}
						}
						else if (j == 2) {
							if (cube[0][6] == 'r')
							{
								cornerwhile(0);
							}
							else if (cube[0][6] == 'g') {
								str += "U' ";
								UL();
								cornerwhile(2);
							}
							else if (cube[0][6] == 'b') {
								str += "U ";
								UR();
								cornerwhile(6);
							}
							else {
								str += "U U ";
								UR();
								UR();
								cornerwhile(8);
							}
						}
						else if (j == 6) {
							if (cube[4][6] == 'b') {
								cornerwhile(6);
							}
							else if (cube[4][6] == 'r') {
								R6perebor();
								str += "U' ";
								UL();
								cornerwhile(0);
							}
							else if (cube[4][6] == 'o') {
								R6perebor();
								str += "U ";
								UR();
								cornerwhile(8);
							}
							else {
								R6perebor();
								str += "U U ";
								UR();
								UR();
								cornerwhile(2);
							}
						}
						else if (j == 8) {
							if (cube[2][6] == 'r') {
								cornerwhile(0);
							}
							else if (cube[2][6] == 'g') {
								G6perebor();
								str += "U' ";
								UL();
								cornerwhile(2);
							}
							else if (cube[2][6] == 'b') {
								G6perebor();
								str += "U ";
								UR();
								cornerwhile(6);
							}
							else {
								G6perebor();
								str += "U U ";
								UR();
								UR();
								cornerwhile(8);
							}
						}
					}
					else if (i == 2) {
						if (j == 0) {
							if (cube[0][6] == 'g') {
								cornerwhile(0);
							}
							else if (cube[0][6] == 'r') {
								str += "U ";
								UR();
								cornerwhile(6);
							}
							else if (cube[0][6] == 'o') {
								str += "U' ";
								UL();
								cornerwhile(2);
							}
							else {
								str += "U U ";
								UR();
								UR();
								cornerwhile(8);
							}
						}
						else if (j == 2) {
							if (cube[0][8] == 'g') {
								cornerwhile(2);
							}
							else if (cube[0][8] == 'r') {
								str += "U ";
								UR();
								cornerwhile(0);
							}
							else if (cube[0][8] == 'o') {
								str += "U' ";
								UL();
								cornerwhile(8);
							}
							else {
								str += "U U ";
								UR();
								UR();
								cornerwhile(6);
							}
						}
						else if (j == 6) {
							if (cube[4][0] == 'r')
							{
								cornerwhile(0);
							}
							else if (cube[4][0] == 'g') {
								G6perebor();
								str += "U' ";
								UL();
								cornerwhile(2);
							}
							else if (cube[4][0] == 'b')
							{
								G6perebor();
								str += "U ";
								UR();
								cornerwhile(6);
							}
							else
							{
								G6perebor();
								str += "U U ";
								UR();
								UR();
								cornerwhile(8);
							}
						}
						else if (j == 8)
						{
							if (cube[4][2] == 'o')
							{
								cornerwhile(2);
							}
							else if (cube[4][2] == 'g')
							{
								O6perebor();
								str += "U ";
								UR();
								cornerwhile(0);
							}
							else if (cube[4][2] == 'b')
							{
								O6perebor();
								str += "U' ";
								UL();
								cornerwhile(8);
							}
							else
							{
								O6perebor();
								str += "U U ";
								UR();
								UR();
								cornerwhile(6);
							}
						}
					}
					else if (i == 3)
					{
						if (j == 0)
						{
							if (cube[2][2] == 'g')
							{
								cornerwhile(2);
							}
							else if (cube[2][2] == 'r')
							{
								str += "U ";
								UR();
								cornerwhile(0);
							}
							else if (cube[2][2] == 'o') {
								str += "U' ";
								UL();
								cornerwhile(8);
							}
							else {
								str += "U U ";
								UR();
								UR();
								cornerwhile(6);
							}
						}
						else if (j == 2) {
							if (cube[0][2] == 'o') {
								cornerwhile(8);
							}
							else if (cube[0][2] == 'g') {
								str += "U ";
								UR();
								cornerwhile(2);
							}
							else if (cube[0][2] == 'b') {
								str += "U' ";
								UL();
								cornerwhile(6);
							}
							else {
								str += "U U ";
								UR();
								UR();
								cornerwhile(0);
							}
						}
						else if (j == 6) {
							if (cube[2][8] == 'o') {
								cornerwhile(2);
							}
							else if (cube[2][8] == 'g') {
								O6perebor();
								str += "U ";
								UR();
								cornerwhile(0);
							}
							else if (cube[2][8] == 'b') {
								O6perebor();
								str += "U' ";
								UL();
								cornerwhile(8);
							}
							else {
								O6perebor();
								str += "U U ";
								UR();
								UR();
								cornerwhile(6);
							}
						}
						else if (j == 8) {
							if (cube[4][8] == 'b') {
								cornerwhile(8);
							}
							else if (cube[4][8] == 'o') {
								B6perebor();
								str += "U ";
								UR();
								cornerwhile(2);
							}
							else if (cube[4][8] == 'r') {
								B6perebor();
								str += "U' ";
								UL();
								cornerwhile(6);
							}
							else {
								B6perebor();
								str += "U U ";
								UR();
								UR();
								cornerwhile(0);
							}
						}
					}
					else if (i == 5) {
						if (j == 0) {
							if (cube[4][6] == 'r') {
								cornerwhile(6);
							}
							else if (cube[4][6] == 'g') {
								R6perebor();
								str += "U' ";
								UL();
								cornerwhile(0);
							}
							else if (cube[4][6] == 'b') {
								R6perebor();
								str += "U ";
								UR();
								cornerwhile(8);
							}
							else {
								R6perebor();
								str += "U U ";
								UR();
								UR();
								cornerwhile(2);
							}
						}
						else if (j == 2) {
							if (cube[4][8] == 'o') {
								cornerwhile(8);
							}
							else if (cube[4][8] == 'b') {
								B6perebor();
								str += "U' ";
								UL();
								cornerwhile(6);
							}
							else if (cube[4][8] == 'g') {
								B6perebor();
								str += "U ";
								UR();
								cornerwhile(2);
							}
							else {
								B6perebor();
								str += "U U ";
								UR();
								UR();
								cornerwhile(0);
							}
						}
						else if (j == 6) {
							if (cube[1][0] == 'r') {
								cornerwhile(6);
							}
							else if (cube[1][0] == 'b') {
								str += "U ";
								UR();
								cornerwhile(8);
							}
							else if (cube[1][0] == 'g') {
								str += "U' ";
								UL();
								cornerwhile(0);
							}
							else {
								str += "U U ";
								UR();
								UR();
								cornerwhile(2);
							}
						}
						else if (j == 8) {
							if (cube[3][2] == 'o') {
								cornerwhile(8);
							}
							else if (cube[3][2] == 'b') {
								str += "U' ";
								UL();
								cornerwhile(6);
							}
							else if (cube[3][2] == 'g') {
								str += "U ";
								UR();
								cornerwhile(2);
							}
							else {
								str += "U U ";
								UR();
								UR();
								cornerwhile(0);
							}
						}
					}
				}
			}
		}
	}
	if (cube[1][6] != 'r')
	{
		str += "L U L' U' ";
		LR();
		UR();
		LL();
		UL();
	}
	else if (cube[2][6] != 'g')
	{
		str += "F U F' U' ";
		FR();
		UR();
		FL();
		UL();
	}
	else if (cube[3][6] != 'o')
	{
		str += "R U R' U' ";
		RR();
		UR();
		RL();
		UL();
	}
	else if (cube[5][2] != 'b')
	{
		str += "B U B' U' ";
		BR();
		UR();
		BL();
		UL();
	}
}

void Algo::Bedge()
{
	if (cube[0][1] == 'o')
	{
		str += "U' R' U R U B U' B' ";
		UL();
		RL();
		UR();
		RR();
		UR();
		BR();
		UL();
		BL();
	}
	else
	{
		str += "U L U' L' U' B' U B ";
		UR();
		LR();
		UL();
		LL();
		UL();
		BL();
		UR();
		BR();
	}
}

void Algo::Redge() {
	if (cube[0][3] == 'b') {
		str += "U' B' U B U L U' L' ";
		UL();
		BL();
		UR();
		BR();
		UR();
		LR();
		UL();
		LL();
	}
	else {
		str += "U F U' F' U' L' U L ";
		UR();
		FR();
		UL();
		FL();
		UL();
		LL();
		UR();
		LR();
	}
}

void Algo::Gedge() {
	if (cube[0][7] == 'r') {
		str += "U' L' U L U F U' F' ";
		UL();
		LL();
		UR();
		LR();
		UR();
		FR();
		UL();
		FL();
	}
	else
	{
		str += "U R U' R' U' F' U F ";
		UR();
		RR();
		UL();
		RL();
		UL();
		FL();
		UR();
		FR();
	}
}

void Algo::Oedge()
{
	if (cube[0][5] == 'g')
	{
		str += "U' F' U F U R U' R' ";
		UL();
		FL();
		UR();
		FR();
		UR();
		RR();
		UL();
		RL();
	}
	else
	{
		str += "U B U' B' U' R' U R ";
		UR();
		BR();
		UL();
		BL();
		UL();
		RL();
		UR();
		RR();
	}
}

void Algo::find_edge()
{
	for (int j = 1; j < 9; j += 2)
	{
		if (cube[0][1] != 'y' && cube[5][7] != 'y')
		{
			if (cube[5][7] == 'g')
			{
				str += "U U ";
				UR();
				UR();
				Gedge();
			}
			else if (cube[5][7] == 'r')
			{
				str += "U' ";
				UL();
				Redge();
			}
			else if (cube[5][7] == 'o')
			{
				str += "U ";
				UR();
				Oedge();
			}
			else
			{
				Bedge();
			}
		}
		else if (cube[0][5] != 'y' && cube[3][1] != 'y')
		{
			if (cube[3][1] == 'g')
			{
				str += "U ";
				UR();
				Gedge();
			}
			else if (cube[3][1] == 'r')
			{
				str += "U U ";
				UR();
				UR();
				Redge();
			}
			else if (cube[3][1] == 'o')
			{
				Oedge();
			}
			else
			{
				str += "U' ";
				UL();
				Bedge();
			}
		}
		else if (cube[0][3] != 'y' && cube[1][1] != 'y')
		{
			if (cube[1][1] == 'g')
			{
				str += "U' ";
				UL();
				Gedge();
			}
			else if (cube[1][1] == 'r')
			{
				Redge();
			}
			else if (cube[1][1] == 'o')
			{
				str += "U U ";
				UR();
				UR();
				Oedge();
			}
			else
			{
				str += "U ";
				UR();
				Bedge();
			}
		}
		else if (cube[0][7] != 'y' && cube[2][1] != 'y')
		{
			if (cube[2][1] == 'g')
			{
				Gedge();
			}
			else if (cube[2][1] == 'r')
			{
				str += "U ";
				UR();
				Redge();
			}
			else if (cube[2][1] == 'o')
			{
				str += "U' ";
				UL();
				Oedge();
			}
			else
			{
				str += "U U ";
				UR();
				UR();
				Bedge();
			}
		}
	}
	if ((cube[1][5] != 'r' || cube[2][3] != 'g') && cube[1][5] != 'y' && cube[2][3] != 'y')
	{
		str += "F U' F' U' L' U L ";
		FR();
		UL();
		FL();
		UL();
		LL();
		UR();
		LR();
	}
	else if ((cube[2][5] != 'g' || cube[3][3] != 'o') && cube[2][5] != 'y' && cube[3][3] != 'y')
	{
		str += "R U' R' U' F' U F ";
		RR();
		UL();
		RL();
		UL();
		FL();
		UR();
		FR();
	}
	else if ((cube[3][5] != 'o' || cube[5][5] != 'b') && cube[3][5] != 'y' && cube[5][5] != 'y')
	{
		str += "B U' B' U' R' U R ";
		BR();
		UL();
		BL();
		UL();
		RL();
		UR();
		RR();
	}
	else if ((cube[5][3] != 'b' || cube[1][3] != 'r') && cube[5][3] != 'y' && cube[1][3] != 'y')
	{
		str += "L U' L' U' B' U B ";
		LR();
		UL();
		LL();
		UL();
		BL();
		UR();
		BR();
	}
}

void Algo::firstsloi()
{
	while (true)
	{
		if (cube[4][0] == 'w' && cube[4][2] == 'w' && cube[4][6] == 'w' && cube[4][8] == 'w' && cube[1][6] == 'r' && cube[1][8] == 'r' && cube[2][6] == 'g' && cube[2][8] == 'g' && cube[3][6] == 'o' && cube[3][8] == 'o' && cube[5][0] == 'b' && cube[5][2] == 'b')
		{
			break;
		}
		else
		{
			find_corner();
		}
	}
}

void Algo::secondsloi()
{
	while (true)
	{
		if (cube[2][3] == 'g' && cube[2][5] == 'g' && cube[1][3] == 'r' && cube[1][5] == 'r' && cube[3][3] == 'o' && cube[3][5] == 'o' && cube[5][3] == 'b' && cube[5][5] == 'b')
		{
			break;
		}
		else
		{
			find_edge();
		}
	}
}

void Algo::ykrestG(int count)
{
	for (int i = 0; i < count; i++)
	{
		str += "F R U R' U' F' ";
		FR();
		RR();
		UR();
		RL();
		UL();
		FL();
	}
}

void Algo::ykrestR(int count)
{
	for (int i = 0; i < count; i++)
	{
		str += "L F U F' U' L' ";
		LR();
		FR();
		UR();
		FL();
		UL();
		LL();
	}
}

bool Algo::ykrest()
{
	if (cube[0][1] != 'y' && cube[0][3] != 'y' && cube[0][5] != 'y' && cube[0][7] != 'y')
	{
		ykrestR(2);
		ykrestG(1);
	}
	else if (cube[0][1] == 'y' && cube[0][3] == 'y' && cube[0][5] != 'y' && cube[0][7] != 'y')
	{
		str += "U ";
		UR();
		ykrestR(2);
	}
	else if (cube[0][1] == 'y' && cube[0][3] != 'y' && cube[0][5] == 'y' && cube[0][7] != 'y')
	{
		ykrestR(2);
	}
	else if (cube[0][1] != 'y' && cube[0][3] != 'y' && cube[0][5] == 'y' && cube[0][7] == 'y')
	{
		str += "U' ";
		UL();
		ykrestR(2);
	}
	else if (cube[0][1] != 'y' && cube[0][3] == 'y' && cube[0][5] != 'y' && cube[0][7] == 'y')
	{
		str += "U U ";
		UR();
		UR();
		ykrestR(2);
	}
	else if (cube[0][1] == 'y' && cube[0][3] != 'y' && cube[0][5] != 'y' && cube[0][7] == 'y')
	{
		ykrestR(1);
	}
	else if (cube[0][1] != 'y' && cube[0][3] == 'y' && cube[0][5] == 'y' && cube[0][7] != 'y')
	{
		str += "U ";
		UR();
		ykrestR(1);
	}
	else if (cube[0][1] == 'y' && cube[0][3] == 'y' && cube[0][5] == 'y' && cube[0][7] == 'y')
	{

	}
	else
	{
		return false;
	}
	return true;
}

void Algo::vertolet()
{
	str += "R U' U' R' R' U' R R U' R' R' U' U' R ";
	RR();
	UL();
	UL();
	RL();
	RL();
	UL();
	RR();
	RR();
	UL();
	RL();
	RL();
	UL();
	UL();
	RR();
}

void Algo::ushki()
{
	str += "F R B' R' F' R B R' ";
	FR();
	RR();
	BL();
	RL();
	FL();
	RR();
	BR();
	RL();
}

void Algo::nos()
{
	str += "R' F' L' F R F' L F ";
	RL();
	FL();
	LL();
	FR();
	RR();
	FL();
	LR();
	FR();
}

void Algo::glazki()
{
	str += "R R D R' U U R D' R' U U R' ";
	RR();
	RR();
	DR();
	RL();
	UR();
	UR();
	RR();
	DL();
	RL();
	UR();
	UR();
	RL();
}

void Algo::triplpifpaf()
{
	str += "FR ";
	FR();
	for (int i = 0; i < 3; i++)
	{
		str += "RR UR RL UL ";
		RR();
		UR();
		RL();
		UL();
	}
	FL();
	str += "FL ";
}

void Algo::Rriba()
{
	str += "R U R' U R U U R' ";
	RR();
	UR();
	RL();
	UR();
	RR();
	UR();
	UR();
	RL();
}

void Algo::Lriba()
{
	str += "L' U' L U' L' U' U' L ";
	LL();
	UL();
	LR();
	UL();
	LL();
	UL();
	UL();
	LR();
}

bool Algo::ycor()
{
	if (cube[1][0] == 'y' && cube[1][2] == 'y' && cube[2][2] == 'y' && cube[5][8] == 'y')
	{
		vertolet();
	}
	else if (cube[3][0] == 'y' && cube[1][2] == 'y' && cube[5][6] == 'y' && cube[5][8] == 'y')
	{
		str += "U' ";
		UL();
		vertolet();
	}
	else if (cube[1][0] == 'y' && cube[2][0] == 'y' && cube[2][2] == 'y' && cube[3][2] == 'y')
	{
		str += "U ";
		UR();
		vertolet();
	}
	else if (cube[3][0] == 'y' && cube[3][2] == 'y' && cube[2][0] == 'y' && cube[5][6] == 'y')
	{
		str += "U U ";
		UR();
		UR();
		vertolet();
	}
	else if (cube[1][2] == 'y' && cube[3][0] == 'y' && cube[0][0] == 'y' && cube[0][2] == 'y')
	{
		ushki();
	}
	else if (cube[2][2] == 'y' && cube[5][8] == 'y' && cube[0][0] == 'y' && cube[0][6] == 'y')
	{
		str += "U ";
		UR();
		ushki();
	}
	else if (cube[5][6] == 'y' && cube[2][0] == 'y' && cube[0][8] == 'y' && cube[0][2] == 'y')
	{
		str += "U' ";
		UL();
		ushki();
	}
	else if (cube[3][2] == 'y' && cube[1][0] == 'y' && cube[0][8] == 'y' && cube[0][6] == 'y')
	{
		str += "U U ";
		UR();
		UR();
		ushki();
	}
	else if (cube[5][8] == 'y' && cube[1][2] == 'y' && cube[0][0] == 'y' && cube[0][8] == 'y')
	{
		nos();
	}
	else if (cube[1][0] == 'y' && cube[2][2] == 'y' && cube[0][2] == 'y' && cube[0][6] == 'y')
	{
		str += "U ";
		UR();
		nos();
	}
	else if (cube[5][6] == 'y' && cube[3][0] == 'y' && cube[0][2] == 'y' && cube[0][6] == 'y')
	{
		str += "U' ";
		UL();
		nos();
	}
	else if (cube[2][0] == 'y' && cube[3][2] == 'y' && cube[0][0] == 'y' && cube[0][8] == 'y')
	{
		str += "U U ";
		UR();
		UR();
		nos();
	}
	else if (cube[2][0] == 'y' && cube[2][2] == 'y' && cube[0][0] == 'y' && cube[0][2] == 'y')
	{
		glazki();
	}
	else if (cube[3][0] == 'y' && cube[3][2] == 'y' && cube[0][0] == 'y' && cube[0][6] == 'y')
	{
		str += "U ";
		UR();
		glazki();
	}
	else if (cube[1][0] == 'y' && cube[1][2] == 'y' && cube[0][8] == 'y' && cube[0][2] == 'y')
	{
		str += "U' ";
		UL();
		glazki();
	}
	else if (cube[5][6] == 'y' && cube[5][8] == 'y' && cube[0][6] == 'y' && cube[0][8] == 'y')
	{
		str += "U U ";
		UR();
		UR();
		glazki();
	}
	else if (cube[5][6] == 'y' && cube[5][8] == 'y' && cube[2][0] == 'y' && cube[2][2] == 'y')
	{
		triplpifpaf();
	}
	else if (cube[1][0] == 'y' && cube[1][2] == 'y' && cube[3][0] == 'y' && cube[3][2] == 'y')
	{
		str += "U ";
		UR();
		triplpifpaf();
	}
	else if (cube[0][6] == 'y' && cube[2][2] == 'y' && cube[3][2] == 'y' && cube[5][6] == 'y')
	{
		Rriba();
	}
	else if (cube[0][8] == 'y' && cube[1][2] == 'y' && cube[3][2] == 'y' && cube[5][6] == 'y')
	{
		str += "U ";
		UR();
		Rriba();
	}
	else if (cube[0][0] == 'y' && cube[2][2] == 'y' && cube[3][2] == 'y' && cube[1][2] == 'y')
	{
		str += "U' ";
		UL();
		Rriba();
	}
	else if (cube[0][2] == 'y' && cube[2][2] == 'y' && cube[1][2] == 'y' && cube[5][6] == 'y')
	{
		str += "U U ";
		UR();
		UR();
		Rriba();
	}
	else if (cube[0][8] == 'y' && cube[2][0] == 'y' && cube[1][0] == 'y' && cube[5][8] == 'y')
	{
		Lriba();
	}
	else if (cube[0][2] == 'y' && cube[2][0] == 'y' && cube[1][0] == 'y' && cube[3][0] == 'y')
	{
		str += "U ";
		UR();
		Lriba();
	}
	else if (cube[0][6] == 'y' && cube[3][0] == 'y' && cube[1][0] == 'y' && cube[5][8] == 'y')
	{
		str += "U' ";
		UL();
		Lriba();
	}
	else if (cube[0][0] == 'y' && cube[2][0] == 'y' && cube[3][0] == 'y' && cube[5][8] == 'y')
	{
		str += "U U ";
		UR();
		UR();
		Lriba();
	}
	else if (cube[0][6] == 'y' && cube[0][2] == 'y' && cube[0][0] == 'y' && cube[0][8] == 'y')
	{

	}
	else
	{
		return false;
	}
	return true;
}

void Algo::havepair()
{
	str += "F U F' U' F' L F F U' F' U' F U F' L'Z ";
	FR(); UR(); FL(); UL(); FL(); LR(); FR(); FR(); UL(); FL(); UL(); FR(); UR(); FL(); LL();
}

void Algo::notpair()
{
	str += "L F U' F' U' F U F' L' F U F' U' F' L F L' ";
	LR();
	FR();
	UL();
	FL();
	UL();
	FR();
	UR();
	FL();
	LL();
	FR();
	UR();
	FL();
	UL();
	FL();
	LR();
	FR();
	LL();
}

void Algo::lastcor()
{
	if (cube[5][6] == cube[5][8] && cube[1][0] != cube[1][2])
	{
		havepair();
	}
	else if (cube[1][0] == cube[1][2] && cube[2][0] != cube[2][2])
	{
		str += "U ";
		UR();
		havepair();
	}
	else if (cube[3][0] == cube[3][2] && cube[2][0] != cube[2][2])
	{
		str += "U' ";
		UL();
		havepair();
	}
	else if (cube[2][0] == cube[2][2] && cube[1][0] != cube[1][2])
	{
		str += "U U ";
		UR();
		UR();
		havepair();
	}
	else if (cube[1][0] == cube[1][2] && cube[3][0] == cube[3][2])
	{

	}
	else
	{
		notpair();
	}
}

void Algo::lastgl()
{
	str += "L' U L' U' L' U' L' U L U L L ";
	LL();
	UR();
	LL();
	UL();
	LL();
	UL();
	LL();
	UR();
	LR();
	UR();
	LR();
	LR();
}

void Algo::lastgr()
{
	str += "R U' R U R U R U' R' U' R' R' ";
	RR();
	UL();
	RR();
	UR();
	RR();
	UR();
	RR();
	UL();
	RL();
	UL();
	RL();
	RL();
}

void Algo::lastol()
{
	str += "F' U F' U' F' U' F' U F U F F ";
	FL();
	UR();
	FL();
	UL();
	FL();
	UL();
	FL();
	UR();
	FR();
	UR();
	FR();
	FR();
}

void Algo::lastor()
{
	str += "B U' B U B U B U' B' U' B' B' ";
	BR();
	UL();
	BR();
	UR();
	BR();
	UR();
	BR();
	UL();
	BL();
	UL();
	BL();
	BL();
}

void Algo::lastbl()
{
	str += "R' U R' U' R' U' R' U R U R R ";
	RL();
	UR();
	RL();
	UL();
	RL();
	UL();
	RL();
	UR();
	RR();
	UR();
	RR();
	RR();
}

void Algo::lastbr()
{
	str += "L U' L U L U L U' L' U' L' L' ";
	LR();
	UL();
	LR();
	UR();
	LR();
	UR();
	LR();
	UL();
	LL();
	UL();
	LL();
	LL();
}

void Algo::lastrl()
{
	str += "B' U B' U' B' U' B' U B U B B ";
	BL();
	UR();
	BL();
	UL();
	BL();
	UL();
	BL();
	UR();
	BR();
	UR();
	BR();
	BR();
}

void Algo::lastrr()
{
	str += "F U' F U F U F U' F' U' F' F' ";
	FR();
	UL();
	FR();
	UR();
	FR();
	UR();
	FR();
	UL();
	FL();
	UL();
	FL();
	FL();
}

bool Algo::lastedge()
{
	if (cube[2][1] == 'r' && cube[1][1] == 'o' && cube[3][1] == 'g' && cube[5][7] == 'b')
	{
		lastgl();
	}
	else if (cube[2][1] == 'o' && cube[1][1] == 'g' && cube[3][1] == 'r' && cube[5][7] == 'b')
	{
		lastgr();
	}
	else if (cube[2][1] == 'b' && cube[1][1] == 'r' && cube[3][1] == 'g' && cube[5][7] == 'o')
	{
		lastol();
	}
	else if (cube[2][1] == 'o' && cube[1][1] == 'r' && cube[3][1] == 'b' && cube[5][7] == 'g')
	{
		lastor();
	}
	else if (cube[2][1] == 'g' && cube[1][1] == 'o' && cube[3][1] == 'b' && cube[5][7] == 'r')
	{
		lastbr();
	}
	else if (cube[2][1] == 'g' && cube[1][1] == 'b' && cube[3][1] == 'r' && cube[5][7] == 'o')
	{
		lastbl();
	}
	else if (cube[2][1] == 'r' && cube[1][1] == 'b' && cube[3][1] == 'o' && cube[5][7] == 'g')
	{
		lastrl();
	}
	else if (cube[2][1] == 'b' && cube[1][1] == 'g' && cube[3][1] == 'o' && cube[5][7] == 'r') {
		lastrr();
	}
	else if (cube[1][1] == 'o' && cube[2][1] == 'b' && cube[3][1] == 'r' && cube[5][7] == 'g') {
		lastol();
		lastgl();
	}
	else if (cube[1][1] == 'g' && cube[2][1] == 'r' && cube[3][1] == 'b' && cube[5][7] == 'o') {
		lastor();
		lastgr();
	}
	else if (cube[1][1] == 'b' && cube[2][1] == 'o' && cube[3][1] == 'g' && cube[5][7] == 'r') {
		lastol();
		lastbl();
	}
	else if (cube[1][1] == 'r' && cube[2][1] == 'g' && cube[3][1] == 'o' && cube[5][7] == 'b') {

	}
	else {
		return false;
	}
	return true;
}

void Algo::littlecheck(int& count) {
	for (int j = 0; j < 9; j++) {
		if (cube[0][j] != 'y' || cube[1][j] != 'r' || cube[2][j] != 'g' || cube[3][j] != 'o' || cube[4][j] != 'w' || cube[5][j] != 'b') {
			count++;
			break;
		}
	}
}