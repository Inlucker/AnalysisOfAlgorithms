#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <Windows.h>
#include <random>
#include <ctime>

using namespace std;

#include "Algorithms.h"

typedef int (*AlgPtr)(mtrx&, mtrx, int, int, mtrx, int, int);
//typedef void (*GenPtr)(int, int*);

double getCPUTime();

void getCPUTimeOfAlg(AlgPtr alg, int size, int iterations, string alg_name = "Algorithm");

void getStandartTimes();
void getVinogradTimes();
void getOptimizedVinogradTimes();

void getStandartTimesWorst();
void getVinogradTimesWorst();
void getOptimizedVinogradTimesWorst();

void mtrxGen(mtrx &rez, int n, int m, int lim);
int prepare(mtrx &result, int n1, int m1, int n2, int m2);
void printMtrx(mtrx mtr, int n, int m);

#endif // TOOLS_H
