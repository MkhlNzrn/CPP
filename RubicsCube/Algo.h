#pragma once
#include "Cube.h"


class Algo : public Cube {

public:

	bool Check();
	bool find(bool b, int count);
	void checkmas(int* mas, unsigned char c);
	bool checkcol(unsigned char a, unsigned char b);
	bool checkcen(vector<unsigned char>& cen, unsigned char a, bool flag, int* mas);
	bool checkreb(vector<pair<unsigned char, unsigned char>>& reb, unsigned char a, unsigned char b, bool flag, int* mas);
	bool checkcor(vector<pair<unsigned char, pair<unsigned char, unsigned char>>>& cor, unsigned char a, unsigned char b, unsigned char c, bool flag, int* mas);
	void goodw(int a);
	void findkrest();
	void krest();
	int count_edge_krest();
	void edgekrest();
	void cornerwhile(int var);
	void R6perebor();
	void G6perebor();
	void O6perebor();
	void B6perebor();
	void find_corner();
	void Bedge();
	void Redge();
	void Gedge();
	void Oedge();
	void find_edge();
	void firstsloi();
	void secondsloi();
	void ykrestG(int count);
	void ykrestR(int count);
	bool ykrest();
	void vertolet();
	void ushki();
	void nos();
	void glazki();
	void triplpifpaf();
	void Rriba();
	void Lriba();
	bool ycor();
	void notpair();
	void lastcor();
	void lastgl();
	void lastgr();
	void lastol();
	void lastor();
	void lastbl();
	void lastbr();
	void lastrl();
	void lastrr();
	bool lastedge();
	void littlecheck(int& count);
	void havepair();
};