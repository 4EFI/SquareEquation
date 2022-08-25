#include "TXLib.h"

void DrawFunc(int color, double (*func)(double x));

int main()
{
    txCreateWindow (800, 600);

    DrawFunc(TX_WHITE,      sin);
    DrawFunc(TX_YELLOW,     cos);
    DrawFunc(TX_LIGHTGREEN, tan);

    return 0;
}

void DrawFunc(int color, double (*func)(double x))
{
    txSetColor    (color);
    txSetFillColor(color);

    for(double x = -10; x < +10; x += 0.001)
    {
        double y = func(x);

        txCircle(x*100 + 800/2, -y*100 + 600/2, 2);
    }
}
