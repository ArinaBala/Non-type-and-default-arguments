#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>

// Параметр типа по умолчанию (double)
template <typename TElement = double>
class Array
{
    static int count;
    TElement* _ptr;
    int size;

public:
    Array() : _ptr(new TElement[1]), size(1) 
    {
        ++count;
    }
    Array(int size) : _ptr(new TElement[size]), size(size) 
    { 
        ++count;
    }
    Array(const Array<TElement>& obj);
    Array& operator=(const Array& obj);
    ~Array() { delete[] _ptr; --count; }

    void FillArray(void);
    void PrintArray(void);
    int getSize(void) const { return size; }

    TElement& operator[] (int index) { return (index >= 0 && index < size) ? _ptr[index] : _ptr[0]; }
    const TElement& operator[] (int index) const { return (index >= 0 && index < size) ? _ptr[index] : _ptr[0]; }

    // перегрузки
    Array<TElement>& operator+=(int n);      // увеличить
    Array<TElement>& operator-=(int n);      // уменьшить
    Array<TElement> operator+(int n) const;  // новый объект

    static int GetInstanceCount() { return count; }
};

// Реализации методов
template <typename T>
void Array<T>::FillArray(void)
{
    srand(time(nullptr));
    for (int i = 0; i < size; ++i) _ptr[i] = rand() % 50;
}

template <typename T>
void Array<T>::PrintArray(void)
{
    for (int i = 0; i < size; ++i)
        std::cout << "Array[" << i << "] = " << _ptr[i] << std::endl;
}

template <typename T>
Array<T>::Array(const Array<T>& obj)
{
    size = obj.size;
    _ptr = new T[size];
    for (int i = 0; i < size; ++i) _ptr[i] = obj._ptr[i];
}

template <typename TElement>
Array<TElement>& Array<TElement>::operator=(const Array& obj)
{
    if (this == &obj) return *this;

    size = obj.size;
    delete[] _ptr;
    _ptr = new TElement[size];
    for (int i = 0; i < size; ++i) _ptr[i] = obj._ptr[i];

    ++count;
    return *this;
}

// Сложение двух массивов
template <typename TElement>
Array<TElement> operator+(const Array<TElement>& left, const Array<TElement>& right)
{
    Array<TElement> temp(left.getSize() + right.getSize());
    for (int i = 0; i < left.getSize(); i++) temp[i] = left[i];
    for (int i = 0; i < right.getSize(); i++) temp[i + left.getSize()] = right[i];
    return temp;
}

// Увеличение массива: arr += число
template <typename TElement>
Array<TElement>& Array<TElement>::operator+=(int n)
{
    if (n <= 0) return *this;

    TElement* newArr = new TElement[size + n];
    for (int i = 0; i < size; i++) newArr[i] = _ptr[i];
    for (int i = size; i < size + n; i++) newArr[i] = 0;

    delete[] _ptr;
    _ptr = newArr;
    size += n;
    return *this;
}

// Уменьшение массива: arr -= число
template <typename TElement>
Array<TElement>& Array<TElement>::operator-=(int n)
{
    if (n <= 0 || n >= size) return *this;

    TElement* newArr = new TElement[size - n];
    for (int i = 0; i < size - n; i++) newArr[i] = _ptr[i];

    delete[] _ptr;
    _ptr = newArr;
    size -= n;
    return *this;
}

// Новый объект: rez = arr + число
template <typename TElement>
Array<TElement> Array<TElement>::operator+(int n) const
{
    if (n <= 0) return *this;

    Array<TElement> temp(size + n);
    for (int i = 0; i < size; i++) temp[i] = _ptr[i];
    for (int i = size; i < size + n; i++) temp[i] = 0;
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
