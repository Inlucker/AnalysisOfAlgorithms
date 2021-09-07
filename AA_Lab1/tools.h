#ifndef TOOLS_H
#define TOOL

#include <Windows.h>
#include "Algorithms.h"
#include <random>

using namespace std;

#define ITERATIONS_REC_CASH 1000
#define ITERATIONS_REC 250
#define ITERATIONS_MATRIX 50000

double getCPUTime();

void getCPUTimeOfAlg(AlgPtr alg, string str1, string str2, int iterations, string alg_name = "Algorithm");

void getCPUTimeOfAlg(AlgPtr alg, size_t length, int iterations, string alg_name = "Algorithm");

void getLevLenTimes();
void getLevLenRecTimes();
void getLevLenRecCashTimes();
void getDamLevLenRecTimes();

string genStr(size_t size);

#endif // TOOLS_H
