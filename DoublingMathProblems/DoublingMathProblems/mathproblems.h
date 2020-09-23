#ifndef __MATHPROBLEMS_H_INCLUDED__
#define __MATHPROBLEMS_H_INCLUDED__
#include "fraction.h"

class MathProblem
{
protected:
    Fraction firstFraction;
    Fraction secondFraction;
    Fraction userAnswer;
    Fraction correctAnswer;
    char operation;
    bool isAnswerCorrect;
public:
    void setProblem(Fraction, char, Fraction);
    MathProblem();
    void displayProblem();
    void askUserForAnswer();
    void displayResults();
    bool isCorrect();
};
#endif // !__MATHPROBLEMS_H_INCLUDED__