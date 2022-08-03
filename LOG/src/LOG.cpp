#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <stdarg.h>

#include "LOG.h"

int LogLvlTree = 0;
int Debug      = true;

FILE* LogFile = OpenLogFile();

//-----------------------------------------------------------------------------
//{ Class FunctionsCallTree implementation
//-----------------------------------------------------------------------------

FunctionsCallTree::FunctionsCallTree (const char* _funcName):
    funcName (_funcName)
{
    LogLvlTree++;
}

//-----------------------------------------------------------------------------

FunctionsCallTree::~FunctionsCallTree()
{
    LogLvlTree--;
}

//}
//-----------------------------------------------------------------------------

void _LOG (FILE* file, const char fileName[], const int line, const char str[], ...)
{
    va_list arg = {};
    va_start (arg, str);

    if (Debug)
    {
        if (file == stderr) fprintf (file, ">>>");

        fprintf    (file, "%02d", LogLvlTree);
        PutsSpaces (file, LogLvlTree * TabNumSym);

        LOG_INFO (file, fileName, line);
        vfprintf (file, str, arg);
        fputc    ('\n', file);
    }

    va_end (arg);
}

//-----------------------------------------------------------------------------

FILE* OpenLogFile (const char* path)
{
    atexit (&FinishLog);

    if ( !IsTTY (LogFile) )
    {
        fclose (LogFile);
    }

    LogFile = fopen (path, "a");

    return LogFile;
}

//-----------------------------------------------------------------------------

bool IsTTY (FILE* file)
{
    if (file == stdin || file == stderr || file == stdout)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//-----------------------------------------------------------------------------

void FinishLog()
{
    if (LogFile)
    {
        fputs ("End of Log!\n", LogFile);

        fclose (LogFile);
        LogFile = NULL;
    }
}

//-----------------------------------------------------------------------------

void SetDebug (bool isDebug)
{
    Debug = isDebug;
}

//-----------------------------------------------------------------------------

void PutsSpaces (FILE* file, int numSpaces)
{
    fprintf (file, "%*s", numSpaces, "");
}

//-----------------------------------------------------------------------------

