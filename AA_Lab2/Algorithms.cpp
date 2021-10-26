#include "Algorithms.h"

int standartMult(mtrx &rez, mtrx mtrx1, int n1, int m1, mtrx mtrx2, int n2, int m2)
{
    if (m1 != n2)
        return SIZE_ERROR;

    for (int i = 0; i < n1; i++)
       for (int j = 0; j < m2; j++)
       {
           rez[i][j] = 0;
           for (int k = 0; k < n2; k++)
               rez[i][j] = rez[i][j] + mtrx1[i][k] * mtrx2[k][j];
       }
    return 0;
}

int standartMultCalc(mtrx &rez, mtrx mtrx1, int n1, int m1, mtrx mtrx2, int n2, int m2)
{
    int t = 1; // check if !=
    if (m1 != n2)
        return SIZE_ERROR;

    t += 1 + 1; // for i prep
    for (int i = 0; i < n1; i++)
    {
        t += 1 + 1; // for j prep
        for (int j = 0; j < m2; j++)
        {
            t += 1 + 1 + 1; // [][]=
            rez[i][j] = 0;
            t += 1 + 1; // for k prep
            for (int k = 0; k < n2; k++)
            {
                t += 2 + 1 + 2 + 1 + 2 + 2 + 2; // [][] = [][] + [][] * [][]
                rez[i][j] = rez[i][j] + mtrx1[i][k] * mtrx2[k][j];
                t += 2; //inc + check
            }
            t += 2; //inc + check
        }
        t += 2; //inc + check
    }
    return t;
}

int vinograd(mtrx &rez, mtrx mtrx1, int n1, int m1, mtrx mtrx2, int n2, int m2)
{
    if (m1 != n2)
        return SIZE_ERROR;

    vector<int> mulH(n1, 0);
    for (int i = 0; i < n1; i++)
        for (int j = 0; j < m1 / 2; j++)
            mulH[i] = mulH[i] + mtrx1[i][j * 2] * mtrx1[i][j * 2 + 1];

    vector<int> mulV(n1, 0);
    for (int i = 0; i < m2; i++)
        for (int j = 0; j < n2 / 2; j++)
            mulV[i] = mulV[i] + mtrx2[j * 2][i] * mtrx2[j * 2 + 1][i];

    for (int i = 0; i < n1; i++)
        for (int j = 0; j < m2; j++)
        {
            rez[i][j] = -mulH[i] - mulV[j];
            for (int k = 0; k < n2 / 2; k++)
                rez[i][j] = rez[i][j] + (mtrx1[i][2 * k + 1] + mtrx2[2 * k][j]) * (mtrx1[i][2 * k] + mtrx2[2 * k + 1][j]);
        }

    if (n2 % 2 == 1)
        for (int i = 0; i < n1; i++)
            for (int j = 0; j < m2; j++)
                rez[i][j] = rez[i][j] + mtrx1[i][n2 - 1] * mtrx2[n2 - 1][j];

    return 0;
}

int vinogradCalc(mtrx &rez, mtrx mtrx1, int n1, int m1, mtrx mtrx2, int n2, int m2)
{
    int t = 1; // check if !=
    if (m1 != n2)
        return SIZE_ERROR;

    vector<int> mulH(n1, 0);
    t += 2;
    for (int i = 0; i < n1; i++)
    {
        t += 4;
        for (int j = 0; j < m1 / 2; j++)
        {
            t += 15; // [] = [] + [][*] * [][*+]
            mulH[i] = mulH[i] + mtrx1[i][j * 2] * mtrx1[i][j * 2 + 1];
            t += 4;
        }
        t += 2;
    }

    vector<int> mulV(n1, 0);
    t += 2;
    for (int i = 0; i < m2; i++)
    {
        t += 4;
        for (int j = 0; j < n2 / 2; j++)
        {
            t += 15; // [] = [] + [*][] * [*+][]
            mulV[i] = mulV[i] + mtrx2[j * 2][i] * mtrx2[j * 2 + 1][i];
            t += 4;
        }
        t += 2;
    }

    t += 2;
    for (int i = 0; i < n1; i++)
    {
        t += 2;
        for (int j = 0; j < m2; j++)
        {
            t += 6; // [][] = [] - []
            rez[i][j] = -mulH[i] - mulV[j];
            t += 4;
            for (int k = 0; k < n2 / 2; k++)
            {
                t += 6 + 10 + 2 + 10; // [][] = [][] + ([][*+] + [*][]) * ([][*] + [*+][])
                rez[i][j] = rez[i][j] + (mtrx1[i][2 * k + 1] + mtrx2[2 * k][j]) * (mtrx1[i][2 * k] + mtrx2[2 * k + 1][j]);
                t += 4;
            }
            t += 2;
        }
        t += 2;
    }

    t += 3;
    if (n2 % 2 == 1)
    {
        t += 2;
        for (int i = 0; i < n1; i++)
        {
            t += 2;
            for (int j = 0; j < m2; j++)
            {
                t += 14; // [][] = [][] + [][-] * [-][]
                rez[i][j] = rez[i][j] + mtrx1[i][n2 - 1] * mtrx2[n2 - 1][j];
                t += 2;
            }
            t += 2;
        }
    }

    return t;
}

