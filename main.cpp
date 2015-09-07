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
            base1 = atoi(str1.substr(0, str1.find('#')).c_str());
            str1 = str1.substr(str1.find('#') + 1);
        }
        else
        {
            base1 = radix;
        }

        if (str2.find('#') != string::npos)
        {
            base2 = atoi(str2.substr(0, str2.find('#')).c_str());
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


