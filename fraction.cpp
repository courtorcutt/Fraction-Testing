#include <string>
#include <iostream>
using namespace std;

#include "fraction.h"

// Accessor methods -> should get what was entered as numerator and denominator
int Fraction :: numerator() const {
    return nominator;
}

int Fraction :: denominator() const {
    return divisor;
}

// the empty constructor which will return 0/1 as the numerator and denominator
Fraction :: Fraction() : nominator(0), divisor(1) {
}

// first constructor to take a single int, which will return the denominator of 1
Fraction :: Fraction(int numerator) : nominator(numerator), divisor(1) {
}

// the gcd algorithm
int Fraction :: gcd (int nominator, int diviser) {
    // first you check if the two numbers are multiples of each other by determining if the
    // numerator is a larger number and if the remainder from dividing the two numbers is zero.
    // If it is then the gcd is the denominator
    if (diviser <= nominator && nominator % diviser == 0) {
        return diviser;

        // if the numerator is less than the denominator you switch the positions and call the
        // gcd on the (denominator, numerator) to find the greatest common denominator
    } else if (nominator < diviser) {
        return gcd(diviser, nominator);

        // otherwise run the gcd switching positions with the (denominator, remainder of numerator/denominator)
    } else {
        return gcd(diviser, nominator % diviser);
    }
}

// second constructor to take in two ints
Fraction :: Fraction(int numerator, int denominator) {
    // if the entered denominator is zero throw exception
    if (denominator == 0) {
        throw FractionException("You cannot divide by zero in a fraction. Please change!");
    }

    // get the gcd gcd result
    int gcdFactor = gcd(abs(numerator), abs(denominator));

    // check if denominator is negative. If it is then I want only the numerator to be negative
    if (denominator < 0) {
        divisor = -(denominator / gcdFactor);
        nominator = -(numerator / gcdFactor);
    }

    // otherwise denominator is positive, so just return the simplified form
    if(denominator > 0){
        divisor = denominator / gcdFactor;
        nominator = numerator / gcdFactor;
    }
}

// BINARY OPERATORS
ostream& operator<<(ostream& out, const Fraction& fraction) {
    // to write out the fraction
    out << fraction.numerator() << "/" << fraction.denominator();
    return out;
}

// BINARY OPERATIONS
Fraction operator+(const Fraction& firstFraction, const Fraction& secondFraction) {
    // first check if denominators of both fractions being added are the same
    if (firstFraction.denominator() == secondFraction.denominator()) {
        // if they are then you only have to add the numerators over the same denominator
        return Fraction((firstFraction.numerator() + secondFraction.numerator()) , firstFraction.denominator());

        // otherwise must multiply accross and pass into the fraction constructor to find the gcd
    } else {
        int numerator = (firstFraction.numerator() * secondFraction.denominator()) + (firstFraction.denominator() * secondFraction.numerator());
        int divisor = firstFraction.denominator() * secondFraction.denominator();
        return Fraction(numerator, divisor);
    }
}

Fraction operator+(const int& leftInt, const Fraction& rightFraction) {
    // pass in an integer on the left side now
    int leftSide = leftInt * rightFraction.denominator();
    int rightSide = rightFraction.numerator();

    // find a common denominator so you can add both numerators
    int numerator = leftSide + rightSide;
    int denominator = rightFraction.denominator();

    return Fraction(numerator, denominator);
}

Fraction operator+(const Fraction& leftFraction, const int& rightInt) {
    int leftNumerator = leftFraction.numerator();
    int rightNumerator = rightInt * leftFraction.denominator();

    // find a common denominator so you can add both numerators
    int numerator = leftNumerator + rightNumerator;
    int denominator = leftFraction.denominator();

    return Fraction(numerator, denominator);
}

