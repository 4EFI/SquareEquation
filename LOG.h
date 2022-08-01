#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <io.h>

//-----------------------------------------------------------------------------

const int MaxStr    = 100;
const int TabNumSym = 4;

static int lvlTree = 0;

int Debug = true;

FILE* OpenLogFile (const char* path = "LOG.txt");

static FILE* LogFile = OpenLogFile();

//-----------------------------------------------------------------------------

class FunctionsCallTree
{
public:
    FunctionsCallTree (const char* _funcName);
   ~FunctionsCallTree();

private:
    const char* funcName = NULL;
};

//-----------------------------------------------------------------------------
//{ Class FunctionsCallTree implementation
//-----------------------------------------------------------------------------

FunctionsCallTree::FunctionsCallTree (const char* _funcName):
    funcName (_funcName)
{
    lvlTree++;
}

//-----------------------------------------------------------------------------

FunctionsCallTree::~FunctionsCallTree()
{
    lvlTree--;
}

//}
//-----------------------------------------------------------------------------

bool IsTTY (FILE* file);

void FinishLog();

void SetDebug (bool isDebug);

void PutsSpaces (FILE* file, int numSpaces);

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

#define LOG_INFO(file) \
    fprintf (file, "%s:%d: ", __FILE__, __LINE__);

#define _LOG(file, str, ...)                    \
{                                               \
    if (Debug)                                  \
    {                                           \
        fprintf    (file, "%02d", lvlTree);     \
        PutsSpaces (file, lvlTree * TabNumSym); \
                                                \
        LOG_INFO (file);                        \
        fprintf  (file, str, ##__VA_ARGS__);    \
        fputc    ('\n', file);                  \
    }                                           \
}

#define FLOG(str, ...)                  \
    _LOG (LogFile, str, ##__VA_ARGS__); \

#define LOG(str, ...)                   \
{                                       \
    _LOG (LogFile, str, ##__VA_ARGS__); \
    _LOG (stderr,  str, ##__VA_ARGS__); \
}

#define $(str)                                    \
{                                                 \
    if (Debug)                                    \
    {                                             \
        PutsSpaces (stderr, lvlTree * TabNumSym); \
                                                  \
        FLOG (#str);                              \
        str;                                      \
    }                                             \
}

#define $funcsTree                                      \
    FunctionsCallTree __funcsTree(__PRETTY_FUNCTION__); \

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

#endif
