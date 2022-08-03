#include "Config.h"

#include "SquareEquationLib.h"
#include "OptionsCmdLine/OptionsCmdLine.h"
#include "LOG/LOG.h"

//-----------------------------------------------------------------------------

//{----------------------------------------------------------------------------
/// \brief Функция для ввода коэффицентов
///
/// \param *a указатель на первый коэффицент квадратного уравнения
/// \param *b указатель на второй коэффицент квадратного уравнения
/// \param *c указатель на третий коэффицент квадратного уравнения
///
/// \note При некорректном вводе данных,
///       программа просит пользователя повторно их ввести
///
/// \warning Эта функция изменяет значения вводимых переменных
//}----------------------------------------------------------------------------

void EnterCoefficient (double *a, double *b, double *c);

//{----------------------------------------------------------------------------
/// \brief Функция для вывода решений квадратного уравнения
/// \param numSolutions количество решений
/// \param *solutions массив рещений уравнения
//}----------------------------------------------------------------------------

void PrintSolutions (int numSolutions, double *solutions);

int Help         (int /*argc*/, const char* /*argv*/[], int /*pos*/);
int RunUnitTests (int   argc,   const char*   argv  [], int   pos  );
int Woooo        (int /*argc*/, const char* /*argv*/[], int /*pos*/);
int Meow         (int /*argc*/, const char* /*argv*/[], int /*pos*/);

bool RunOneUnitTest (double a,                double b, double c,
                     int    testNumSolutions, double *testSolutions,
                     int    testNumber);

//-----------------------------------------------------------------------------

const Option Options[] = {{"-h",      Help},
                          {"/h",      Help},
                          {"--help",  Help},
                          {"/?",      Help},
                          {"-t",      RunUnitTests},
                          {"--test",  RunUnitTests},
                          {"--woooo", Woooo},
                          {"--meow",  Meow}};

//-----------------------------------------------------------------------------

int main (int argc, const char *argv[])
{
    if (IsExplanation)
    {
        printf ("This program solves square equations. "
                "It does not solve round equations, sorry :(((\n");
    }

    int numOption = ProcessCommandLine (argc, argv,
                                        sizeof (Options) / sizeof (Option),
                                        Options);
    if (numOption < 0) return -numOption;

    double solutions[2] = {};

    double a = 0, b = 0, c = 0;

    EnterCoefficient (&a, &b, &c);

    $setFuncsTree

    int numSolutions = SolveSquareEquation (a, b, c, solutions);

    PrintSolutions (numSolutions, solutions);

    return 0;
}

//-----------------------------------------------------------------------------

void EnterCoefficient (double *a, double *b, double *c)
{
    //{ ASSERT
    assert (a != NULL);
    assert (b != NULL);
    assert (c != NULL);
    //}

    if (IsExplanation) printf ("Enter coefficients a b c...\n");

    while (true)
    {
        int numEnterNums = scanf ("%lf %lf %lf", a, b, c);

        if (numEnterNums == 3)
        {
            break;
        }

        ClearBuffer();

        if (IsExplanation) printf ("Not correct input, repeat please...\n");
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
        if (IsExplanation) printf ("No solutions\n");
        else               printf ("0");
    }
    else if (numSolutions == Infinity)
    {
        if (IsExplanation) printf ("An infinite number of solutions\n");
        else               printf ("-1\n");
    }
    else
    {
        printf ("Number of solutions = %d\n", numSolutions);

        for (int i = 0; i < numSolutions; i++)
        {
            printf ("Solution %d = %lf\n", i + 1, solutions[i]);
        }
    }
}

//-----------------------------------------------------------------------------
//{ Option Functions Implementation
//-----------------------------------------------------------------------------

int Help (int /*argc*/, const char* /*argv*/[], int /*pos*/)
{
    printf ("\nDocumentation located in local path were opened: html/index.html\n\n");

    char option[] = "chrome file://html\\index.html";

    system (option);

    return 0;
}

//-----------------------------------------------------------------------------

int RunUnitTests(int argc, const char* argv[], int pos)
{
    const char pathDefault[] = "UnitTests.txt";

    FILE *file = NULL;

    //The last option in the list
    if (pos == argc - 1)
    {
        file = fopen (pathDefault, "r");

        if (!file)
        {
            printf ("Default file does not exist!\n");

            return 0;
        }
    }
    else
    {
        file = fopen (argv[pos + 1], "r");
    }

    if (!file)
    {
        printf ("An error occurred while opening the file!\n");

        //The number of skipped arguments
        return 1;
    }

    double a = 0, b = 0, c = 0;

    int    numSolutions = 0;
    double solutions[2] = {};

    for (int nowUnitTest = 0; ; nowUnitTest++)
    {
        int numRead = fscanf (file, "%lf %lf %lf", &a, &b, &c);

        if (numRead == EOF)
        {
            printf ("Tests completed!\n");

            break;
        }
        else
        {
            fscanf (file, "%d", &numSolutions);

            if (numSolutions != Infinity)
            {
                for (int i = 0; i < numSolutions; i++)
                {
                    fscanf (file, "%lf", &solutions[i]);
                }
            }

            RunOneUnitTest (a, b, c, numSolutions, solutions, nowUnitTest);
        }
    }

    fclose (file);

    return -pos;
}

//-----------------------------------------------------------------------------

int Woooo(int /*argc*/, const char* /*argv*/[], int /*pos*/)
{
    char option[] = "chrome http://ded32.net.ru/woooo.mp3";

    system (option);

    return 0;
}

//-----------------------------------------------------------------------------

int Meow(int /*argc*/, const char* /*argv*/[], int /*pos*/)
{
    char option[] = "chrome http://ded32.net.ru/meow.wav";

    system (option);

    return 0;
}

//}
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
        printf ("%d: The number of solutions should be %d; program solution is %d\n",
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
            printf ("%d: Solution should be %lf; program solution is %lf\n",
                    testNumber, testSolutions[i], solutions[i]);

            return 0;
        }
    }

    testPassed:
    printf ("Unit test number %d have passed!\n", testNumber);

    return 1;
}

//-----------------------------------------------------------------------------