Fraction operator-(const Fraction& firstFraction, const Fraction& secondFraction) {
    // first check if denominators of both fractions being subtracted are the same
    if (firstFraction.denominator() == secondFraction.denominator()) {
        // if they are then you only have to subtract the numerators over the same denominator
        int numerator = firstFraction.numerator() - secondFraction.numerator();
        int denominator = firstFraction.denominator();
        return Fraction(numerator, denominator);
    }

    // otherwise must multiply accross and pass into the fraction constructor to find the gcd to simplify
    int numerator = (firstFraction.numerator() * secondFraction.denominator()) - (firstFraction.denominator() * secondFraction.numerator());
    int denominator = firstFraction.denominator() * secondFraction.denominator();

    return Fraction(numerator, denominator);
}

Fraction operator-(const int& leftInt, const Fraction& rightFraction) {
    int leftSide = leftInt * rightFraction.denominator();
    int rightSide = rightFraction.numerator();

    // find a common denominator to subtract both sides
    int numerator = leftSide - rightSide;
    int denominator = rightFraction.denominator();

    return Fraction(numerator, denominator);
}

Fraction operator-(const Fraction& leftFraction, const int& rightInt) {
    int leftSide = leftFraction.numerator();
    int rightSide = rightInt * leftFraction.denominator();

    // find a common denominator to subtract both sides
    int numerator = leftSide - rightSide;
    int denominator = leftFraction.denominator();

    return Fraction(numerator, denominator);
}

Fraction operator*(const Fraction& firstFraction, const Fraction& secondFraction) {
    // multiply numerators and denominators and pass overall fraction into constructor
    int numerator = firstFraction.numerator() * secondFraction.numerator();
    int denominator = firstFraction.denominator() * secondFraction.denominator();

    return Fraction(numerator, denominator);
}

Fraction operator*(const int& leftInt, const Fraction& rightFraction) {
    // multiply numerators and pass overall fraction into constructor
    int numerator = leftInt * rightFraction.numerator();
    int denominator = rightFraction.denominator();
    return Fraction(numerator, denominator);
}

Fraction operator*(const Fraction& leftFraction, const int& rightInt) {
    // multiply numerators and pass overall fraction into constructor
    int numerator = leftFraction.numerator() * rightInt;
    int denominator = leftFraction.denominator();
    return Fraction(numerator, denominator);
}

Fraction operator/(const Fraction& firstFraction, const Fraction& secondFraction) {
    // must cross multiply to divide
    int numerator = firstFraction.numerator() * secondFraction.denominator();
    int denominator = firstFraction.denominator() * secondFraction.numerator();

    return Fraction(numerator, denominator);
}

Fraction operator/(const int& leftInt, const Fraction& rightFraction) {
    // must cross multiply to divide
    int numerator = leftInt * rightFraction.denominator();
    int denominator = rightFraction.numerator();

    return Fraction(numerator, denominator);
}

Fraction operator/(const Fraction& leftFraction, const int& rightInt) {
    // must cross multiply to divide
    int numerator = leftFraction.numerator();
    int denominator = leftFraction.denominator() * rightInt;

    return Fraction(numerator, denominator);
}

// // UNARY OPERATIONS
Fraction Fraction :: operator-() {
    // want to make the nominator negative when print out <<
    int numerator = -nominator;
    int denominator = divisor;

    return Fraction(numerator, denominator);
}

// want to post increment
Fraction& Fraction :: operator++() {
    // to increment the fraction, you need to add the divisor
    // to the nominator once since you are only incrementing by one
    nominator = nominator + divisor;

    // return this pointer to the fraction&
    return *this;
}

// want to pre increment by adding to the fraction first
Fraction Fraction :: operator++(int incrementFraction) {
    Fraction newFraction(nominator, divisor);
    // so change the fraction by adding by one first to the numerator
    nominator = nominator + divisor;
    // return that fraction for operations to be done
    return newFraction;
}

