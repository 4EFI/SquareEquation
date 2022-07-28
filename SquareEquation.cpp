//{----------------------------------------------------------------------------
/// @file SquareEquation.cpp
/// @mainpage
/// Files:
/// - @ref SquareEquation.cpp
//}----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
#include "SquareEquation.h"

using std::isfinite;

//-----------------------------------------------------------------------------

int main(int argc, const char *argv[])
{
    ProcessCommandLine(argc, argv, sizeof(Options) / sizeof(OptionDef), Options);

    double solutions[2] = {};

    double a = 0, b = 0, c = 0;

    EnterCoefficient(&a, &b, &c);

    int numSolutions = SolveSquareEquation(NAN, b, c, solutions);

    PrintSolutions(numSolutions, solutions);

    return 0;
}

//-----------------------------------------------------------------------------

int SolveLinearEquation(double a, double b, double *solution)
{
    //{ ASSERT
    assert(isfinite(a) != 0);
    assert(isfinite(b) != 0);
    assert(solution    != NULL);
    //}

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
    //{ ASSERT
    assert(isfinite(a) != 0);
    assert(isfinite(b) != 0);
    assert(isfinite(c) != 0);
    assert(solutions   != NULL);
    //}

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
    //{ ASSERT
    assert(solutions != NULL);
    //}

    if (numSolutions == 0)
    {
        printf("No solutions\n");
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
    //{ ASSERT
    assert(isfinite(x)        != 0);
    assert(isfinite(y)        != 0);
    assert(isfinite(accuracy) != 0);
    //}

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
    //{ ASSERT
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
    //}

    while (true)
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
    //{ ASSERT
    assert(isfinite(a)   != 0);
    assert(isfinite(b)   != 0);
    assert(isfinite(c)   != 0);
    assert(testSolutions != NULL);
    //}

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

    if(noErrors)
    {
        printf("Unit test number %d have passed!\n", testNumber);
    }

    return noErrors;
}

//-----------------------------------------------------------------------------

void ClearBuffer()
{
    while(getchar() != '\n') ;
}

//-----------------------------------------------------------------------------

void ProcessCommandLine(int argc,       const char*     argv[],
                        int numOptions, const OptionDef options[])
{
    //{ ASSERT
    assert(argv != NULL);
    //}

    int optionNum = 0;

    for(int i = 1; i < argc; i++)
    {
        optionNum = -1;

        for(int j = 0; j < numOptions; j++)
        {
            if(strcmp(options[j].nameOption, argv[i]) == 0)
            {
                optionNum = j;
            }
        }

        if(optionNum == -1)
        {
            printf("Option %s does not exist!\n", argv[i]);
        }
        else
        {
            options[optionNum].func();
        }
    }
}

//-----------------------------------------------------------------------------

int NumWordInArray(const char* word, int sizeArr, const char* arr[])
{
    //{ ASSERT
    assert(word != NULL);
    assert(arr  != NULL);
    //}

    for(int i = 0; i < sizeArr; i++)
    {
        if(strcmp(word, arr[i]) == 0)
        {
            return i;
        }
    }

    return -1;
}

//-----------------------------------------------------------------------------

void Help()
{
    printf("\nDocumentation located in local path were opened: html/index.html\n\n");

    char option[] = "chrome file://C:\\Users\\kvv20\\OneDrive\\Documents\\SquareEquation\\html\\index.html";

    system(option);
}

//-----------------------------------------------------------------------------

void RunUnitTests()
{
    char path[] = "";

    printf("Enter a path to file with unit tests...\n");
    scanf("%s", path);

    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        printf("An error occurred while opening the file!\n");

        return;
    }

    double a = 0, b = 0, c = 0;

    int    numSolutions = 0;
    double solutions[2] = {};

    for(int nowUnitTest = 0; ; nowUnitTest++)
    {
        int numRead = fscanf(file, "%lf %lf %lf", &a, &b, &c);

        if (numRead == EOF)
        {
            printf("Tests completed!\n");

            break;
        }

        else if (numRead != 3)
        {
            printf("Incorrect coefficients in unit test number %d!\n", nowUnitTest);

            continue;
        }

        fscanf(file, "%d", &numSolutions);

        if(numSolutions != Infinity)
        {
            for(int i = 0; i < numSolutions; i++)
            {
                fscanf(file, "%lf", &solutions[i]);
            }
        }

        UnitTestsSquareEquation(a, b, c, numSolutions, solutions, nowUnitTest);
    }

    fclose(file);
}

//-----------------------------------------------------------------------------

void Woooo()
{
    char option[] = "chrome http://ded32.net.ru/woooo.mp3";

    system(option);
}

//-----------------------------------------------------------------------------

void Meow()
{
    char option[] = "chrome http://ded32.net.ru/meow.wav";

    system(option);
}

//-----------------------------------------------------------------------------
