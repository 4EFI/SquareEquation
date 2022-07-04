//{----------------------------------------------------------------------------
/// @file SquareEquation.cpp
/// @mainpage
/// Files:
/// - @ref SquareEquation.cpp
//}----------------------------------------------------------------------------

#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <TXLib.h>

//-----------------------------------------------------------------------------

/// \brief ��������� �������������
const int    Infinity = 9999999;

/// \brief ��������� ��������
const double Accuracy = 10e-6;

const int    Debug    = false;

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

int SolveLinearEquation(double a, double b, double *solution);

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

int SolveSquareEquation(double a, double b, double c, double *solutions);

//{----------------------------------------------------------------------------
/// \brief ������� ��� ������ ������� ����������� ���������
/// \param numSolutions ���������� �������
/// \param *solutions ������ ������� ���������
//}----------------------------------------------------------------------------

void PrintSolutions(int numSolutions, double *solutions);

//{----------------------------------------------------------------------------
/// \brief ������� ��� ��������� ���������� ���� double � ������������
/// \param x ������ �����
/// \param y ������ �����
/// \param accuracy ����������� ���������, �� ��������� ������ Accurancy
/// \return True, ���� ��� ����� ����� � ������ �����������, ����� False
//}----------------------------------------------------------------------------

bool CompareNumbers(double x, double y, double accuracy = Accuracy);

//{----------------------------------------------------------------------------
/// \brief ������� ��� ����� ������������
///
/// \param *a ��������� �� ������ ���������� ����������� ���������
/// \param *b ��������� �� ������ ���������� ����������� ���������
/// \param *c ��������� �� ������ ���������� ����������� ���������
///
/// \note ��� ������������ ����� ������,
///       ��������� ������ ������������ �������� �� ������
///
/// \warning ��� ������� �������� �������� �������� ����������
//}----------------------------------------------------------------------------

void EnterCoefficient(double *a, double *b, double *c);

bool UnitTestsSquareEquation(double  a,                double b, double c,
                             int     testNumSolutions, double *testSolutions,
                             int     testNumber);

//{----------------------------------------------------------------------------
/// \brief ������� ��� ������� ������� �������� ������
//}----------------------------------------------------------------------------

void ClearBuffer();

//-----------------------------------------------------------------------------

int main()
{
    double solutions[2] = {};

    double a = 0, b = 0, c = 0;

    EnterCoefficient(&a, &b, &c);

    int numSolutions = SolveSquareEquation(a, b, c, solutions);

    PrintSolutions(numSolutions, solutions);

    /*
    UnitTestsSquareEquation(0, 0,  0,  Infinity, nullptr, 1);

    double arr_1[2] = {-3, 1};
    UnitTestsSquareEquation(1, 2, -3,  2,        arr_1,   2);
    */
}

//-----------------------------------------------------------------------------

int SolveLinearEquation(double a, double b, double *solution)
{
    int numSolutions = 0;

    if (CompareNumbers(a, 0))
    {
        if(CompareNumbers(b, 0))
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

int SolveSquareEquation(double a, double b, double c, double *solutions)
{
    int numSolutions = 0;

    //bx + c = 0
    if ( CompareNumbers(a, 0) )
    {
        numSolutions = SolveLinearEquation(b, c, solutions);

        return numSolutions;
    }

    double D = b*b - 4*a*c;

    if (Debug) printf("line %d: D = %lf\n", __LINE__, D);

    if (D < 0)
    {
        numSolutions = 0;
    }
    else if (CompareNumbers(D, 0))
    {
        numSolutions = 1;

        solutions[0] = -b / (2*a);

        if (solutions[0] == -0) solutions[0] = 0;
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

void PrintSolutions(int numSolutions, double *solutions)
{
    if (numSolutions == 0)
    {
        printf("None solutions\n");
    }
    else if (numSolutions == Infinity)
    {
        printf("An infinite number of solutions\n");
    }
    else
    {
        printf("Number of solutions = %d\n", numSolutions);

        for (int i = 0; i < numSolutions; i++)
        {
            printf("Solution %d = %lf\n", i + 1, solutions[i]);
        }
    }
}

//-----------------------------------------------------------------------------

bool CompareNumbers(double x, double y, double accuracy)
{
    bool isEqual = 0;

    if (fabs(x - y) < accuracy)
    {
        isEqual = 1;
    }

    if (Debug) printf("line %d: x - y = %lg; accuracy = %lg; isEqual = %d\n",
                      __LINE__, x - y, accuracy, isEqual);

    return isEqual;
}

//-----------------------------------------------------------------------------

void EnterCoefficient(double *a, double *b, double *c)
{
    while(true)
    {
        int numEnterNums = scanf("%lf %lf %lf", a, b, c);

        if (numEnterNums == 3)
        {
            break;
        }

        ClearBuffer();

        printf("Not correct enter, repeat please...\n");
    }
}

//-----------------------------------------------------------------------------

bool UnitTestsSquareEquation(double  a,                double b, double c,
                             int     testNumSolutions, double *testSolutions,
                             int     testNumber)
{
    bool noErrors = 1;

    double solutions[2] = {};

    int numSolutions = SolveSquareEquation(a, b, c, solutions);

    if (numSolutions != testNumSolutions)
    {
        noErrors = 0;
        printf("%d: The number of solutions should be %d; program solution is %d\n",
               testNumber, testNumSolutions, numSolutions);
    }

    if (numSolutions == Infinity) return noErrors;

    if (testSolutions[1] < testSolutions[0])
    {
        std::swap(testSolutions[0], testSolutions[1]);
    }

    for (int i = 0; i < numSolutions; i++)
    {
        if (!CompareNumbers(testSolutions[i], solutions[i]))
        {
            printf("%d: Solution should be %lf; program solution is %lf\n",
                   testNumber, testSolutions[i], solutions[i]);

            noErrors = 0;
        }
    }

    return noErrors;
}

//-----------------------------------------------------------------------------

void ClearBuffer()
{
    while(getchar() != '\n') ;
}

//-----------------------------------------------------------------------------
