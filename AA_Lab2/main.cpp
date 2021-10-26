#include <iostream>

using namespace std;

#include "Algorithms.h"
#include "tools.h"

void funcTests();

int main()
{
    int n = 300;
    mtrx mtrx1, mtrx2, rez;
    mtrxGen(mtrx1, n, n, 5);
    mtrxGen(mtrx2, n, n, 5);
    prepare(rez, n, n, n, n);

    int t = standartMultCalc(rez, mtrx1, n, n, mtrx2, n, n);
    cout << t << endl;
    t = vinogradCalc(rez, mtrx1, n, n, mtrx2, n, n);
    cout << t << endl;
    t = optimizedVinogradCalc(rez, mtrx1, n, n, mtrx2, n, n);
    cout << t << endl;


    /*int n = 3;
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
    printMtrx(rez, n, n);*/

    //funcTests();

    /*getStandartTimes();
    getVinogradTimes();
    getOptimizedVinogradTimes();

    getStandartTimesWorst();
    getVinogradTimesWorst();
    getOptimizedVinogradTimesWorst();*/

    return 0;
}

void setRez1(mtrx &rez)
{
    prepare(rez, 3, 3, 3, 3);
    int k = 1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            rez[i][j] = k++;
}

void setMtrx1_2(mtrx &rez)
{
    prepare(rez, 3, 3, 3, 3);
    rez[0][0] = 1;
    rez[1][1] = 1;
    rez[2][2] = 1;
}

void setRez2(mtrx &rez)
{
    prepare(rez, 3, 3, 3, 3);
    rez[0][0] = 10;
    rez[0][1] = 4;
    rez[0][2] = 10;
    rez[1][0] = 8;
    rez[1][1] = 8;
    rez[1][2] = 12;
    rez[2][0] = 17;
    rez[2][1] = 6;
    rez[2][2] = 7;
}

bool checkMtrxs(mtrx mtrx1, int n1, int m1, mtrx mtrx2, int n2, int m2)
{
    if (n1 != n2 || m1 != m2)
        return false;

    for (int i = 0; i < n1; i++)
        for (int j = 0; j < m1; j++)
            if (mtrx1[i][j] != mtrx2[i][j])
                return false;

    return true;
}

void funcTests()
{
    //Preporation
    int pos_tests = 0;
    int neg_tests = 0;
    int n = 3;
    mtrx mtrx1, mtrx2, rez, exp_rez;

    //Test1
    setRez1(mtrx1);
    setMtrx1_2(mtrx2);
    prepare(rez, n, n, n, n);
    setRez1(exp_rez);

    cout << "Matrix 1:" << endl;
    printMtrx(mtrx1, n, n);

    cout << "Matrix 2:" << endl;
    printMtrx(mtrx2, n, n);

    cout << "Expected result:" << endl;
    printMtrx(exp_rez, n, n);

    standartMult(rez, mtrx1, n, n, mtrx2, n, n);
    cout << "standartMult Result Matrix:" << endl;
    printMtrx(rez, n, n);
    if (checkMtrxs(rez, n, n, exp_rez, n, n))
        pos_tests++;
    else
        neg_tests++;

    vinograd(rez, mtrx1, n, n, mtrx2, n, n);
    cout << "vinograd Result Matrix:" << endl;
    printMtrx(rez, n, n);
    if (checkMtrxs(rez, n, n, exp_rez, n, n))
        pos_tests++;
    else
        neg_tests++;

    optimizedVinograd(rez, mtrx1, n, n, mtrx2, n, n);
    cout << "optimizedVinograd Result Matrix:" << endl;
    printMtrx(rez, n, n);
    if (checkMtrxs(rez, n, n, exp_rez, n, n))
        pos_tests++;
    else
        neg_tests++;

    //Test2
    mtrxGen(mtrx1, n, n, 5);
    mtrxGen(mtrx2, n, n, 5);
    prepare(rez, n, n, n, n);
    setRez2(exp_rez);

    cout << "Matrix 1:" << endl;
    printMtrx(mtrx1, n, n);

    cout << "Matrix 2:" << endl;
    printMtrx(mtrx2, n, n);

    cout << "Expected result:" << endl;
    printMtrx(exp_rez, n, n);

    standartMult(rez, mtrx1, n, n, mtrx2, n, n);
    cout << "standartMult Result Matrix:" << endl;
    printMtrx(rez, n, n);
    if (checkMtrxs(rez, n, n, exp_rez, n, n))
        pos_tests++;
    else
        neg_tests++;

    vinograd(rez, mtrx1, n, n, mtrx2, n, n);
    cout << "vinograd Result Matrix:" << endl;
    printMtrx(rez, n, n);
    if (checkMtrxs(rez, n, n, exp_rez, n, n))
        pos_tests++;
    else
        neg_tests++;

    optimizedVinograd(rez, mtrx1, n, n, mtrx2, n, n);
    cout << "optimizedVinograd Result Matrix:" << endl;
    printMtrx(rez, n, n);
    if (checkMtrxs(rez, n, n, exp_rez, n, n))
        pos_tests++;
    else
        neg_tests++;

   //Test results
   cout << pos_tests << "/" << pos_tests+neg_tests << " positive tests" << endl;
}
