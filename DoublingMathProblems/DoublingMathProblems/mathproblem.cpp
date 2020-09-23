#include "mathproblems.h"

void MathProblem::setProblem(Fraction f1, char oper, Fraction f2)
{
    firstFraction = f1;
    secondFraction = f2;
    operation = oper;
    if (oper == '+')
        correctAnswer = firstFraction + secondFraction;
    else if (oper == '-')
        correctAnswer = firstFraction - secondFraction;
    else if (oper == '*')
        correctAnswer = firstFraction * secondFraction;
    else correctAnswer = firstFraction / secondFraction;
    isAnswerCorrect = false;
}
MathProblem::MathProblem()
{
    isAnswerCorrect = false;
}
void MathProblem::displayProblem()
{
    cout << firstFraction << " " << operation << " " << secondFraction << " = ? ";
}
void MathProblem::askUserForAnswer()
{
    cin >> userAnswer;
    if (userAnswer == correctAnswer)
        isAnswerCorrect = true;
}
void MathProblem::displayResults()
{
    cout << "Problem: " << firstFraction << " " << operation << " " <<
        secondFraction << endl;
    cout << "Your answer " << userAnswer;
    cout << "   Correct answer " << correctAnswer;
    if (isAnswerCorrect)
        cout << "    Correct!";
    else cout << "    Sorry, wrong answer";
    cout << endl;
}
bool MathProblem::isCorrect()
{
    return isAnswerCorrect;
}