int optimizedVinograd(mtrx &rez, mtrx mtrx1, int n1, int m1, mtrx mtrrx2, int n2, int m2)
{
    if (m1 != n2)
        return SIZE_ERROR;

    vector<int> mulH(n1, 0);
    for (int i = 0; i < n1; i++)
        for (int j = 0; j < m1 - 1; j += 2)
            mulH[i] -= mtrx1[i][j] * mtrx1[i][j + 1];

    vector<int> mulV(n1, 0);
    for (int i = 0; i < m2; i++)
        for (int j = 0; j < n2 - 1; j += 2)
            mulV[i] -= mtrrx2[j][i] * mtrrx2[j + 1][i];

    bool flag = false;
    if (n2 % 2 == 1)
        flag = true;

    for (int i = 0; i < n1; i++)
        for (int j = 0; j < m2; j++)
        {
            rez[i][j] = mulH[i] + mulV[j];
            for (int k = 0; k < n2 - 1; k += 2)
                rez[i][j] += (mtrx1[i][k + 1] + mtrrx2[k][j]) * (mtrx1[i][k] + mtrrx2[k + 1][j]);

            if (flag)
                rez[i][j] += mtrx1[i][n2 - 1] * mtrrx2[n2 - 1][j];
        }

    return 0;
}

int optimizedVinogradCalc(mtrx &rez, mtrx mtrx1, int n1, int m1, mtrx mtrrx2, int n2, int m2)
{
    int t = 1; // check if !=
    if (m1 != n2)
        return SIZE_ERROR;

    vector<int> mulH(n1, 0);
    t += 2;
    for (int i = 0; i < n1; i++)
    {
        t += 3;
        for (int j = 0; j < m1 - 1; j += 2)
        {
            t += 9; // [] -= [][] * [][+]
            mulH[i] -= mtrx1[i][j] * mtrx1[i][j + 1];
            t += 3;
        }
        t += 2;
    }

    vector<int> mulV(n1, 0);
    t += 2;
    for (int i = 0; i < m2; i++)
    {
        t += 3;
        for (int j = 0; j < n2 - 1; j += 2)
        {
            t += 9; // [] -= [][] * [+][]
            mulV[i] -= mtrrx2[j][i] * mtrrx2[j + 1][i];
            t += 3;
        }
        t += 2;
    }

    t += 4;
    bool flag = false;
    if (n2 % 2 == 1)
    {
        t += 1;
        flag = true;
    }

    t += 2;
    for (int i = 0; i < n1; i++)
    {
        t += 2;
        for (int j = 0; j < m2; j++)
        {
            t += 6; // [][] = [] + []
            rez[i][j] = mulH[i] + mulV[j];
            t += 3;
            for (int k = 0; k < n2 - 1; k += 2)
            {
                t += 3+6+2+6; // [][] += ([][+]+[][]) * ([][]+[+][])
                rez[i][j] += (mtrx1[i][k + 1] + mtrrx2[k][j]) * (mtrx1[i][k] + mtrrx2[k + 1][j]);
                t += 3;
            }

            t += 1;
            if (flag)
            {
                t += 3 + 3 + 2 + 3; // [][] += [][-] * [-][]
                rez[i][j] += mtrx1[i][n2 - 1] * mtrrx2[n2 - 1][j];
            }
            t += 2;
        }
        t += 2;
    }

    return t;
}
