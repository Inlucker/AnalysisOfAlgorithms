#ifndef TOOLS_H
#define TOOL

#include <Windows.h>
#include "Algorithms.h"

double getCPUTime();

void getCPUTimeOfAlg(AlgPtr alg, string str1, string str2, int iterations, string alg_name = "Algorithm");

#endif // TOOLS_H
