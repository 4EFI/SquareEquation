#ifndef OPTIONS_CMD_LINE_H
#define OPTIONS_CMD_LINE_H

//-----------------------------------------------------------------------------

struct Option
{
    const char* name;

    int (*func)(int argc, const char *argv[], int pos);
};

//-----------------------------------------------------------------------------

int ProcessCommandLine (int argc,       const char*     argv[],
                        int numOptions, const Option options[]);

int NumWordInArray (const char* word, int sizeArr, const char* arr[]);

//-----------------------------------------------------------------------------

#endif
