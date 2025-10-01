#include <iostream>
#include "Array.h"
using namespace std;

int main()
{
    Array<int> arr1(5);
    arr1.FillArray();
    cout << "arr1: " << arr1 << endl;

    Array<int> arr2(3);
    arr2.FillArray();
    cout << "arr2: " << arr2 << endl;

    // arr1 + arr2
    Array<int> rez = arr1 + arr2;
    cout << "rez = arr1 + arr2: " << rez << endl;

    // arr1 += 5
    arr1 += 5;
    cout << "arr1 += 5: " << arr1 << endl;

    // arr1 -= 2
    arr1 -= 2;
    cout << "arr1 -= 2: " << arr1 << endl;

    // rez = arr1 + 5
    rez = arr1 + 5;
    cout << "rez = arr1 + 5: " << rez << endl;

    system("pause");
    return 0;
}
