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
