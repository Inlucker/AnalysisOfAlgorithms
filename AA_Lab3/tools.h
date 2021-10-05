#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <Windows.h>
#include <random>
#include <ctime>

using namespace std;

#include "Algorithms.h"

typedef void (*SortPtr)(int*, int*);

double getCPUTime();

void getCPUTimeOfAlg(SortPtr alg, int length, int iterations, string alg_name = "Algorithm");

void getBubbleSortTimes();
void getSelectionSortTimes();
void getInsertionSortTimes();

void genMas(int size, int *mas);

#endif // TOOLS_H
