#include <iostream>
#include <random>
#include <ctime>

using namespace std;

#include "Algorithms.h"
#include "tools.h"

#define N 30

void printMas(const int *mas, int size);

int main()
{
    int mas[N];
    srand(time(0));
    for (int i = 0; i < N; i++)
        mas[i] = rand() % 100;
        //mas[i] = N-i;

    cout << "Array:" << endl;
    printMas(mas, N);

    int tmp[N];
    for (int i = 0; i < N; i++)
        tmp[i] = mas[i];
    BubbleSort(&tmp[0], &tmp[N-1]);
    cout << "BubbleSort:" << endl;
    printMas(tmp, N);

    for (int i = 0; i < N; i++)
        tmp[i] = mas[i];
    SelectionSort(&tmp[0], &tmp[N-1]);
    cout << "SelectionSort:" << endl;
    printMas(tmp, N);

    for (int i = 0; i < N; i++)
        tmp[i] = mas[i];
    InsertionSort(&tmp[0], &tmp[N-1]);
    cout << "InsertionSort:" << endl;
    printMas(tmp, N);

    //Трудоёмкость
    //cout << getBubbleSort(&mas[0], &mas[N-1]) << endl;
    //cout << getBubblesort2(&mas[0], &mas[N]) << endl;
    //cout << getSelectionSort(&mas[0], &mas[N-1]) << endl;
    //cout << getInsertionSort(&mas[0], &mas[N-1]) << endl;

    getBubbleSortTimes(&genMasRandom);
    getSelectionSortTimes(&genMasRandom);
    getInsertionSortTimes(&genMasRandom);

    return 0;
}

void printMas(const int *mas, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << mas[i] << " ";
    }
    cout << endl;
}
