#include <iostream>
#include <vector>
#include <climits>

using namespace std;

typedef vector<pair<pair<size_t, size_t>, size_t>> cash_t;

string genStr(size_t size)
{
    string rez = string(size, '0');
    for (size_t i = 0; i < size; i++)
    {
        rez[i] = rand()%26 + 97;
    }
    return rez;
}

bool checkCash(size_t str1, size_t str2, const cash_t &cash, size_t& rez)
{
    for (auto &el : cash)
    {
        if (el.first.first == str1 && el.first.second == str2)
        {
            rez = el.second;
            return true;
        }
    }
    return false;
}

size_t LevLenRecCash(string str1, string str2, cash_t &cash)
{
    size_t i = str1.length();
    size_t j = str2.length();
    size_t len = INT_MAX;
    if (checkCash(i, j, cash, len))
    {
        return len;
    }
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
        size_t add = LevLenRecCash(str1.substr(0, i), str2.substr(0, j-1), cash) + 1;
        size_t del = LevLenRecCash(str1.substr(0, i-1), str2.substr(0, j), cash) + 1;
        size_t change = LevLenRecCash(str1.substr(0, i-1), str2.substr(0, j-1), cash);
        if (str1[i-1] != str2[j-1])
            change++;

        size_t rez = min(add, min(del, change));
        cash.push_back(make_pair(make_pair(i, j), rez));
        return  rez;
    }
}

size_t LevLenRecCash(string str1, string str2)
{
    cash_t cash = cash_t();
    return LevLenRecCash(str1, str2, cash);
}

int main()
{
    string str1 = genStr(10);
    string str2 = genStr(10);

    size_t rez = LevLenRecCash(str1, str2);

    //cout << rez << endl;

    return 0;
}
