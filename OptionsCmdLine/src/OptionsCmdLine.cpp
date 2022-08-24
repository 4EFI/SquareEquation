#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <algorithm>

#include "../OptionsCmdLine.h"

//-----------------------------------------------------------------------------

int ProcessCommandLine (int argc,       const char*     argv[],
                        int numOptions, const Option options[])
{
    //{ ASSERT
    assert (argv != NULL);
    //}

    int optionNum = 0;

    for (int numArg = 1; numArg < argc; numArg++)
    {
        optionNum = -1;

        for (int i = 0; i < numOptions; i++)
        {
            if ( strcmp (options[i].name, argv[numArg]) == 0 )
            {
                optionNum = i;
            }
        }

        if (optionNum == -1)
        {
            printf ("Option \"%s\" does not exist!\n", argv[numArg]);
        }
        else
        {
	    // arg_to_skip
	    // 
            int numSkips = options[optionNum].func (argc, argv, numArg);

            if (numSkips < 0) return numSkips;

            numArg += numSkips;
        }
    }

    return 0;
}

//-----------------------------------------------------------------------------

int NumWordInArray (const char* word, int sizeArr, const char* arr[])
{
    //{ ASSERT
    assert (word != NULL);
    assert (arr  != NULL);
    //}

    for (int i = 0; i < sizeArr; i++)
    {
        if (strcmp (word, arr[i]) == 0)
        {
            return i;
        }
    }

    return -1;
}

//-----------------------------------------------------------------------------
