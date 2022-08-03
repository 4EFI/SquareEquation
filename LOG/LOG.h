#ifndef LOG_H
#define LOG_H

#include <stdio.h>

//-----------------------------------------------------------------------------

const int MaxStr    = 100;
const int TabNumSym = 4;

extern int LogLvlTree;

extern int Debug;

FILE* OpenLogFile (const char* path = "LOG.txt");

extern FILE* LogFile;

//-----------------------------------------------------------------------------

struct FunctionsCallTree
{
public:
    FunctionsCallTree (const char* _funcName);
   ~FunctionsCallTree();

private:
    const char* funcName = NULL;
};

//-----------------------------------------------------------------------------

void _LOG (FILE* file, const char fileName[], const int line, const char str[], ...);

bool IsTTY (FILE* file);

void FinishLog();

void SetDebug (bool isDebug);

void PutsSpaces (FILE* file, int numSpaces);

//-----------------------------------------------------------------------------

#define LOG_INFO(file, fileName, line) \
    fprintf (file, "%s:%d: ", fileName, line);


/*
#define _LOG(file, str, ...)                         \
{                                                    \
    if (Debug)                                       \
    {                                                \
        if ((file) == stderr) fprintf (file, ">>>"); \
        fprintf    (file, "%02d", LogLvlTree);       \
        PutsSpaces (file, LogLvlTree * TabNumSym);   \
                                                     \
        LOG_INFO (file);                             \
        fprintf  (file, str, ##__VA_ARGS__);         \
        fputc    ('\n', file);                       \
    }                                                \
}
*/

#ifndef NLOG

#define FLOG(str, ...)                                      \
    _LOG (LogFile, __FILE__, __LINE__, str, ##__VA_ARGS__); \

#define LOG(str, ...)                                      \
{                                                          \
    FLOG (str, ##__VA_ARGS__);                             \
    _LOG (stderr, __FILE__, __LINE__, str, ##__VA_ARGS__); \
}

#define $$(code)  \
{                 \
    FLOG (#code); \
    code;         \
}

#define $LOG_LVL_UP \
    FunctionsCallTree __funcsTree(__PRETTY_FUNCTION__);

#else

#define FLOG(str, ...) ;
#define  LOG(str, ...) ;

#define $$(code) ;

#define $LOG_LVL_UP ;

#endif

//-----------------------------------------------------------------------------

#endif
