#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <io.h>

//-----------------------------------------------------------------------------

int CurrentLogLine = 0;

FILE* OpenLogFile (const char* path = "LOG.txt");

static FILE* LogFile = OpenLogFile();

//-----------------------------------------------------------------------------

bool IsTTY (FILE* file);

void FinishLog();

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

#define FLOG(str, ...)                    \
{                                         \
    LOG_INFO (LogFile);                   \
    fprintf  (LogFile, str, __VA_ARGS__); \
    fputc    ('\n', LogFile);             \
}

#define LOG(str, ...)                    \
{                                        \
    FLOG     (str, __VA_ARGS__);         \
                                         \
    LOG_INFO (stderr);                   \
    fprintf  (stderr, str, __VA_ARGS__); \
    fputc    ('\n', stderr);             \
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

#endif
