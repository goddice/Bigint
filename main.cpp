/**
   Simple 4-function calculator to demonstrate the use of Bigint
**/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Bigint.h"

using namespace std;

extern string exportToBaseNstr(Bigint n, int baseN);
extern Bigint importBaseNstr(string str, int baseN);
extern int charToNum(char num);
extern char numToChar(char num);

int main (int argc, char** argv) {
    int radix = 10;
    if (argc == 3)
    {
        radix = atoi(argv[2]);
    }
    string str1, str2;
    Bigint n1, n2;
    char op;

    while (cin >> str1 >> op >> str2) {
        int base1, base2;
        if (str1.find('#') != string::npos)
        {
            string baseStr = str1.substr(0, str1.find('#'));
            int factor = 1;
            base1 = 0;
            for (int i=0; i<baseStr.length(); i++)
            {
                base1 += charToNum(baseStr[baseStr.length() - 1 - i]) * factor;
                factor = factor * radix;
            }
            str1 = str1.substr(str1.find('#') + 1);
        }
        else
        {
            base1 = radix;
        }

        if (str2.find('#') != string::npos)
        {
            string baseStr = str2.substr(0, str2.find('#'));
            int factor = 1;
            base2 = 0;
            for (int i=0; i<baseStr.length(); i++)
            {
                base2 += charToNum(baseStr[baseStr.length() - 1 - i]) * factor;
                factor = factor * radix;
            }
            str2 = str2.substr(str2.find('#') + 1);
        }
        else
        {
            base2 = radix;
        }
        n1 = importBaseNstr(str1, base1);
        n2 = importBaseNstr(str2, base2);

        switch (op) {
        case '+' :
            cout << exportToBaseNstr(n1 + n2, radix) << endl; break;
        case '-' :
            cout << exportToBaseNstr(n1 - n2, radix) << endl; break;
        case '*' :
            cout << exportToBaseNstr(n1 * n2, radix) << endl; break;
        case '/' :
            cout << exportToBaseNstr(n1 / n2, radix) << endl; break;
        }
    }

    return 0;
}


