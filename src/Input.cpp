#include "../include/Config.h"

#include <stdio.h>
#include <assert.h>

#include "../LOG/LOG.h"
#include "../include/Input.h"
#include "../Math/SquareEquationLib.h"

//-----------------------------------------------------------------------------

void EnterCoefficient (double *a, double *b, double *c)
{
    $LOG_LVL_UP

    //{ ASSERT
    assert (a != NULL);
    assert (b != NULL);
    assert (c != NULL);
    //}

    FLOG ("True conditions");

    if (IsExplanation) printf ("Enter coefficients a b c...\n");

    while (true)
    {
        int numEnterNums = scanf ("%lf %lf %lf", a, b, c);

        if (numEnterNums == 3)
        {
            break;
        }

        ClearBuffer();

        if (IsExplanation) printf ("Некорректный ввод, повторите попытку...\n");
    }
}

//-----------------------------------------------------------------------------

void PrintSolutions (int numSolutions, double *solutions)
{
    //{ ASSERT
    assert (solutions != NULL);
    //}

    if (numSolutions == 0)
    {
        if (IsExplanation) printf ("Нет решений\n");
        else               printf ("0");
    }
    else if (numSolutions == Infinity)
    {
        if (IsExplanation) printf ("Бесконечное количество решений\n");
        else               printf ("-1\n");
    }
    else
    {
        printf ("Количество решений = %d\n", numSolutions);

        for (int i = 0; i < numSolutions; i++)
        {
            printf ("Решения %d = %lf\n", i + 1, solutions[i]);
        }
    }
}

//-----------------------------------------------------------------------------

void ClearBuffer()
{
    while (getchar() != '\n') {;}
}

//-----------------------------------------------------------------------------
