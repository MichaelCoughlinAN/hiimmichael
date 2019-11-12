/*
    Solves algebraic problems for linear systems of 3 equations in 3 unknowns,
    and quadratic, cubic, and quartic equations of one variable.
*/

#ifndef __DDC_ALGEBRA_H
#define __DDC_ALGEBRA_H

#include <complex>

namespace Algebra
{
    typedef std::complex<double> complex;

    const double TOLERANCE = 1.0e-8;

    class SolverException
    {
    public:
        SolverException(const char *_message)
            : message(_message)
        {
        }

        const char *GetMessage() const { return message; }

    private:
        const char *message;
    };

    inline bool IsZero(complex x)
    {
        return (fabs(x.real()) < TOLERANCE) && (fabs(x.imag()) < TOLERANCE);
    }

    //
    //   Solves the linear system of equations for the variables u,v,w:
    //
    //       Du + Ev + Fw + G = 0
    //       Hu + Iv + Jw + K = 0
    //       Lu + Mv + Nw + P = 0
    //
    //   Where D..P are known real numbers.
    //
    //   If a solution is possible, returns true and sets u, v, w.
    //   If no solution exists, returns false and leaves u, v, w unmodified.
    //
    bool SolveLinearEquations(
        // input parameters
        double D, double E, double F, double G,
        double H, double I, double J, double K,
        double L, double M, double N, double P,

        // output parameters (set only if this function returns true)
        double &u, double &v, double &w
    );

    // Returns n=0..numComplexValues, and fills in outArray 
    // with the n values from inArray that are real-valued 
    // (i.e., whose imaginary parts are within TOLERANCE of 0.)
    // outArray must be large enough to receive numComplexValues values.
    int FilterRealNumbers(
        int numComplexValues, 
        const complex inArray[], 
        double outArray[]);

    // Returns n=0..2, the number of distinct complex roots 
    // found for the equation
    //
    //     ax^2 + bx + c = 0
    //
    // Stores the roots in the first n slots of the array 'roots'.
    int SolveQuadraticEquation(
        complex a, 
        complex b, 
        complex c, 
        complex roots[2]);

    // Returns n=0..3, the number of distinct complex roots 
    // found for the equation
    //
    //     ax^3 + bx^2 + cx + d = 0
    //
    // Stores the roots in the first n slots of the array 'roots'.
    int SolveCubicEquation(
        complex a, 
        complex b, 
        complex c, 
        complex d, 
        complex roots[3]);

    // Returns n=0..4, the number of distinct complex roots 
    // found for the equation
    //
    //     ax^4 + bx^3 + cx^2 + dx + e = 0
    //
    // Stores the roots in the first n slots of the array 'roots'.
    int SolveQuarticEquation(
        complex a, 
        complex b, 
        complex c, 
        complex d, 
        complex e, 
        complex roots[4]);

    // The above solvers are generalized for complex-valued 
    // coefficients and roots.
    // Below are helper methods that accept real-valued 
    // coefficients and return the subset of roots that are real-valued.

    inline int SolveQuadraticEquation(
        double a, 
        double b, 
        double c, 
        double roots[2])
    {
        complex croots[2];

        const int numComplexRoots = SolveQuadraticEquation(
            complex(a), 
            complex(b), 
            complex(c), 
            croots);

        return FilterRealNumbers(numComplexRoots, croots, roots);
    }

    inline int SolveCubicEquation(
        double a, 
        double b, 
        double c, 
        double d, 
        double roots[3])
    {
        complex croots[3];

        const int numComplexRoots = SolveCubicEquation(
            complex(a), 
            complex(b), 
            complex(c), 
            complex(d), 
            croots);

        return FilterRealNumbers(numComplexRoots, croots, roots);
    }

    inline int SolveQuarticEquation(
        double a, 
        double b, 
        double c, 
        double d, 
        double e, 
        double roots[4])
    {
        complex croots[4];

        const int numComplexRoots = SolveQuarticEquation(
            complex(a), 
            complex(b), 
            complex(c), 
            complex(d), 
            complex(e), 
            croots);

        return FilterRealNumbers(numComplexRoots, croots, roots);
    }

    void UnitTest();
}

#endif // __DDC_ALGEBRA_H
