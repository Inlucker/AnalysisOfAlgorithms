#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <Windows.h>
#include <random>
#include <ctime>

using namespace std;

#include "Algorithms.h"

typedef void (*SortPtr)(int*, int*);
typedef void (*GenPtr)(int, int*);

double getCPUTime();

void getCPUTimeOfAlg(SortPtr alg, GenPtr gen, int length, int iterations, string alg_name = "Algorithm");

void getBubbleSortTimes(GenPtr gen);
void getSelectionSortTimes(GenPtr gen);
void getInsertionSortTimes(GenPtr gen);

void genMasRandom(int size, int *mas);
void genMasWorst(int size, int *mas);
void genMasBest(int size, int *mas);

#endif // TOOLS_H
