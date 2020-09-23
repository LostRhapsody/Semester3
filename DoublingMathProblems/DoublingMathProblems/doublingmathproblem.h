#ifndef __DOUBLINGMATHPROBLEM_H_INCLUDED
#define __DOUBLINGMATHPROBLEM_H_INCLUDED
#include "mathproblems.h"

class DoublingMathProblem : public MathProblem
{
public:
    DoublingMathProblem();
    void setProblem(Fraction);
};
#endif // !__DOUBLINGMATHPROBLEM_H_INCLUDED