#include <iostream>
#include <random>
#include <ctime>

using namespace std;

#include "Algorithms.h"

#define N 10

void printMas(const int *mas, int size);

int main()
{
    int mas[N];
    srand(time(0));
    for (int i = 0; i < N; i++)
        mas[i] = rand() % 100;
        //mas[i] = N-i;

    printMas(mas, N);

    //cout << getBubbleSort(&mas[0], &mas[N-1]) << endl;
    //cout << getBubblesort2(&mas[0], &mas[N]) << endl;
    cout << getSelectionSort(&mas[0], &mas[N-1]) << endl;

    //SelectionSort(&mas[0], &mas[N-1]);

    printMas(mas, N);
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
