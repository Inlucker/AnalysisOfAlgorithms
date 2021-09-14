#include <iostream>
#include <vector>

using namespace std;

string genStr(size_t size)
{
    string rez = string(size, '0');
    for (size_t i = 0; i < size; i++)
    {
        rez[i] = rand()%26 + 97;
    }
    return rez;
}

size_t LevLen(string str1, string str2)
{
    if (str2.length() < str1.length())
    {
        return LevLen(str2, str1);
    }

        const size_t min_size = str1.length();
        const size_t max_size = str2.length();

    vector<size_t> cur_row(min_size+1);
    for (size_t i = 1; i <= min_size; i++)
    {
        cur_row[i] = i;
    }

    for (size_t i = 1; i <= max_size; i++)
    {
        vector<size_t> prev_row = cur_row;
        cur_row = vector<size_t>(min_size+1);
        cur_row[0] = i;
        for (size_t j = 1; j <= min_size; j++)
        {
            size_t add = prev_row[j] + 1;
            size_t del = cur_row[j-1] + 1;
            size_t change = prev_row[j-1];
            if (str1[j-1] != str2[i-1])
                change++;
            cur_row[j] = min(add, min(del, change));
        }
    }

    return cur_row[min_size];
}

int main()
{
    string str1 = genStr(10);
    string str2 = genStr(10);

    size_t rez = LevLen(str1, str2);

    //cout << rez << endl;

    return 0;
}
