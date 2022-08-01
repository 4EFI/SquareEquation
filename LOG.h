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
    printf ("<");

    lvlTree++;
}

//-----------------------------------------------------------------------------

FunctionsCallTree::~FunctionsCallTree()
{
    lvlTree--;

    printf (">");
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

#define _LOG(file)
{

}

#define FLOG(str, ...)                             \
{                                                  \
    if (Debug)                                     \
    {                                              \
        fprintf (LogFile, "%2d", lvlTree)          \
        PutsSpaces (LogFile, lvlTree * TabNumSym); \
                                                   \
        LOG_INFO (LogFile);                        \
        fprintf  (LogFile, str, ##__VA_ARGS__);    \
        fputc    ('\n', LogFile);                  \
    }                                              \
}

#define LOG(str, ...)                          \
{                                              \
    if (Debug)                                 \
    {                                          \
        FLOG     (str, __VA_ARGS__);           \
                                               \
        LOG_INFO (stderr);                     \
        fprintf  (stderr, str, ##__VA_ARGS__); \
        fputc    ('\n', stderr);               \
    }                                          \
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
