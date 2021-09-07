#include <iostream>
#include <vector>

#include <Windows.h>
#include <limits>

using namespace std;

#include "Algorithms.h"
#include "tools.h"

int main()
{
    string str1 = "arsetant";
    string str2 = "dagestan";
    //string str1 = "kot";
    //string str2 = "skto";

    //getCPUTimeOfAlg(&LevLenRecCash, str1, str2, ITERATIONS_REC_CASH, "LevLenRecCash");
    //getCPUTimeOfAlg(&LevLenRec, str1, str2, ITERATIONS_REC, "LevLenRec");
    //getCPUTimeOfAlg(&LevLen, str1, str2, ITERATIONS_MATRIX, "LevLen");
    //getCPUTimeOfAlg(&DamLevLenRec, str1, str2, ITERATIONS_REC, "DamLevLenRec");

    int input = -1;
    while (input != 0)
    {
        cout << endl;
        cout << "1 - User mode" << endl;
        cout << "2 - Time tests" << endl;
        cout << "3 - Memory tests" << endl;
        cout << "0 - Exit from programm" << endl;
        cout << endl;

        _flushall();
        cout << "Enter the number of command to be done: ";
        while (!(cin >> input))
        {
            cout << "Wrong input" << endl;
            cin.clear();
            _flushall();
            cout << "Enter the number of command to be done: ";
        }

        switch (input)
        {
            case 1:
            {
                cout << "Enter str1:"  << endl;
                cin >> str1;
                cout << "Enter str2:"  << endl;
                cin >> str2;
                cout << endl;
                cout << "Algorithms:"  << endl;
                cout << "1 - LevLen:"  << endl;
                cout << "2 - LevLenRec:"  << endl;
                cout << "3 - LevLenRecCash:"  << endl;
                cout << "4 - DamLevLenRec:"  << endl;
                cout << "Choose algorithm: ";
                int alg = -1;
                cin >> alg;
                size_t rez = -1;
                switch (alg)
                {
                    case 1:
                    {
                        rez = LevLen(str1, str2);
                        break;
                    }
                    case 2:
                    {
                        rez = LevLenRec(str1, str2);
                        break;
                    }
                    case 3:
                    {
                        rez = LevLenRecCash(str1, str2);
                        break;
                    }
                    case 4:
                    {
                        rez = DamLevLenRec(str1, str2);
                        break;
                    }
                    default:
                    {
                        cout << "Wrong algorithm" << endl;
                        break;
                    }
                }
                cout << "length between \"" << str1 << "\" and \"" << str2 << "\" = " << rez << endl;
                break;
            }
            case 2:
            {
                cout << endl;
                cout << "Algorithms:"  << endl;
                cout << "1 - LevLen:"  << endl;
                cout << "2 - LevLenRec:"  << endl;
                cout << "3 - LevLenRecCash:"  << endl;
                cout << "4 - DamLevLenRec:"  << endl;
                cout << "5 - All:"  << endl;
                cout << "Choose algorithm: ";
                int alg = -1;
                cin >> alg;
                cout << endl;
                switch (alg)
                {
                    case 1:
                    {
                        //getCPUTimeOfAlg(&LevLen, 8, ITERATIONS_MATRIX, "LevLen");
                        getLevLenTimes();
                        break;
                    }
                    case 2:
                    {
                        //getCPUTimeOfAlg(&LevLenRec, 8, ITERATIONS_REC, "LevLenRec");
                        getLevLenRecTimes();
                        break;
                    }
                    case 3:
                    {
                        //getCPUTimeOfAlg(&LevLenRecCash, 8, ITERATIONS_REC_CASH, "LevLenRecCash");
                        getLevLenRecCashTimes();
                        break;
                    }
                    case 4:
                    {
                        //getCPUTimeOfAlg(&DamLevLenRec, 8, ITERATIONS_REC, "DamLevLenRec");
                        getDamLevLenRecTimes();
                        break;
                    }
                    case 5:
                    {
                        /*getCPUTimeOfAlg(&LevLen, 8, ITERATIONS_MATRIX, "LevLen");
                        getCPUTimeOfAlg(&LevLenRec, 8, ITERATIONS_REC, "LevLenRec");
                        getCPUTimeOfAlg(&LevLenRecCash, 8, ITERATIONS_REC_CASH, "LevLenRecCash");
                        getCPUTimeOfAlg(&DamLevLenRec, 8, ITERATIONS_REC, "DamLevLenRec");*/
                        getLevLenTimes();
                        getLevLenRecTimes();
                        getLevLenRecCashTimes();
                        getDamLevLenRecTimes();
                        break;
                    }
                    default:
                    {
                        cout << "Wrong algorithm" << endl;
                        break;
                    }
                    break;
                }
                break;
            }
            case 3:
            {
                cout << endl;
                cout << "Algorithms:"  << endl;
                cout << "1 - LevLen:"  << endl;
                cout << "2 - LevLenRec:"  << endl;
                cout << "3 - LevLenRecCash:"  << endl;
                cout << "4 - DamLevLenRec:"  << endl;
                cout << "Choose algorithm: ";
                int alg = -1;
                cin >> alg;
                cout << endl;
                switch (alg)
                {
                    case 1:
                    {
                        cout << "ToDo!" << endl;
                        break;
                    }
                    case 2:
                    {
                        cout << "ToDo!" << endl;
                        break;
                    }
                    case 3:
                    {
                        cout << "ToDo!" << endl;
                        break;
                    }
                    case 4:
                    {
                        cout << "ToDo!" << endl;
                        break;
                    }
                    default:
                    {
                        cout << "Wrong algorithm" << endl;
                        break;
                    }
                    break;
                }
                break;
            }
            case 0:
            {
                cout << "Good buy!" << endl;
                break;
            }
            default:
            {
                cout << "Wrong command" << endl;
                break;
            }
        }
    }

    return 0;
}
