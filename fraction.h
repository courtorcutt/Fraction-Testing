class Fraction{
private:
    // the default constructor
    int nominator;
    int divisor;

    // to compute the greatest common divisor
    int gcd(int nominator, int divisor);


public:
    // empty constructor when there is no input
    Fraction();

    // first constructor to take a single int
    Fraction(int numerator);

    // second constructor to take two ints
    Fraction(int numerator, int denominator);

    // accessor methods for getting the nominator and divisor
    int numerator() const;
    int denominator() const;

    // The << and >> binary operators can access the variables now in the Function class
    friend ostream& operator<<(ostream& out, const Fraction& fraction);
    friend istream& operator>>(istream& in, Fraction& fraction);

    // Unary Operations
    Fraction operator-();
    Fraction& operator++();
    Fraction operator++(int incrementFraction);

    // Binary Operations
    Fraction& operator+=(const Fraction& secondFraction);
    Fraction& operator+=(const int& rightInt);

    // Comparison operators
    friend bool operator==(const Fraction& firstFraction, const Fraction& secondFraction);
    friend bool operator==(const int& leftInt, const Fraction& rightFraction);
    friend bool operator==(const Fraction& leftFraction, const int& rightInt);

    friend bool operator!=(const Fraction& firstFraction, const Fraction& secondFraction);
    friend bool operator!=(const int& leftInt, const Fraction& rightFraction);
    friend bool operator!=(const Fraction& leftFraction, const int& rightInt);
    bool operator!=(const int& rightInt);
    bool operator!=(const Fraction& right);

    friend bool operator>(const Fraction& firstFraction, const Fraction& secondFraction);
    friend bool operator>(const int& leftInt, const Fraction& rightFraction);
    friend bool operator>(const Fraction& leftFraction, const int& rightInt);

    friend bool operator>=(const Fraction& firstFraction, const Fraction& secondFraction);
    friend bool operator>=(const int& leftInt, const Fraction& rightFraction);
    friend bool operator>=(const Fraction& leftFraction, const int& rightInt);

    friend bool operator<(const Fraction& firstFraction, const Fraction& secondFraction);
    friend bool operator<=(const Fraction& firstFraction, const Fraction& secondFraction);

};

// Binary Operations
Fraction operator+(const Fraction& firstFraction, const Fraction& secondFraction);
Fraction operator+(const int& leftInt, const Fraction& rightFraction);
Fraction operator+(const Fraction& leftFraction, const int& rightInt);

Fraction operator-(const Fraction& firstFraction, const Fraction& secondFraction);
Fraction operator-(const int& leftInt, const Fraction& rightFraction);
Fraction operator-(const Fraction& leftFraction, const int& rightInt);

Fraction operator*(const Fraction& firstFraction, const Fraction& secondFraction);
Fraction operator*(const int& leftInt, const Fraction& rightFraction);
Fraction operator*(const Fraction& leftFraction, const int& rightInt);

Fraction operator/(const Fraction& firstFraction, const Fraction& secondFraction);
Fraction operator/(const int& leftInt, const Fraction& rightFraction);
Fraction operator/(const Fraction& leftFraction, const int& rightInt);

class FractionException {
private:
    // string to hold the error message
    string error;

public:
    // the constructor to take in the error message
    FractionException(const string& errorMessage);

    // returns error message
    string what();
};
