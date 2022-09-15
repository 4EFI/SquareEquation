#include "Config.h"

#include <stdio.h>
#include <assert.h>
#include <windows.h>
#include <algorithm>
#include <locale.h>

#include "Math/SquareEquationLib.h"
#include "OptionsCmdLine/OptionsCmdLine.h"
#include "LOG/LOG.h"
#include "Input.h"

using std::isfinite;

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

void EnterCoefficient (double *a, double *b, double *c);

//{----------------------------------------------------------------------------
/// \brief ������� ��� ������ ������� ����������� ���������
/// \param numSolutions ���������� �������
/// \param *solutions ������ ������� ���������
//}----------------------------------------------------------------------------

void PrintSolutions (int numSolutions, double *solutions);

int Help         (int /*argc*/, const char* /*argv*/[], int   pos  );
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
    setlocale (LC_ALL, "");

    if (IsExplanation)
    {
    printf ("������ ��������� ������ ���������� ���������. "
            "��� �� ������ ������� ���������, ����:(((\n");
    }

    int numOption = ProcessCommandLine (argc,
					argv,
                                        sizeof (Options) / sizeof (Option),
                                        Options);
    if (numOption < 0) return -numOption;

    double solutions[2] = {};

    double a = 0, b = 0, c = 0;

    EnterCoefficient (&a, &b, &c);

    int numSolutions = SolveSquareEquation (a, b, c, solutions);

    FLOG ("%d", numSolutions);

    PrintSolutions (numSolutions, solutions);

    return 0;
}

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

        if (IsExplanation) printf ("������������ ����, ��������� �������...\n");
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
        if (IsExplanation) printf ("��� �������\n");
        else               printf ("0");
    }
    else if (numSolutions == Infinity)
    {
        if (IsExplanation) printf ("����������� ���������� �������\n");
        else               printf ("-1\n");
    }
    else
    {
        printf ("���������� ������� = %d\n", numSolutions);

        for (int i = 0; i < numSolutions; i++)
        {
            printf ("������� %d = %lf\n", i + 1, solutions[i]);
        }
    }
}

//-----------------------------------------------------------------------------
//{ Option Functions Implementation
//-----------------------------------------------------------------------------

int Help (int /*argc*/, const char* /*argv*/[], int pos)
{
    printf ("1) -t ��� --test ��������� ���� ����� �� �����. �� �������� ����� �������"
            " �������� ����� ����� �� ������ �����. ���� ��������� '.', �� ���� �����"
            " ����� ������� �� ���������� �����, ����� ���� ����� ������� �� ����������"
            " �����, ���� ������ ����� ����� ���������.\n"
            "2) -woooo ����������������\n"
            "3) -meow ���\n");

    return -pos;
}

//-----------------------------------------------------------------------------

int RunUnitTests(int argc, const char* argv[], int pos)
{
    const char pathDefault[] = "UnitTests.txt";

    FILE *file = NULL;

    //The last option in the list
    if ( pos == argc - 1 || (pos < (argc - 1) && strcmp(argv[pos + 1], ".") == 0) )
    {
        file = fopen (pathDefault, "r");

        if (!file)
        {
            printf ("������ ���� �� ����������!\n");

            return 0;
        }
    }
    else
    {
        file = fopen (argv[pos + 1], "r");
    }

    if (!file)
    {
        printf ("��������� ������ ��� �������� �����!\n");

        //The number of skipped arguments
        return 1;
    }

    double a = 0, b = 0, c = 0;

    int    numSolutions = 0;
    double solutions[2] = {};

    for (int nowUnitTest = 0; ; nowUnitTest++)
    {
	//  necessary function
        int numRead = fscanf (file, "%lf %lf %lf", &a, &b, &c);

        if (numRead == EOF)
        {
            printf ("����� ��������!\n");

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
