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

/// \brief Константа бесконечности
const int    Infinity = 9999999;

/// \brief Константа точности
const double Accuracy = 10e-6;

//-----------------------------------------------------------------------------

//{----------------------------------------------------------------------------
/// \brief Функция для решения линейного уравнения
///
/// \param a первый коэффицент линейного уравнения
/// \param b второй коэффицент линейного уравнения
/// \param *solution указатель решения линейного уравнений
///
/// \return Возвращает количество решений уравнения
///
/// \note Функция принимает коэффиценты линейного уравнения типа a*x + b = 0
///
/// \warning Эта функция изменяет элементы передаваемой переменной
///          для записи решения
//}----------------------------------------------------------------------------

int SolveLinearEquation (double a, double b, double *solution);

//{----------------------------------------------------------------------------
/// \brief Функция для решения квадратного уравнения
///
/// \param a первый коэффицент квадратного уравнения
/// \param b второй коэффицент квадратного уравнения
/// \param c третий коэффицент квадратного уравнения
/// \param *solutions массив решений квадратного уравнений
///
/// \return Возвращает количество решений уравнения
///
/// \note Функция принимает коэффиценты квадратного уравнения типа
///       a*x^2 + b*x + c = 0, выводит в передаваемый массивв
///
/// \warning Эта функция изменяет элементы передаваемого массива
//}----------------------------------------------------------------------------

int SolveSquareEquation (double a, double b, double c, double *solutions);

//{----------------------------------------------------------------------------
/// \brief Функция для сравнения переменных типа double с погрешностью
/// \param x первое число
/// \param y второе число
/// \param accuracy погрешность сравнения, по умолчанию равная Accurancy
/// \return True, если два числа равны с учетом погрешности, иначе False
//}----------------------------------------------------------------------------

bool CompareNumbers (double x, double y, double accuracy = Accuracy);

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

        return 1;
    }

    return -1;
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

    if (Debug) printf ("line %d: D = %lf\n", __LINE__, D);

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
        solutions[0] = ( -b - sqrt(D) ) / (2*a);
        solutions[1] = ( -b + sqrt(D) ) / (2*a);

        return 2;
    }

    return -1;
}

//-----------------------------------------------------------------------------

bool CompareNumbers (double x, double y, double accuracy)
{
    //{ ASSERT
    assert (isfinite (x)        != 0);
    assert (isfinite (y)        != 0);
    assert (isfinite (accuracy) != 0);
    //}

    return ( fabs (x - y) < accuracy );
}

//-----------------------------------------------------------------------------

#endif
