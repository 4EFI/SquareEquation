#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <algorithm>

#define NLOG

#include "../../LOG/LOG.h"
#include "../SquareEquationLib.h"

using std::isfinite;

//-----------------------------------------------------------------------------

int SolveLinearEquation (double a, double b, double *solution)
{
    //{ ASSERT
    assert (isfinite (a) != 0);
    assert (isfinite (b) != 0);
    assert (solution     != NULL);
    //}

    if ( CompareNumbers (a, 0) )
    {
        if ( CompareNumbers (b, 0) )
        {
            return Infinity;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        *solution = (-b) / a;

        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wfloat-equal"

        if (*solution == -0)
        {
            *solution = 0;
        }

        #pragma GCC diagnostic pop

        return 1;
    }

    return -1;
}

//-----------------------------------------------------------------------------

int SolveSquareEquation (double a, double b, double c, double *solutions)
{
    $LOG_LVL_UP

    //{ ASSERT
    assert (isfinite (a) != 0);
    assert (isfinite (b) != 0);
    assert (isfinite (c) != 0);
    assert (solutions    != NULL);
    //}

    //bx + c = 0
    if ( CompareNumbers (a, 0) )
    {
        return SolveLinearEquation (b, c, solutions);
    }

    if ( CompareNumbers(c, 0) )
    {
        solutions[0] = 0;

        int numSolutions = SolveLinearEquation(a, b, &solutions[1]);

        if (numSolutions == Infinity) return Infinity;
        else                          return numSolutions + 1;
    }

    double D = b*b - 4*a*c;

    LOG ("D = %lf", D);

    if (D < 0)
    {
        return 0;
    }
    else if ( CompareNumbers(D, 0) )
    {
        solutions[0] = -b / (2*a);

        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wfloat-equal"

        if (solutions[0] == -0) solutions[0] = 0;

        #pragma GCC diagnostic pop

        return 1;
    }
    else
    {
        double sqrtD = sqrt (D);

        solutions[0] = ( -b - sqrtD ) / (2*a);
        solutions[1] = ( -b + sqrtD ) / (2*a);

        return 2;
    }

    return -1;
}

//-----------------------------------------------------------------------------

bool CompareNumbers (double x, double y, double accuracy)
{
    $LOG_LVL_UP

    FLOG ("x = %lf, y = %lf, accuracy = %lf", x, y, accuracy);

    //{ ASSERT
    assert (isfinite (x)        != 0);
    assert (isfinite (y)        != 0);
    assert (isfinite (accuracy) != 0);
    //}

    return ( fabs (x - y) < accuracy );
}

//-----------------------------------------------------------------------------

