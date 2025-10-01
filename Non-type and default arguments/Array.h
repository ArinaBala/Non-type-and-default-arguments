#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>

template <typename TElement = double>
class Array
{
    static int count;
    TElement* _ptr;
    int size;

public:
    Array() : _ptr(new TElement[1]), size(1) { ++count; }
    Array(int sz) : _ptr(new TElement[sz]), size(sz) { ++count; }
    Array(const Array<TElement>& other);
    Array& operator=(const Array& other);
    ~Array() { delete[] _ptr; --count; }

    void FillArray();
    void PrintArray() const;
    int getSize() const { return size; }

    TElement& operator[](int index) { return (index >= 0 && index < size) ? _ptr[index] : _ptr[0]; }
    const TElement& operator[](int index) const { return (index >= 0 && index < size) ? _ptr[index] : _ptr[0]; }

    Array<TElement>& operator+=(int n);
    Array<TElement>& operator-=(int n);
    Array<TElement> operator+(int n) const;

    static int GetInstanceCount() { return count; }
};

// Реализации

template <typename T>
void Array<T>::FillArray()
{
    srand(time(nullptr));
    for (int i = 0; i < size; ++i) _ptr[i] = rand() % 50;
}

template <typename T>
void Array<T>::PrintArray() const
{
    for (int i = 0; i < size; ++i) std::cout << "Array[" << i << "] = " << _ptr[i] << std::endl;
}

template <typename T>
Array<T>::Array(const Array<T>& other)
{
    size = other.size;
    _ptr = new T[size];
    for (int i = 0; i < size; ++i) _ptr[i] = other._ptr[i];
}

template <typename TElement>
Array<TElement>& Array<TElement>::operator=(const Array& other)
{
    if (this == &other) return *this;

    size = other.size;
    delete[] _ptr;
    _ptr = new TElement[size];
    for (int i = 0; i < size; ++i) _ptr[i] = other._ptr[i];

    ++count;
    return *this;
}

// Сложение двух массивов
template <typename TElement>
Array<TElement> operator+(const Array<TElement>& left, const Array<TElement>& right)
{
    Array<TElement> temp(left.getSize() + right.getSize());
    for (int i = 0; i < left.getSize(); i++) temp[i] = left[i];
    for (int j = 0; j < right.getSize(); j++) temp[j + left.getSize()] = right[j];
    return temp;
}

// Увеличение массива
template <typename TElement>
Array<TElement>& Array<TElement>::operator+=(int n)
{
    TElement* newArr = new TElement[size + n];
    for (int i = 0; i < size; i++) newArr[i] = _ptr[i];
    for (int j = size; j < size + n; j++) newArr[j] = 0;

    delete[] _ptr;
    _ptr = newArr;
    size += n;
    return *this;
}

// Уменьшение массива
template <typename TElement>
Array<TElement>& Array<TElement>::operator-=(int n)
{
    if (n >= size) n = size - 1;

    TElement* newArr = new TElement[size - n];
    for (int i = 0; i < size - n; i++) newArr[i] = _ptr[i];

    delete[] _ptr;
    _ptr = newArr;
    size -= n;
    return *this;
}

// Новый объект
template <typename TElement>
Array<TElement> Array<TElement>::operator+(int n) const
{
    Array<TElement> temp(size + n);
    for (int i = 0; i < size; i++) temp[i] = _ptr[i];
    for (int j = size; j < size + n; j++) temp[j] = 0;
    return temp;
}

// Перегрузка вывода
template <typename TElement>
std::ostream& operator<<(std::ostream& os, const Array<TElement>& arr)
{
    for (int i = 0; i < arr.getSize(); i++) os << arr[i] << " ";
    return os;
}

// Статическое поле
template <typename TInner>
int Array<TInner>::count;

template <>
int Array<double>::count = -1;
