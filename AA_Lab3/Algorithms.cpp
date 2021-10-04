#include "Algorithms.h"

void swap(int *el1, int *el2)
{
    int temp = *el1;
    *el1 = *el2;
    *el2 = temp;
}

/*#include <iostream>

using namespace std;

void printMas(int *mas, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << mas[i] << " ";
    }
    cout << endl;
}*/

void BubbleSort(int *l, int *r)
{
    for (int i = 0; i < r-l; i++)
    {
        for (int *j = l; j < r-i; j++)
        {
            if (*j > *(j+1))
                swap(j, (j+1));
        }
        //printMas(l, r-l+1);
    }
}


int getBubbleSort(int *l, int *r)
{
    int rez = 3; //init+srav
    for (int i = 0; i < r-l; i++)
    {
        rez += 3; //init+srav
        for (int *j = l; j < r-i; j++)
        {
            if (*j > *(j+1))
                swap(j, (j+1));
            rez+=5; //telo j
            rez++; //increment
            rez+=2; //srav
        }
        rez++; //increment
        rez+=2; //srav
    }
    return rez;
}

/*int getBubbleSort2(int* l, int* r)
{
    int rez = 3; //init+srav
    for (int* j = r; j > l + 1; j--)
    {
        rez += 3; //init+srav
        for (int* i = l; i < j - 1; i++)
        {
            if (*i > *(i + 1))
            {
                swap(i, (i + 1));
            }
            rez+=5; //telo
            rez++; //increment
            rez+=2; //srav
        }
        rez++; //increment
        rez+=2; //srav
    }
    return rez;
}*/

void SelectionSort(int *l, int *r)
{
    for (int *i = l; i <= r; i++)
    {
        int minz = *i, *ind = i;
        for (int *j = i + 1; j <= r; j++)
        {
            if (*j < minz)
            {
                minz = *j;
                ind = j;
            }
        }
        swap(i, ind);
    }
}

int getSelectionSort(int *l, int *r)
{
    int rez = 2; //init+srav
    for (int *i = l; i <= r; i++)
    {
        rez += 2; //double = (assignment)
        int minz = *i, *ind = i;
        rez += 3; //init+srav
        for (int *j = i + 1; j <= r; j++)
        {
            if (*j < minz)
            {
                minz = *j;
                ind = j;
            }
            rez += 3; //telo j
            rez++; //increment
            rez++; //srav
        }
        swap(i, ind);
        rez+=3; //swap
        rez++; //increment
        rez++; //srav
    }
    return rez;
}
