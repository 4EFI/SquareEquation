#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "../include/OptionsSquareEq.h"
#include "../include/UnitTestsSquareEq.h"
#include "../Math/SquareEquationLib.h"

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

    // ��������� ����� � ������
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

//-----------------------------------------------------------------------------

