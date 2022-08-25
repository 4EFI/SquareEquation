#include "include/Config.h"

#include <stdio.h>
#include <assert.h>
#include <algorithm>
#include <locale.h>

#include "Math/SquareEquation.h"
#include "OptionsCmdLine/OptionsCmdLine.h"
#include "LOG/LOG.h"

#include "include/Input.h"
#include "include/OptionsSquareEq.h"
#include "include/UnitTestsSquareEq.h"

//-----------------------------------------------------------------------------

int main (int argc, const char *argv[])
{
    setlocale (LC_ALL, "");

    if (IsExplanation)
    {
        printf ("Данная программа решает квадратные уравнения. "
                "Она не решает круглые уравнения, сори:(((\n");
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
