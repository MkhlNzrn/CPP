#pragma once
#include <vector>
#include <iostream>

struct chunk {
    uint8_t * memory;
    int size;
    bool isFree;
};

template <class Type>
class allocator {
public:
    typedef size_t     size_type;
    typedef ptrdiff_t  difference_type;
    typedef Type*       pointer;
    typedef const Type* const_pointer;
    typedef Type&       reference;
    typedef const Type& const_reference;
    typedef Type        value_type;

    allocator();
    template<class ...arguments>  //нужно для параметр пак
    explicit allocator(arguments ...args);
    template<class Tp>
    allocator(const allocator<Tp> & other) : chunks(other.chunks) {} //хули собственно не компилимся
    ~allocator() = default;
    Type* allocate(size_t n);
    void deallocate(Type * ptr, size_t n) noexcept;
    std::vector<chunk> chunks;
private:
    const int memory_limit = 1000000000; // 1GB
    void stupid_bubble_sort(int * arr, int n);
};

template<class Type>
allocator<Type>::allocator() {
    int n = 100;
    chunks = std::vector<chunk>(n);
    for (int i = 0; i < n; i++) {
        int size = 10000000;
        chunks[i].size = size;
        chunks[i].isFree = true;
        chunks[i].memory = new uint8_t[size];
    }
}

template<class Type>
template<class... arguments>
allocator<Type>::allocator(arguments... args) {
    int n = sizeof...(args);
    int sum = 0;
    int sizes[]{ args... };
    chunks = std::vector<chunk>(n);
    stupid_bubble_sort(sizes, n);
    for (int i = 0; i < n; i++) {
        sum += sizes[i];
        chunks[i].size = sizes[i];
    }
    if (sum > memory_limit) {
        throw std::runtime_error("Allocator failed\n");
    }
    else {
        for (int i = 0; i < n; i++) {
            chunks[i].memory = new uint8_t[sizes[i]];
            chunks[i].isFree = true;
        }
    }
}

template<class Type>
Type *allocator<Type>::allocate(size_t n) {
    for (auto & item : chunks) {
        if (item.size >= n * sizeof(Type) and item.isFree) {
            item.isFree = false;
            return (Type*)item.memory;
        }
    }
    throw std::runtime_error("Bad allocation\n");
}

template<class Type>
void allocator<Type>::deallocate(Type *ptr, size_t n) noexcept{
    for (auto item : chunks) {
        if ((Type*)item.memory == ptr) {
            item.isFree = true;
            return;
        }
    }
}

template<class Type>//шаблонный класс
void allocator<Type>::stupid_bubble_sort(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i] < arr[j]) {
                std::swap(arr[i], arr[j]);
            }
        }
    }
}

