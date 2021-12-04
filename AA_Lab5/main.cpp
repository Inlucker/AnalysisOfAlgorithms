#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

vector<string> get_words(string str)
{
    vector<string> rez;

    string tmp = "";
    for (auto& c : str)
    {
        if (c != ' ')
            tmp += c;
        else
        {
            rez.push_back(tmp);
            tmp = "";
        }
    }
    if (tmp != "")
        rez.push_back(tmp);

    return rez;
}

vector<string> get_polinoms(vector<string> words)
{
    vector<string> rez;

    for (auto& w : words)
    {
        bool flag = true;
        int len = w.length();
        int half_len = w.length()/2;
        for (int i = 0; i <= half_len; i++)
            if (w[i] != w[len-1-i])
            {
                flag = false;
                break;
            }
        if (flag)
            rez.push_back(w);
    }

    return rez;
}

string get_longest_polinom(vector<string> polinoms)
{
    string rez = polinoms[0];

    for (auto& p : polinoms)
    {
        if (p.length() > rez.length())
            rez = p;
    }

    return rez;
}

string get_res(string str)
{
    return (get_longest_polinom(get_polinoms(get_words(str))));
}


int main()
{
    cout << "Hello World!" << endl;

    vector<string> words = get_words("test lol 23323232 s sss ll 233232332 sls sll lls");
    vector<string> polinoms = get_polinoms(words);
    string longest_polinom = get_longest_polinom(polinoms);

    for (auto& w:polinoms)
    {
        cout << w << endl;
    }

    cout << longest_polinom << endl;

    cout << get_res("test lol 23323232 s sss ll 2332323322 sls sll lls");


    return 0;
}
