#ifndef SQUARE_EQUATION_H
#define SQUARE_EQUATION_H

//{----------------------------------------------------------------------------
/// @file SquareEquation.cpp
/// @mainpage
/// Files:
/// - @ref SquareEquation.h
/// - @ref Input.h
//}----------------------------------------------------------------------------

#include "Config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <algorithm>

#include "Input.h"

using std::isfinite;

//-----------------------------------------------------------------------------

/// \brief ��������� �������������
const int    Infinity = 9999999;

/// \brief ��������� ��������
const double Accuracy = 10e-6;

//-----------------------------------------------------------------------------

//{----------------------------------------------------------------------------
/// \brief ������� ��� ������� ��������� ���������
///
/// \param a ������ ���������� ��������� ���������
/// \param b ������ ���������� ��������� ���������
/// \param *solution ��������� ������� ��������� ���������
///
/// \return ���������� ���������� ������� ���������
///
/// \note ������� ��������� ����������� ��������� ��������� ���� a*x + b = 0
///
/// \warning ��� ������� �������� �������� ������������ ����������
///          ��� ������ �������
//}----------------------------------------------------------------------------

int SolveLinearEquation (double a, double b, double *solution);

//{----------------------------------------------------------------------------
/// \brief ������� ��� ������� ����������� ���������
///
/// \param a ������ ���������� ����������� ���������
/// \param b ������ ���������� ����������� ���������
/// \param c ������ ���������� ����������� ���������
/// \param *solutions ������ ������� ����������� ���������
///
/// \return ���������� ���������� ������� ���������
///
/// \note ������� ��������� ����������� ����������� ��������� ����
///       a*x^2 + b*x + c = 0, ������� � ������������ �������
///
/// \warning ��� ������� �������� �������� ������������� �������
//}----------------------------------------------------------------------------

int SolveSquareEquation (double a, double b, double c, double *solutions);

//{----------------------------------------------------------------------------
/// \brief ������� ��� ��������� ���������� ���� double � ������������
/// \param x ������ �����
/// \param y ������ �����
/// \param accuracy ����������� ���������, �� ��������� ������ Accurancy
/// \return True, ���� ��� ����� ����� � ������ �����������, ����� False
//}----------------------------------------------------------------------------

bool CompareNumbers (double x, double y, double accuracy = Accuracy);

//-----------------------------------------------------------------------------

int SolveLinearEquation (double a, double b, double *solution)
{
    //{ ASSERT
    assert (isfinite (a) != 0);
    assert (isfinite (b) != 0);
    assert (solution    != NULL);
    //}

    int numSolutions = 0;

    if ( CompareNumbers (a, 0) )
    {
        if ( CompareNumbers(b, 0) )
        {
            numSolutions = Infinity;
        }
        else
        {
            numSolutions = 0;
        }
    }
    else
    {
        numSolutions = 1;

        *solution = (-b) / a;
    }

    return numSolutions;
}

//-----------------------------------------------------------------------------

int SolveSquareEquation (double a, double b, double c, double *solutions)
{
    //{ ASSERT
    assert (isfinite (a) != 0);
    assert (isfinite (b) != 0);
    assert (isfinite (c) != 0);
    assert (solutions    != NULL);
    //}

    int numSolutions = 0;

    //bx + c = 0
    if ( CompareNumbers (a, 0) )
    {
        numSolutions = SolveLinearEquation (b, c, solutions);

        return numSolutions;
    }

    double D = b*b - 4*a*c;

    if (Debug) printf ("line %d: D = %lf\n", __LINE__, D);

    if (D < 0)
    {
        numSolutions = 0;
    }
    else if ( CompareNumbers(D, 0) )
    {
        numSolutions = 1;

        solutions[0] = -b / (2*a);

        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wfloat-equal"

        if (solutions[0] == -0) solutions[0] = 0;

        #pragma GCC diagnostic pop

    }
    else
    {
        numSolutions = 2;

        solutions[0] = ( -b - sqrt(D) ) / (2*a);
        solutions[1] = ( -b + sqrt(D) ) / (2*a);
    }

    return numSolutions;
}

//-----------------------------------------------------------------------------

bool CompareNumbers (double x, double y, double accuracy)
{
    //{ ASSERT
    assert (isfinite (x)        != 0);
    assert (isfinite (y)        != 0);
    assert (isfinite (accuracy) != 0);
    //}

    bool isEqual = 0;

    if ( fabs (x - y) < accuracy )
    {
        isEqual = 1;
    }

    if (Debug) printf ("line %d: x - y = %lg; accuracy = %lg; isEqual = %d\n",
                       __LINE__, x - y, accuracy, isEqual);

    return isEqual;
}

//-----------------------------------------------------------------------------

#endif
