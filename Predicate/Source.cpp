#include <iostream>
#include<vector>
#include <algorithm>
using namespace std;
bool isless(int n) { //istrue <0
	return n < 0;
}


template< typename T>
class my_buffer {
private:
	size_t buffer_size = 0;
	size_t pos; //флажок на последний добавленный элемент
	T* mas; //сам буффер ввиде динамического массива
public:
	class CustumIterator :public iterator<random_access_iterator_tag, T> { //кастомный итератор
	private:
		T* start; //указатель на начало
	public:
		CustumIterator(T* start_) :  //конструктор
			start(start_)
		{

		}
		CustumIterator(const CustumIterator& it) : //копирования
			start(it.start)
		{

		}
		//перегрузки операторов:
		bool operator!=(CustumIterator const& other) const {
			return start != other.start; //true если не равно
		}
		bool operator==(CustumIterator const& other) const {
			return start == other.start;  //true если равно
		}
		typename CustumIterator::reference operator*() const { //возвращает указатель
			return *start;
		}
		CustumIterator& operator++() {
			++start;
			return *this;
		}
		CustumIterator& operator--() {
			--start;
			return *this;
		}
		CustumIterator operator+(typename std::iterator<std::random_access_iterator_tag, T>::difference_type diff) const { //для работы с stl контейнерами
			return iterator(start + diff);
		}

		CustumIterator operator-(typename std::iterator<std::random_access_iterator_tag, T>::difference_type diff) const { //для работы с stl контейнерами
			return iterator(start - diff);
		}
		size_t operator - (CustumIterator const& other) const {  //разность итераторов
			return this->start - other.start;
		}
		bool operator < (CustumIterator const& other) const {
			return start < other.start;
		}
		bool operator > (CustumIterator const& other) const {
			return start > other.start;
		}
		bool operator >= (CustumIterator const& other) const {
			return start >= other.start;
		}
		bool operator <= (CustumIterator const& other) const {
			return start <= other.start;
		}
		CustumIterator& operator += (const size_t n) { //прибавление константы к итератору
			start += n;
			return *this;
		}
		CustumIterator& operator -= (const size_t n) { //итератор - константа
			start -= n;
			return *this;
		}
		T operator [] (const size_t n) {   //перегрузка оператора индексации
			return *(start + n);
		}
	};
	typedef CustumIterator iterator;
	ring_buffer(size_t size_)   //конструктор от одного аргумента
	{
		buffer_size = size_;
		mas = new T[buffer_size];
		pos = 0;
		for (size_t i = 0; i < buffer_size; i++)
		{
			mas[i] = 0;
		}
	}
	my_buffer(size_t size_, T value) :   //конструктор от двух аргументов
		buffer_size(size_)
	{
		mas = new T[buffer_size];
		pos = 0;
		for (size_t i = 0; i < buffer_size; i++)
		{
			mas[i] = value;
		}
	}
	~my_buffer() {
		delete[] mas;
	}

	void push_back(T v) {
		mas[pos] = v;
		if (pos == (buffer_size - 1)) {
			pos = 0;
		}
		else {
			pos++;
		}
	}
	int  size() {
		return buffer_size;
	}
	void pop_back() {
		mas[buffer_size - 1] = 0;
		pos--;
		buffer_size--;
	}
	void push_front(T v) {
		T* temp_arr = new T[buffer_size];
		temp_arr[0] = v;
		for (size_t i = 1; i < buffer_size; i++)
		{
			temp_arr[i] = mas[i - 1];
		}
		for (size_t i = 0; i < buffer_size; i++)
		{
			mas[i] = temp_arr[i];
		}
	}
	void push_at(const iterator it, T value) {
		T* temp_arr = new T[buffer_size];
		int i;
		for (i = 0; i < buffer_size; i++)
		{
			if (it == &(mas[i])) {
				temp_arr[i] = value;
				break;
			}
			else {
				temp_arr[i] = mas[i];
			}
		}
		i++;
		for (size_t j = i - 1; j < buffer_size; j++)
		{
			if (i == buffer_size) {
				i = 0;
			}
			temp_arr[i] = mas[j];
			i++;
		}
		for (size_t i = 0; i < buffer_size; i++)
		{
			mas[i] = temp_arr[i];
		}

	}
	void pop_at(const iterator it) {
		if (it >= end()) {
			throw invalid_argument("error, out of range");
		}
		T* temp_arr = new T[buffer_size];
		int j = 0;
		for (int i = 0; i < buffer_size; i++)
		{
			if (it == &(mas[j])) {
				j++;
				i--;
			}
			else {
				temp_arr[i] = mas[j];
				j++;
			}
		}
		for (size_t i = 0; i < buffer_size; i++)
		{
			mas[i] = temp_arr[i];
		}
		buffer_size--;

	}
	void pop_front() {
		for (size_t i = 0; i < buffer_size - 1; i++)
		{
			mas[i] = mas[i + 1];
		}
		buffer_size--;
	}
	T get_first() {
		return mas[0];
	}
	T get_last() {
		return mas[buffer_size - 1];
	}
	iterator begin() { //возвращаю итератор начальной позиции
		return iterator(mas);
	}
	iterator end() {  //возвращаю итератор конечной позиции
		return iterator(&(mas[buffer_size]));
	}
	const T operator [](size_t N) {
		if (N >= buffer_size) {
			throw invalid_argument("error, out of range");
		}
		else {
			return  mas[N];
		}
	}
	void resize(size_t n) {
		if (n < buffer_size) {
			throw  invalid_argument("error, cannot be reduced");
		}
		else {
			T* new_arr = new T[n];
			for (int i = 0; i < n; i++)
			{
				new_arr[i] = mas[i];
			}
			pos = buffer_size;
			buffer_size = n;
			mas = new_arr;
		}
	}
};



void print(my_buffer<int>& ring) { //вывод содержимого через пробел
	for (size_t i = 0; i < ring.size(); i++)
	{
		cout << ring[i] << " ";
	}
	cout << endl;
}

int main() {
}