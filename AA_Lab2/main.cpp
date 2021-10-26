#include <iostream>

using namespace std;

#include "Algorithms.h"
#include "tools.h"

int main()
{
    int n = 3;
    mtrx mtrx1, mtrx2, rez;
    mtrxGen(mtrx1, n, n, 5);
    mtrxGen(mtrx2, n, n, 5);
    prepare(rez, n, n, n, n);

    cout << "Matrix 1:" << endl;
    printMtrx(mtrx1, n, n);

    cout << "Matrix 2:" << endl;
    printMtrx(mtrx2, n, n);

    standartMult(rez, mtrx1, n, n, mtrx2, n, n);
    cout << "standartMult Result Matrix:" << endl;
    printMtrx(rez, n, n);

    vinograd(rez, mtrx1, n, n, mtrx2, n, n);
    cout << "vinograd Result Matrix:" << endl;
    printMtrx(rez, n, n);

    optimizedVinograd(rez, mtrx1, n, n, mtrx2, n, n);
    cout << "optimizedVinograd Result Matrix:" << endl;
    printMtrx(rez, n, n);
    return 0;
}
