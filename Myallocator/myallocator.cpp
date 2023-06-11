#include <iostream>
#include "myallocator.h"
#include <vector>
#include <list>
#include <map>
int main() {

    std::allocator_traits<allocator<int>> allocatorTraits;
    allocator<int> allocator1;

    std::vector<int, allocator<int>> vector(10, -1, allocator1);
    vector.push_back(10);

    std::list<int, allocator<int>> list;
    list.resize(10);
    list.push_back(100);

    std::map<int, int, std::less<int>, allocator<int>> mapa;
    mapa[1] = 1;
    mapa[436] = 26;
    mapa[223523] = 32534637;

    int *pInt = allocator1.allocate(10);
    for (auto i = 0; i < 10; i++) {
        pInt[i] = i;
    }

    allocator1.deallocate(pInt, 10);

    return 0;
}
