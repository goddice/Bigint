/**
 * Bigint: a class for computing with l-o-n-g integers
**/

#ifndef BIGINT_H_
#define BIGINT_H_

#ifndef DIGITS
#define DIGITS 256
#endif

class Bigint {

  public:

    /**
     * Creates a Bigint with the value of other
     */
    Bigint (const Bigint& other);
    Bigint (int other = 0);

    /**
     * Type conversions
     */
    operator int () const;

    /**
     * Makes this equivalent to other
     */
    Bigint& operator= (const Bigint& other);
    Bigint& operator= (int other);

    /**
     * Computes sum, difference, product, or quotient of n1 and n2
     */
    friend Bigint operator+ (const Bigint& n1, const Bigint& n2);
    friend Bigint operator- (const Bigint& n1, const Bigint& n2);
    friend Bigint operator* (const Bigint& n1, const Bigint& n2);
    friend Bigint operator/ (const Bigint& n1, const int& n2);
    friend Bigint operator/ (const Bigint& n1, const Bigint& n2);

    /**
     * Arithmetic comparisons
     */
    friend bool operator== (const Bigint& n1, const Bigint& n2);
    friend bool operator< (const Bigint& n1, const Bigint& n2);

    /**
      * Inserts or extracts a Bigint on an IO stream
      */
    friend std::ostream& operator<< (std::ostream &out, const Bigint& n);
    friend std::istream& operator>> (std::istream& in, Bigint& n);

  private:
    int digits[DIGITS];
};

#endif
