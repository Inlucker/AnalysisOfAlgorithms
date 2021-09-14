#include <iostream>
#include <vector>

using namespace std;

typedef vector<pair<pair<string, string>, size_t>> cash_t;

string genStr(size_t size)
{
    string rez = string(size, '0');
    for (size_t i = 0; i < size; i++)
    {
        rez[i] = rand()%26 + 97;
    }
    return rez;
}

size_t DamLevLenRec(string str1, string str2)
{
    size_t i = str1.length();
    size_t j = str2.length();
    if (i == 0 && j == 0)
    {
        return 0;
    }
    else if (i > 0 && j == 0)
    {
        return i;
    }
    else if (i == 0 && j > 0)
    {
        return j;
    }
    else
    {
        size_t add = DamLevLenRec(str1.substr(0, i), str2.substr(0, j-1)) + 1;
        size_t del = DamLevLenRec(str1.substr(0, i-1), str2.substr(0, j)) + 1;
        size_t change = DamLevLenRec(str1.substr(0, i-1), str2.substr(0, j-1));
        if (str1[i-1] != str2[j-1])
            change++;
        size_t rez = min(add, min(del, change));
        if (i > 1 && j > 1 && str1[i-1]==str2[j-2] && str1[i-2] == str2[j-1])
        {
            size_t transposition = DamLevLenRec(str1.substr(0, i-2), str2.substr(0, j-2)) + 1;
            rez = min(rez, transposition);
        }
        return  rez;
    }
}

int main()
{
    string str1 = genStr(10);
    string str2 = genStr(10);

    size_t rez = DamLevLenRec(str1, str2);

    //cout << rez << endl;

    return 0;
}
