#include "DxLib.h"
#include "Tonbo.h"
#include <math.h>
#include"../Scene/InGameScene.h"


double t = 0.0;
// 不規則っぽく見える座標を計算する関数
void TonboMotion(double t, int centerX, int centerY, int* x, int* y)
{
    // x座標の計算
    *x = centerX
        + (int)(120.0 * sin(t * 0.5)) // 大きく速い揺れ
        + (int)(70.0 * cos(t * 1.1)) // 中くらいの揺れ
        + (int)(10.0 * sin(t * 0.7)); // 細かい揺れ


    //y座標の計算
    *y = centerY
        + (int)(100.0 * cos(t * 1.1)) // ゆっくりした上下
        + (int)(60.0 * sin(t * 0.9)) // 中くらいの揺れ
        + (int)(30.0 * cos(t * 0.3)); // 細かい揺れ
}

// 描画関数（毎フレーム呼ばれる）
void TonboDraw(void)
{
  int x, y; // 円の描画位置

  // 現在の時間tから座標を計算
  TonboMotion(t, 320, 240, &x, &y);

  // 円を描画（赤っぽい色）
  DrawCircle(x, y, 20, GetColor(255, 100, 100), TRUE);

  // 時間を進める（これが無いと動かない）
  t += 0.03;
}