#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>

using namespace std;

typedef vector<vector<int>> mtrx;

#define SIZE_ERROR 1;

int standartMult(mtrx &rez, mtrx mtrx1, int n1, int m1, mtrx mtrx2, int n2, int m2);

int vinograd(mtrx &rez, mtrx mtrx1, int n1, int m1, mtrx mtrx2, int n2, int m2);

int optimizedVinograd(mtrx &rez, mtrx mtrx1, int n1, int m1, mtrx mtrx2, int n2, int m2);

#endif // ALGORITHMS_H
