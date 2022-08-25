#include <assert.h>
#include <algorithm>

#include "../include/UnitTestsSquareEq.h"
#include "../Math/SquareEquation.h"

using std::isfinite;

//-----------------------------------------------------------------------------

bool RunOneUnitTest (double a,                double b, double c,
                     int    testNumSolutions, double testSolutions[],
                     int    testNumber)
{
    //{ ASSERT
    assert (isfinite (a)  != 0);
    assert (isfinite (b)  != 0);
    assert (isfinite (c)  != 0);
    assert (testSolutions != NULL);
    //}

    double solutions[2] = {};

    int numSolutions = SolveSquareEquation (a, b, c, solutions);

    if (numSolutions == Infinity && numSolutions == testNumSolutions)
    {
        goto testPassed;
    }

    if (numSolutions != testNumSolutions)
    {
        printf ("%d: ���������� ������ ������ ���� %d; ���������� ������ ��������� %d\n",
                testNumber, testNumSolutions, numSolutions);

        return 0;
    }

    if (numSolutions == 2 && testSolutions[1] < testSolutions[0])
    {
        std::swap (testSolutions[0], testSolutions[1]);
    }

    for (int i = 0; i < numSolutions; i++)
    {
        if ( !CompareNumbers (testSolutions[i], solutions[i]) )
        {
            printf ("%d: ������� ������ ���� %lf; ����������� ������� %lf\n",
                    testNumber, testSolutions[i], solutions[i]);

            return 0;
        }
    }

    testPassed:
    printf ("���� ���� %d ������� �������!\n", testNumber);

    return 1;
}

//-----------------------------------------------------------------------------

