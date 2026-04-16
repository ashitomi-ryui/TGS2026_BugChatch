#include "DxLib.h"
#include "Tonbo.h"
#include <math.h>
#include"../Scene/InGameScene.h"

int x, y; // 円の描画位置
double t = 0.0;
// 不規則っぽく見える座標を計算する関数
void TonboMotion(double t, int centerX, int centerY, int* x, int* y)
{
    // x座標の計算
    *x = centerX
        + (int)(30.0 * sin(t * 0.1)) // 大きく速い揺れ
        + (int)(100.0 * cos(t * 0.7)) // 中くらいの揺れ
        + (int)(50.0 * sin(t * 0.9)); // 細かい揺れ


    //y座標の計算
    *y = centerY
        + (int)(10.0 * cos(t * 1.0)) // ゆっくりした上下
        + (int)(20.0 * sin(t * 0.9)) // 中くらいの揺れ
        + (int)(10.0 * cos(t * 0.3)); // 細かい揺れ
}
void TonboUpdate(float delta_second)
{

}
// 描画関数（毎フレーム呼ばれる）
void TonboDraw(void)
{
  

  // 現在の時間tから座標を計算
  TonboMotion(t, 550, 300, &x, &y);

  // 円を描画（赤っぽい色）
  DrawCircle(x, y, 20, GetColor(255, 100, 100), TRUE);

  // 時間を進める（これが無いと動かない）
  t += 0.03;
}

int TonboLocation(void)
{
    return x, y;
}