#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> mtrx;

using namespace std;

void mtrxGen(mtrx &rez, int n, int m, int lim) {
    for (int i = 0; i < n; i++) {
        rez.push_back(vector<int>(m));
        for (int j = 0; j < m; j++) {
            rez[i][j] = rand() % lim;
        }
    }
}

int prepare(mtrx &result, int n1, int m1, int n2, int m2)
{
    if (m1 != n2)
    {
        return 1;
    }
    for (int i = 0; i < n1; i++)
    {
        result.push_back(vector<int>(m2, 0));
    }
    return 0;
}

int standartMult(mtrx &rez, mtrx mtrx1, int n1, int m1, mtrx mtrx2, int n2, int m2)
{
    if (m1 != n2)
    {
        return 1;
    }
    for (int i = 0; i < n1; i++)
    {
       for (int j = 0; j < m2; j++)
       {
           rez[i][j] = 0;
           for (int k = 0; k < n2; k++)
           {
               rez[i][j] = rez[i][j] + mtrx1[i][k] * mtrx2[k][j];
           }
       }
    }
    return 0;
}

void printMtrx(mtrx mtr, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << mtr[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    int n = 3;
    mtrx mtrx1, mtrx2, rez;
    mtrxGen(mtrx1, n, n, 5);
    mtrxGen(mtrx2, n, n, 5);
    prepare(rez, n, n, n, n);
    standartMult(rez, mtrx1, n, n, mtrx2, n, n);

    cout << "Matrix 1:" << endl;
    printMtrx(mtrx1, n, n);

    cout << "Matrix 2:" << endl;
    printMtrx(mtrx2, n, n);

     cout << "Result Matrix:" << endl;
     printMtrx(rez, n, n);
    return 0;
}
