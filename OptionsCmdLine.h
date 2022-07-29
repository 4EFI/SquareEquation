#ifndef OPTIONS_CMD_LINE_H
#define OPTIONS_CMD_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <algorithm>

// --test "name" 5 --help
// --test "name" 5 10 --help
// --test "name" --help

//-----------------------------------------------------------------------------

struct OptionDefZSR
{
    const char* name;

    int (*func)(int argc, const char *argv[], int pos);
};

//-----------------------------------------------------------------------------

void ProcessCommandLine (int argc,       const char*     argv[],
                         int numOptions, const OptionDef options[]);

int NumWordInArray (const char* word, int sizeArr, const char* arr[]);

//-----------------------------------------------------------------------------

int ProcessCommandLine (int argc,       const char*     argv[],
                         int numOptions, const OptionDef options[])
{
    //{ ASSERT
    assert (argv != NULL);
    //}

    int optionNum = 0;

    for (int numArg = 1; numArg < argc; numArg++)
    {
        printf("Num arg %d: (%s)\n", numArg, argv[numArg]);

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
            int numSkips = options[optionNum].func();

            if (numSkips < 0) return numSkips;

            numArg += numSkips;
        }
    }
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

#endif
