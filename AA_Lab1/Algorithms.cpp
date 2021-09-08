#include "Algorithms.h"


size_t LevLen(string str1, string str2)
{
    if (str2.length() < str1.length())
    {
        return LevLen(str2, str1);
    }

        const size_t min_size = str1.length();
        const size_t max_size = str2.length();

    /*cout << "   0| ";
    for (size_t i = 0; i < min_size; i++)
    {
        cout << src[i] << "| ";
    }
    cout << endl;
    for (size_t i = 0; i <= min_size+1; i++)
        cout << "-|-";
    cout << endl;*/

    vector<size_t> cur_row(min_size+1);
    for (size_t i = 1; i <= min_size; i++)
    {
        cur_row[i] = i;
    }

    //cout << "0| ";
    //cout << cur_row;
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
        //cout << dst[i-1] << "| ";
        //cout << cur_row;
    }

    return cur_row[min_size];
}

size_t LevLenRec(string str1, string str2)
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
        size_t add = LevLenRec(str1.substr(0, i), str2.substr(0, j-1)) + 1;
        size_t del = LevLenRec(str1.substr(0, i-1), str2.substr(0, j)) + 1;
        size_t change = LevLenRec(str1.substr(0, i-1), str2.substr(0, j-1));
        if (str1[i-1] != str2[j-1])
            change++;
        return  min(add, min(del, change));
    }
}

bool checkCash(string str1, string str2, const cash_t &cash, size_t& rez)
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
    size_t len = INT_MAX;
    if (checkCash(str1, str2, cash, len)) // FIX
    {
        return len;
    }
    //cout << str1 << " " << str2 << endl;
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
        size_t add = LevLenRecCash(str1.substr(0, i), str2.substr(0, j-1), cash) + 1;
        size_t del = LevLenRecCash(str1.substr(0, i-1), str2.substr(0, j), cash) + 1;
        size_t change = LevLenRecCash(str1.substr(0, i-1), str2.substr(0, j-1), cash);
        if (str1[i-1] != str2[j-1])
            change++;

        size_t rez = min(add, min(del, change));
        cash.push_back(make_pair(make_pair(str1, str2), rez));
        return  rez;
    }
}

size_t LevLenRecCash(string str1, string str2)
{
    cash_t cash = cash_t();
    return LevLenRecCash(str1, str2, cash);
}

size_t DamLevLen(string src, string dst)
{
    if (dst.length() < src.length())
    {
        return DamLevLen(dst, src);
    }

    const size_t min_size = src.length();
    const size_t max_size = dst.length();

    vector<size_t> row1(min_size+1);
    for (size_t i = 1; i <= min_size; i++)
    {
        row1[i] = i;
    }

    vector<size_t> row2 = vector<size_t>(min_size+1);

    for (size_t i = 1; i <= max_size; i++)
    {
        if (i >= 2)
        {
            vector<size_t> row3 = row2;
            row2 = row1;
            row1 = vector<size_t>(min_size+1);
            row1[0] = i;
            for (size_t j = 1; j <= min_size; j++)
            {
                size_t add = row2[j] + 1;
                size_t del = row1[j-1] + 1;
                size_t change = row2[j-1];
                if (src[j-1] != dst[i-1])
                    change++;
                row1[j] = min(add, min(del, change));

                if (i > 1 && j > 1 && src[j-1]==dst[i-2] && src[j-2] == dst[i-1])
                {
                    //cout << src[j-1] << " == " << dst[i-2] << "; " << src[j-2] << " == " << dst[i-1] << endl;
                    size_t transposition = row3[j-2] + 1;
                    row1[j] = min(row1[j], transposition);
                }
            }
        }
        else
        {
            row2 = row1;
            row1 = vector<size_t>(min_size+1);
            row1[0] = i;
            for (size_t j = 1; j <= min_size; j++)
            {
                size_t add = row2[j] + 1;
                size_t del = row1[j-1] + 1;
                size_t change = row2[j-1];
                if (src[j-1] != dst[i-1])
                    change++;
                row1[j] = min(add, min(del, change));
            }
        }
    }

    return row1[min_size];
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

ostream& operator <<(ostream& os, const vector<size_t>& vec)
{
    if (vec.size() == 0)
    {
        os << "vector is empty.";
        return os;
    }

    for (auto& el : vec)
    {
        os << el << "| ";
    }
    cout << endl;
    /*for (size_t i = 0; i <= vec.size(); i++)
        os << "-|-";
    cout << endl;*/

    return os;
}

