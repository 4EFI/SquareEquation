#define _TX_ALLOW_TRACE 9

#include "TXLib.h"

int main()
{
    txCreateWindow (800, 600);

    while (1)
        {
        if (GetAsyncKeyState (VK_SPACE)) *(int*)NULL = 0;
        txSleep();
        }

    return 0;
}
