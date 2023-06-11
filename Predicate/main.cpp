#include "predicate.h"
#include <iostream>
#include <sstream>
#include <assert.h>
#include <vector>
#include <set>
#include <iterator>
#include <functional>


using namespace std;

int main() {
	set<int> s{ 1, 2, 3 };
	cout << isPalindrome(s.begin(), s.end(), [](int x, int y) {return x + y > 0; });
}