Fraction& Fraction :: operator+=(const Fraction& secondFraction) {
    int gcdFactor;
    // multiply accross both sides
    int leftSide = nominator * secondFraction.denominator();
    int rightSide = secondFraction.numerator() * divisor;

    // then I want to simplify the new fraction that has been created
    // from multiplying by calling the gcd function
    int numerator = leftSide + rightSide;
    int denominator = secondFraction.denominator() * divisor;
    gcdFactor = gcd(numerator, denominator);

    nominator = (numerator / gcdFactor);
    divisor = (denominator / gcdFactor);
    return *this;
}

Fraction& Fraction::operator+=(const int& rightInt) {
    int gcdFactor;
    int leftSide = nominator;
    int rightSide = rightInt * divisor;

    int numerator = leftSide + rightSide;
    int denominator = divisor;

    gcdFactor = gcd(numerator, denominator);

    nominator = numerator / gcdFactor;
    divisor = denominator / gcdFactor;

    return *this;
}

bool operator==(const Fraction& firstFraction, const Fraction& secondFraction) {
    // check if numerators and denominators are the same and return true of they are
    bool numeratorPass = (firstFraction.numerator() == secondFraction.numerator());
    bool denominatorPass = (firstFraction.denominator() == secondFraction.denominator());

    // only pass if both are true
    return(numeratorPass && denominatorPass);
}

bool operator!=(const Fraction& firstFraction, const Fraction& secondFraction) {
    // check if numerators and denominators are the same and return true of they are
    bool numeratorPass = (firstFraction.numerator() != secondFraction.numerator());
    bool denominatorPass = (firstFraction.denominator() != secondFraction.denominator());

    // only pass if either are true now
    return(numeratorPass || denominatorPass);
}

bool Fraction::operator!=(const Fraction& rightFraction) {
    return (nominator != rightFraction.numerator() && divisor != rightFraction.denominator());
}

bool Fraction::operator!=(const int& rightInt) {
    return (nominator != rightInt && divisor != 1);
}

bool operator>(const Fraction& firstFraction, const Fraction& secondFraction) {
    // get them to have a common denominator by multiplying accross and then
    // just compare the numerators
    int firstNumerator = (firstFraction.numerator() * secondFraction.denominator());
    int secondNumerator = (secondFraction.numerator() * firstFraction.denominator());
    return (firstNumerator > secondNumerator);
}



bool operator>=(const Fraction& firstFraction, const Fraction& secondFraction) {
    // get them to have a common denominator by multiplying accross and then
    // just compare the numerators
    int firstNumerator = (firstFraction.numerator() * secondFraction.denominator());
    int secondNumerator = (secondFraction.numerator() * firstFraction.denominator());
    return (firstNumerator >= secondNumerator);
}

bool operator<(const Fraction& firstFraction, const Fraction& secondFraction) {
    // get them to have a common denominator by multiplying accross and then
    // just compare the numerators
    int firstNumerator = (firstFraction.numerator() * secondFraction.denominator());
    int secondNumerator = (secondFraction.numerator() * firstFraction.denominator());
    return (firstNumerator < secondNumerator);
}

bool operator<=(const Fraction& firstFraction, const Fraction& secondFraction) {
    // get them to have a common denominator by multiplying accross and then
    // just compare the numerators
    int firstNumerator = (firstFraction.numerator() * secondFraction.denominator());
    int secondNumerator = (secondFraction.numerator() * firstFraction.denominator());
    return (firstNumerator <= secondNumerator);
}

bool operator==(const int& leftInt, const Fraction& rightFraction) {
    // the ints denominator will be one. So they will be equal if the fraction's denominator is 1 too
    return (leftInt == rightFraction.numerator() && rightFraction.denominator() == 1);
}

bool operator==(const Fraction& leftFraction, const int& rightInt) {
    // the ints denominator will be one. So they will be equal if the fraction's denominator is 1 too
    return (rightInt == leftFraction.numerator() && leftFraction.denominator() == 1);
}

bool operator!=(const int& leftInt, const Fraction& rightFraction) {
    // should return true of not equal
    return (leftInt != rightFraction.numerator() && rightFraction.denominator() != 1);
}

