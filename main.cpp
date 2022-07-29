#include "Config.h"

#include "SquareEquationLib.h"
#include "OptionsCmdLine.h"

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

void Help();
void RunUnitTests();
void Woooo();
void Meow();

bool RunOneUnitTest (double a,                double b, double c,
                     int    testNumSolutions, double *testSolutions,
                     int    testNumber);

//-----------------------------------------------------------------------------

const OptionDef Options[] = {{"-h",      Help},
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
    ProcessCommandLine (argc, argv, sizeof (Options) / sizeof (OptionDef), Options);

    double solutions[2] = {};

    double a = 0, b = 0, c = 0;

    EnterCoefficient(&a, &b, &c);

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

    while (true)
    {
        int numEnterNums = scanf ("%lf %lf %lf", a, b, c);

        if (numEnterNums == 3)
        {
            break;
        }

        ClearBuffer();

        printf ("Not correct input, repeat please...\n");
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
        printf ("No solutions\n");
    }
    else if (numSolutions == Infinity)
    {
        printf ("An infinite number of solutions\n");
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

void Help()
{
    printf ("\nDocumentation located in local path were opened: html/index.html\n\n");

    char option[] = "chrome file://html\\index.html";

    system (option);
}

//-----------------------------------------------------------------------------

void RunUnitTests()
{
    char path[_MAX_DIR] = "";

    printf ("Enter a path to file with unit tests...\n");
    fgets  (path, _MAX_DIR, stdin);

    FILE *file = fopen (path, "r");

    if (file == NULL)
    {
        printf ("An error occurred while opening the file!\n");

        return;
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

        else if (numRead != 3)
        {
            printf ("Incorrect coefficients in unit test number %d!\n", nowUnitTest);

            continue;
        }

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

    fclose (file);
}

//-----------------------------------------------------------------------------

void Woooo()
{
    char option[] = "chrome http://ded32.net.ru/woooo.mp3";

    system (option);
}

//-----------------------------------------------------------------------------

void Meow()
{
    char option[] = "chrome http://ded32.net.ru/meow.wav";

    system (option);
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

    bool noErrors = 1;

    double solutions[2] = {};

    int numSolutions = SolveSquareEquation (a, b, c, solutions);

    if (numSolutions != testNumSolutions)
    {
        noErrors = 0;
        printf ("%d: The number of solutions should be %d; program solution is %d\n",
                testNumber, testNumSolutions, numSolutions);
    }

    if (numSolutions == Infinity) return noErrors;

    if (testSolutions[1] < testSolutions[0])
    {
        std::swap (testSolutions[0], testSolutions[1]);
    }

    for (int i = 0; i < numSolutions; i++)
    {
        if (!CompareNumbers(testSolutions[i], solutions[i]))
        {
            printf ("%d: Solution should be %lf; program solution is %lf\n",
                    testNumber, testSolutions[i], solutions[i]);

            noErrors = 0;
        }
    }

    if (noErrors)
    {
        printf ("Unit test number %d have passed!\n", testNumber);
    }

    return noErrors;
}

//-----------------------------------------------------------------------------
