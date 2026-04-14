#include "DxLib.h"
#include "Tonbo.h"
#include <math.h>
#include"../Scene/InGameScene.h"


double t = 0.0;

void GetWeirdMotion(double t, int centerX, int centerY, int* x, int* y)
{
    *x = centerX
        + (int)(120.0 * sin(t * 1.3))
        + (int)(70.0 * cos(t * 2.1))
        + (int)(40.0 * sin(t * 3.7));

    *y = centerY
        + (int)(100.0 * cos(t * 1.1))
        + (int)(60.0 * sin(t * 2.9))
        + (int)(30.0 * cos(t * 4.3));
}

void TonboDraw(void)
{
  int x, y;
  GetWeirdMotion(t, 320, 240, &x, &y);

  DrawCircle(x, y, 20, GetColor(255, 100, 100), TRUE);
  t += 0.03;
}