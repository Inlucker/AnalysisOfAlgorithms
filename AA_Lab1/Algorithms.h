#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <vector>

using namespace std;

typedef size_t (*AlgPtr)(string, string);

size_t LevLen(string src, string dst);

size_t LevLenRec(string str1, string str2);

typedef vector<pair<pair<string, string>, size_t>> cash_t;

size_t LevLenRecCash(string str1, string str2, cash_t &cash);

size_t LevLenRecCash(string str1, string str2);

size_t DamLevLen(string src, string dst);

size_t DamLevLenRec(string str1, string str2);

#endif // ALGORITHMS_H
