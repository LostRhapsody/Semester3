#ifndef __FRACTION_H_INCLUDED__
#define __FRACTION_H_INCLUDED__
#include <iostream>
using namespace std;


class Fraction
{
    friend ostream& operator<<(ostream&, Fraction&);
    friend istream& operator>>(istream&, Fraction&);
private:
    int wholeNum;
    int numerator;
    int denominator;
    double convert();
public:
    Fraction(int = 0, int = 1);
    Fraction(int, int, int);
    void enterFractionValue();
    void reduceFraction();
    void displayFraction();
    int getWholeNum();
    int getNumerator();
    void removeWholeNum();
    Fraction operator+(Fraction&);
    Fraction operator-(Fraction&);
    Fraction operator*(Fraction&);
    Fraction operator/(Fraction&);
    bool operator==(Fraction&);
    bool operator>(Fraction&);
    bool operator<(Fraction&);
};
#endif // __FRACTION_H_INCLUDED__