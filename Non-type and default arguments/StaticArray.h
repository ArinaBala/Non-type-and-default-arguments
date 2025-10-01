#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>

// SIZE - это нетиповой аргумент шаблона
// При инстанцировании шаблона можно передать ему в качестве аргумента \
     целочисленное, константное значение, которое будет использовано,\
     например для указания размера массива

// Вместо SIZE будет подставлено непосредственно числовое значение
// В данном примере SIZE является так же параметром шаблона по-умолчанию, \
    но это совсем не обязательно


    template <typename TElement = int, int SIZE = 10>
class StaticArray
{
    TElement arr[SIZE];
public:
    StaticArray() : arr() {}


    void FillArray(void);
    void PrintArray(void);

    int getSize(void) const 
    { 
        return SIZE;
    }

    TElement& operator[] (int index) 
    {
        return index >= 0 && index < SIZE ? arr[index] : arr[0]; 
    }
    const TElement& operator[] (int index) const 
    {
        return index >= 0 && index < SIZE ? arr[index] : arr[0];
    }
};

template <typename T, int SIZE>
void StaticArray<T, SIZE>::FillArray(void)
{
    srand(time(nullptr));

    for (int i = 0; i < SIZE; ++i)
    {
        arr[i] = rand() % 50;
    }
}

template <typename T, int SIZE>
void StaticArray<T, SIZE>::PrintArray(void)
{
    using std::cout;
    using std::endl;

    for (int i = 0; i < SIZE; ++i)
    {
        cout << "Array[" << i << "] = " << arr[i];
    }
}