bool operator!=(const Fraction& leftFracion, const int& rightInt) {
    // should return true of not equal
    return (rightInt != leftFracion.numerator() && leftFracion.denominator() != 1);
}

bool operator>(const int& leftInt, const Fraction& rightFraction) {
    // cross multiply
    int leftSide = leftInt * rightFraction.denominator();
    int rightSide = rightFraction.numerator();

    return (leftSide > rightSide);
}

bool operator>(const Fraction& leftFraction, const int& rightInt) {
    // cross multiply
    int leftSide = rightInt * leftFraction.denominator();
    int rightSide = leftFraction.numerator();

    return (leftSide > rightSide);
}

bool operator>=(const int& leftInt, const Fraction& rightFraction) {
    // cross multiply
    int leftSide = leftInt * rightFraction.denominator();
    int rightSide = rightFraction.numerator();

    return (leftSide >= rightSide);
}

bool operator>=(const Fraction& leftFraction, const int& rightInt) {
    // cross multiply
    int leftSide = rightInt * leftFraction.denominator();
    int rightSide = leftFraction.numerator();

    return (leftSide >= rightSide);
}

bool operator<(const int& leftInt, const Fraction& rightFraction) {
    // multiply the integer with the denominator to cross multiply
    int leftSide = leftInt * rightFraction.denominator();
    int rightSide = rightFraction.numerator();

    return (leftSide < rightSide);
}

bool operator<(const Fraction& leftFraction, const int& rightInt) {
    // multiply the integer with the denominator to cross multiply
    int leftSide = rightInt * leftFraction.denominator();
    int rightSide = leftFraction.numerator();

    return (leftSide < rightSide);
}

bool operator<=(const int& leftInt, const Fraction& rightFraction) {
    // multiply the integer with the denominator to cross multiply
    int leftSide = leftInt * rightFraction.denominator();
    int rightSide = rightFraction.numerator();

    return (leftSide <= rightSide);
}

bool operator<=(const Fraction& leftFraction, const int& rightInt) {
    // multiply the integer with the denominator to cross multiply
    int leftSide = rightInt * leftFraction.denominator();
    int rightSide = leftFraction.numerator();

    return (leftSide <= rightSide);
}

istream& operator>>(istream& in, Fraction& fraction) {
    // first I want a string to be created
    // the string will take in what the user entered and the /
    string slant;
    in >> slant;

    // then the slant must be found
    size_t found = slant.find("/");
    cout << "Input is: " << slant << '\n';
    int len = slant.length();
    cout << "Input length is: " << len << '\n';
    cout << "Found is at position: " << found << '\n';

    if(found != string::npos) {
        int numerator = atoi(slant.substr(0, found).c_str());;
        cout << "Numerator is: " << numerator << '\n';
        int denominator = atoi(slant.substr(found + 1).c_str());
        cout << "Denominator is: " << denominator << '\n';

        if(numerator == 0 && denominator != 0) {
            fraction.nominator = 0;
            fraction.divisor = 1;
        } else if(denominator == 0) {
            throw FractionException("You cannot divide a fraction by zero");
        } else {
            // otherwise set the numerator and denominator to be returned
            fraction.nominator = numerator;
            fraction.divisor = denominator;
        }
    }

    // when we enter nothing we want to set the numerator to 0 and divisor to 1
    // by checking if the whole in slant string is empty
    else if(!slant.empty()) {
        if(atoi(slant.c_str()) == 0) {
            fraction.nominator = 0;
            fraction.divisor = 1;
        } else {
            // otherwise no / was found so dealing with whole number
            // so take in the whole string and put in fraction form by dividing by one
            fraction.nominator = atoi(slant.c_str());
            fraction.divisor = 1;
        }
    }
    return in;
}

// For FractionException:
FractionException :: FractionException(const string& errorMessage) : error(errorMessage) {
}

string FractionException :: what() {
    return error;
}