/**
 * Bigint: a class for computing with l-o-n-g integers
 * Simple implementation using a fixed-size array of int for the digits,
 * with the LSD in array element 0.
 */

#include <string>
#include <iostream>
#include "Bigint.h"

using namespace std;

/**
 * Copy operations.
 */

Bigint::Bigint (const Bigint& other) {
    *this = other;
}

Bigint& Bigint::operator= (const Bigint& other) {
    for (int i = DIGITS-1; i >= 0; --i) {
        digits[i] = other.digits[i];
    }
    return *this;
}

/**
 * Convenience operations for conveting to and from int,
 * which is useful for mixed-mode expressions.
 *
 * Note that there no checks for nonsense values!
 */

Bigint::Bigint (int other) {
    *this = other;
}

Bigint& Bigint::operator= (int other) {
    // assumes non-negative value
    for (int i = 0; i < DIGITS; ++i) {
        digits[i] = other % 10;
        other /= 10;
    }
    return *this;
}

Bigint::operator int () const {
    // no check for overflow
    int result = 0;
    for (int i = DIGITS-1; i >= 0; --i) {
        result *= 10;
        result += digits[i];
    }
    return result;
}

/**
 * Arithmetic operations
 *
 * No attempt to optimise for leading zeros.
 * And don't forget that the MSD is on the _right_!!
 */

Bigint operator+ (const Bigint& n1, const Bigint& n2) {
    // carry is the carry bit after adding the corresponding bit of n1 and n2
    Bigint n;
    int carry = 0;
    for (int i = 0; i < DIGITS; i++)
    {
        int tmp = n1.digits[i] + n2.digits[i] + carry;
         n.digits[i] = tmp % 10; // result bit
         carry = tmp / 10; // carry bit
    }
    return n;
}

Bigint operator- (const Bigint& n1, const Bigint& n2) {
    //
    Bigint n;
    int carry = 0;
    for (int i = 0; i < DIGITS; i++)
    {
         int isCarry = ((n1.digits[i] - carry) < n2.digits[i]); // Decide if we need a carry bit
         n.digits[i] = n1.digits[i] - carry + isCarry * 10 - n2.digits[i]; // update result bit
         carry = isCarry; // update carry bit
    }
    return n;
}

Bigint operator* (const Bigint& n1, const Bigint& n2) {
    // Calculate the numbers of multiply each bit of n2 with n1
    // Then add these numbers up.
    Bigint n = 0;
    for (int i = 0; i < DIGITS; i ++)
    { // compute the product of ith bit of n2 and n1
        Bigint tmp = 0;
        if (n2.digits[i] != 0)
        {
            int carry = 0;
            for (int j = 0; j < DIGITS; j++)
            {
                tmp.digits[j] = (n2.digits[i] * n1.digits[j] + carry) % 10;
                carry = (n2.digits[i] * n1.digits[j] + carry) / 10;
            }
            for (int j = DIGITS - 1; j >=0; j--)
            { // for the production result, we need to left shift i bits since this is the ith bit of n2
                if (j < i)
                {
                    tmp.digits[j] = 0;
                }
                else
                {
                    tmp.digits[j] = tmp.digits[j - i];
                }
            }
            n = n + tmp; // add them up
        }
    }

    return n;
}

Bigint operator/ (const Bigint& n1, const int& n2)
{ // Divide a bigint with an int
     Bigint n;
     int carry = 0;
     for (int i = DIGITS - 1; i >= 0; --i)
     {
         n.digits[i] = (n1.digits[i] + carry * 10) / n2;
         carry = (n1.digits[i] + carry * 10) % n2;
     }
     return n;
}
Bigint operator/ (const Bigint& n1, const Bigint& n2) {
    // We will evaluate a range of the result,
    // then use binary search to find the final result
    if (n1 < n2)
    {
         return Bigint(0);
    }
    if (n1 == n2)
    {
        return Bigint(1);
    }

    // compute the length of n1 and n2
    Bigint n;
    int len1, len2;
    for (int i = DIGITS - 1; i >= 0; i--)
    {
         if (n1.digits[i] == 0)
         {
             continue;
         }
         else
         {
             len1 = i + 1;
             break;
         }
    }
    for (int i = DIGITS - 1; i >= 0; i--)
    {
        if (n2.digits[i] == 0)
        {
            continue;
        }
        else
        {
            len2 = i + 1;
            break;
        }
    }

    // estimate the upper and lower bound of the result by comparing the length of n1 and n2
    Bigint small = 0;
    Bigint large = 0;
    if (len1 == len2)
    {
         small = 1;
         large = 10;
    }
    else
    {
        small.digits[len1 - len2 - 1] = 1;
        large.digits[len1 - len2 + 1] = 1;
    }

    // binary search
    while (true)
    {
        n = (small + large) / 2;
        if ((n * n2) < n1)
        {
             small = n;
        }
        else if ((n * n2) == n1)
        {
            return n;
        }
        else
        {
             large = n;
        }

        if ((small + Bigint(1)) == large)
        {
            return small;
        }
    }
}

/**
 * Basic comparisons
 *
 * Could perhaps use a helper to avoid duplication, but
 * probably not worthwhile.
 */

bool operator== (const Bigint& n1, const Bigint& n2) {
    for (int i = DIGITS-1; i >= 0; --i) {
        if (n1.digits[i] != n2.digits[i]) {
            return false;
        }
    }
    return true;
}

bool operator< (const Bigint& n1, const Bigint& n2) {
    for (int i = DIGITS-1; i >= 0; --i) {
        if (n1.digits[i] != n2.digits[i]) {
            return n1.digits[i] < n2.digits[i];
        }
    }
    return false;
}

/**
 * IO operations.
 *
 * Note that there are no checks for nonsense values!
 */

ostream& operator<< (ostream &out, const Bigint& n) {
    // skeleton code: assumes n has exactly 10 digits
    string result = "";

    for (int i = DIGITS-1; i>=0; --i)
    {
         if (0 == n.digits[i])
         {
             continue;
         }
         else
         {
             for (int j = i; j >= 0; --j)
             {
                  result.append(1, n.digits[j] + '0');
             }
             break;
         }
    }
    if ("" == result)
    {
        result = "0";
    }
    return out << result;
}

istream& operator>> (istream& in, Bigint& n) {
    // skeleton code: assumes input has exactly 10 digits
    string s;
    if (in >> s) {
        // assumes valid digit string
        for (int i = 0; i <= DIGITS; i++)
        {
             if (i < s.length())
             {
                 n.digits[i] = s[s.length() - 1 - i] - '0';
             }
             else
             {
                 n.digits[i] = 0;
             }
        }
    }
    return in;
}
