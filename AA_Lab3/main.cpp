#include <iostream>
#include <random>
#include <ctime>

using namespace std;

#include "Algorithms.h"
#include "tools.h"

#define N 30

void printMas(const int *mas, int size);

void funcTests()
{
    int n = 1;
    int mas1[1] = {10};
    cout << "mas1 = ";
    printMas(mas1, 1);
    BubbleSort(&mas1[0], &mas1[n-1]);
    cout << "sorted1 by BubbleSort = ";
    printMas(mas1, 1);
    bool flag = true;
    if (mas1[0] != 10)
        flag = false;
    if (flag)
        cout << "BbubleSort() with mas1 is correct!" << endl;
    else
        cout << "BbubleSort() with mas1 is NOT correct!" << endl;

    SelectionSort(&mas1[0], &mas1[n-1]);
    cout << "sorted1 by SelectionSort = ";
    printMas(mas1, 1);
    flag = true;
    if (mas1[0] != 10)
        flag = false;
    if (flag)
        cout << "SelectionSort() with mas1 is correct!" << endl;
    else
        cout << "SelectionSort() with mas1 is NOT correct!" << endl;

    InsertionSort(&mas1[0], &mas1[n-1]);
    cout << "sorted1 by InsertionSort = ";
    printMas(mas1, 1);
    flag = true;
    if (mas1[0] != 10)
        flag = false;
    if (flag)
        cout << "SelectionSort() with mas1 is correct!" << endl;
    else
        cout << "SelectionSort() with mas1 is NOT correct!" << endl;

    n = 10;
    int mas10[10] = {10,7,9,5,3,1,8,2,4,6};
    cout << "mas10 = ";
    printMas(mas10, 10);
    BubbleSort(&mas10[0], &mas10[n-1]);
    cout << "sorted10 by BubbleSort = ";
    printMas(mas10, 10);
    flag = true;
    for (int i = 0; i < 10; i++)
        if (mas10[i] != i+1)
            flag = false;
    if (flag)
        cout << "BbubleSort() with mas10 is correct!" << endl;
    else
        cout << "BbubleSort() with mas10 is NOT correct!" << endl;

    int mas10_2[10] = {10,7,9,5,3,1,8,2,4,6};
    SelectionSort(&mas10_2[0], &mas10_2[n-1]);
    cout << "sorted10 by SelectionSort = ";
    printMas(mas10, 10);
    flag = true;
    for (int i = 0; i < 10; i++)
        if (mas10_2[i] != i+1)
            flag = false;
    if (flag)
        cout << "SelectionSort() with mas10 is correct!" << endl;
    else
        cout << "SelectionSort() with mas10 is NOT correct!" << endl;

    int mas10_3[10] = {10,7,9,5,3,1,8,2,4,6};
    InsertionSort(&mas10_3[0], &mas10_3[n-1]);
    cout << "sorted10 by InsertionSort = ";
    printMas(mas10, 10);
    flag = true;
    for (int i = 0; i < 10; i++)
        if (mas10_3[i] != i+1)
            flag = false;
    if (flag)
        cout << "InsertionSort() with mas10 is correct!" << endl;
    else
        cout << "InsertionSort() with mas10 is NOT correct!" << endl;
}

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

    //getBubbleSortTimes(&genMasRandom);
    //getBubbleSortTimes(&genMasBest);
    //getBubbleSortTimes(&genMasWorst);
    //getBubbleSortTimes(&genMasRandom);
    //getSelectionSortTimes(&genMasRandom);
    //getInsertionSortTimes(&genMasRandom);\

    funcTests();

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
