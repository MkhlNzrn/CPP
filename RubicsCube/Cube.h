#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Cube {
public:
	Cube();
	void Save();
	void Read();
	bool Check();
	void Show();
	void RandomSpin();
	void setString();

	void getString();


	~Cube();
	void Right(int turn);
	void Left(int turn);
	void UR();
	void UL();
	void LR();
	void LL();
	void FR();
	void FL();
	void RR();
	void RL();
	void DR();
	void DL();
	void BR();
	void BL();

	unsigned char** return_cube() {
		return cube;
	}


protected:
	string str;
	unsigned char** cube;



};