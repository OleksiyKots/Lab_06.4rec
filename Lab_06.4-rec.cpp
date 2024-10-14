#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;

void create(int* arr, int SIZE, int MIN, int MAX, int i)
{
    if (i < SIZE)
    {
        arr[i] = MIN + rand() % (MAX - MIN + 1);
        create(arr, SIZE, MIN, MAX, ++i);
    }
}

void Print(int* arr, const int SIZE, int i)
{
    cout << setw(4) << arr[i];
    if (i < SIZE - 1)
        Print(arr, SIZE, i + 1);
    else
        cout << endl;
}

int count(int* arr, int SIZE, int C, int i = 0)
{
    if (i < SIZE)
    {
        return (arr[i] > C ? 1 : 0) + count(arr, SIZE, C, i + 1);
    }
    return 0;
}

double mult(int* arr, int SIZE, int maxIndex, double mul = 1.0, int i = 0) {
    if (i < SIZE) {
        if (i > maxIndex) {
            mul *= arr[i];
        }
        return mult(arr, SIZE, maxIndex, mul, i + 1);
    }
    return mul;
}

int findMaxIndex(int* arr, const int size, int maxIndex = 0, int j = 1)
{
    if (j < size) {
        if (abs(arr[j]) > abs(arr[maxIndex])) {
            maxIndex = j;
        }
        return findMaxIndex(arr, size, maxIndex, j + 1);
    }
    return maxIndex;
}

void recursiveSort(int* arr, int* temp, int size, int i, int& negIndex) {
    if (i < size) {
        if (arr[i] < 0) {
            temp[negIndex++] = arr[i];
        }
        recursiveSort(arr, temp, size, i + 1, negIndex);
    }
}

void fillPositive(int* arr, int* temp, int size, int i, int negIndex) {
    if (i < size) {
        if (arr[i] >= 0) {
            temp[negIndex++] = arr[i];
        }
        fillPositive(arr, temp, size, i + 1, negIndex);
    }
}

void copyToOriginal(int* arr, int* temp, int size, int i) {
    if (i < size) {
        arr[i] = temp[i];
        copyToOriginal(arr, temp, size, i + 1);
    }
}

void Sort(int* arr, const int size) {
    int* temp = new int[size];
    int negIndex = 0;

    recursiveSort(arr, temp, size, 0, negIndex);

    int posIndex = negIndex;
    fillPositive(arr, temp, size, 0, posIndex);

    copyToOriginal(arr, temp, size, 0);

    delete[] temp;
}


int main()
{
    srand((unsigned)time(NULL));

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int SIZE;
    int MIN = -10;
    int MAX = 10;
    double C;

    cout << "Введіть значення C: ";
    cin >> C;

    cout << "Введіть розмір масиву: ";
    cin >> SIZE;

    int* arr = new int[SIZE];

    create(arr, SIZE, MIN, MAX, 0);
    cout << "Сгенерований масив: ";
    Print(arr, SIZE, 0);
    cout << endl;

    int countGreater = count(arr, SIZE, C);
    cout << "Кількість елементів, більших за " << C << ": " << countGreater << endl;

    int maxIndex = findMaxIndex(arr, SIZE);
    cout << "Добуток елементів масиву після максимального за модулем елементу: " << mult(arr, SIZE, maxIndex) << endl;

    Sort(arr, SIZE);
    cout << "Відсортований масив: ";
    Print(arr, SIZE, 0);

    delete[] arr;
    return 0;
}
