#pragma once

#include <functional>
#include <iostream>
using namespace std;

template<class InputIterator, class UnaryPredicate>
bool allOf(InputIterator begin, InputIterator end, UnaryPredicate predicate)   //true ��� ������� ���������� ������� ��� ���� ��������� ���������
{
	while (begin != end) {
		if (!predicate(*begin)) return false;
		++begin;
	}
	return true;
}

template<class InputIterator, class UnaryPredicate>					//true ��� ������� ���������� ������� ���� �� ��� ������
bool anyOf(InputIterator begin, InputIterator end, UnaryPredicate predicate)
{
	while (begin != end) {
		if (predicate(*begin)) return true;
		++begin;
	}
	return false;
}

template<class InputIterator, class UnaryPredicate>		//true ��� ������� �� ���������� ������� �� ��� ������
bool noneOf(InputIterator begin, InputIterator end, UnaryPredicate predicate)
{
	while (begin != end) {
		if (predicate(*begin)) return false;
		++begin;
	}
	return true;
}

template<class InputIterator, class UnaryPredicate>    //true ��� ������� ���������� ������� ������ ��� ������
bool oneOf(InputIterator begin, InputIterator end, UnaryPredicate predicate)
{
	bool flag = false;
	while (begin != end) {
		if (predicate(*begin)) {
			if (flag) {
				return !flag;
			}
			else {
				flag = true;
			}
		}
		++begin;
	}
	return flag;
}

template <class ForwardIt, class Compare = std::less<>> //�������� �� ����������������� �� �������� � ��������
bool isSorted(ForwardIt begin, ForwardIt end, Compare compare = std::less<>())
{
	if (begin != end) {
		ForwardIt next = begin;
		while (++next != end) {
			if (compare(*next, *begin))
				return next == end;
			begin = next;
		}
	}
	return true;
}

template <class InputIterator, class UnaryPredicate> //��������� ���� �� �������� �� �������� ��� �������� ������������� ���� �� ������������� ���������, � ����� �������� ��������
bool isPartitioned(InputIterator begin, InputIterator end, UnaryPredicate predicate)
{
	while (begin != end && predicate(*begin)) {
		++begin;
	}
	while (begin != end) {
		if (predicate(*begin)) return false;
		++begin;
	}
	return true;
}

template<class InputIterator, class T>  //���������� ������ �� ������ ��������� �������
InputIterator findNot(InputIterator begin, InputIterator end, const T& value)
{
	while (begin != end) {
		if (*begin != value) return begin;
		++begin;
	}
	return end;
}

template<class InputIt, class T>   //���������� ������ ������ ��������� ������� � �����
constexpr InputIt findBackward(InputIt begin, InputIt end, const T& value)
{
	InputIt res = end;
	for (; begin != end; ++begin) {
		if (*begin == value) {
			res = begin;
		}
	}
	return res;
}

template<class InputIterator, class UnaryPredicate> //���������� true ���� ������������������ � ��� ������� �������� ���������
bool isPalindrome(InputIterator begin, InputIterator end, UnaryPredicate predicate)
{
	int len = 0;
	for (InputIterator it = begin; it != end; it++) {
		len++;
	}
	for (int i = 0; begin != end; begin++, i++) {
		InputIterator it = begin;
		for (int j = i; j < len - i - 1; j++) {
			it++;
		}
		if (!predicate(*begin, *it)) {
			return false;
		}
	}
	return true;
}