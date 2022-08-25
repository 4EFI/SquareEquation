#ifndef OPTIONS_SQUARE_EQ_H
#define OPTIONS_SQUARE_EQ_H

#include "../OptionsCmdLine/OptionsCmdLine.h"

//-----------------------------------------------------------------------------

int Help         (int /*argc*/, const char* /*argv*/[], int   pos  );
int RunUnitTests (int   argc,   const char*   argv  [], int   pos  );
int Woooo        (int /*argc*/, const char* /*argv*/[], int /*pos*/);
int Meow         (int /*argc*/, const char* /*argv*/[], int /*pos*/);

//-----------------------------------------------------------------------------

const Option Options[] = {{"-h",      Help},
                          {"/h",      Help},
                          {"--help",  Help},
                          {"/?",      Help},
                          {"-t",      RunUnitTests},
                          {"--test",  RunUnitTests},
                          {"--woooo", Woooo},
                          {"--meow",  Meow}};

//-----------------------------------------------------------------------------

#endif
