#include "DxLib.h"
#include "Tonbo.h"
#include "Bug.h"
#include <math.h>
#include"../Scene/InGameScene.h"
#include"../Utilitys/Camera.h"

int x, y;
int TonboDestroy;
Vector2D tonbo; // 円の描画位置
Bug* tonboscore;
int TonboRespawn = 0;
float tonborespawntime = 0;
static int tonbocount = 0;
int now_tonbo = 0;
int old_tonbo = 0;
double t = 0.0;
int tonbofukkatu = 0;
// 不規則っぽく見える座標を計算する関数
void Tonbo::TonboMotion(double t, int centerX, int centerY, int* x, int* y)
{
    TonboDestroy = TRUE;
   /* if (tonboscore->GetTonboScore() == 1)
    {
        TonboDestroy = FALSE;
    }*/

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
void Tonbo::TonboUpdate(float delta_second)
{

    //tonbocount = GetRand(3);
    now_tonbo = tonboscore->GetTonboScore();
    //今のスコアと昔のスコアの差が0より大きかったら入る
    if (now_tonbo - old_tonbo > 0)
    {
        
        
     
        if (tonbofukkatu == 0)
        {
            TonboDestroy = FALSE;
            x = -1000;
            y = -1000;
            //座標を画面外へ移動
            tonbo = { -1000.0f,1000.0f };
            //トンボの描画を停止
            TonboDestroy = FALSE;
            tonborespawntime = 0.0f;
            tonbofukkatu = 1;
            tonbocount = GetRand(2);
            tonborespawntime = 0;  //リスポーン時間のカウントの数値を初期化
            tonbofukkatu = 1;
        }
        //リスポーン時間加算
        tonborespawntime += delta_second;
        //一秒立ったら再描画
        if (tonborespawntime >= 1.0f)
        {
            TonboDestroy = TRUE;
            old_tonbo = now_tonbo;   //昔のスコアに現在スコアを代入
            tonbofukkatu = 0;
        }
    }
    else
    {
        switch (tonbocount)
        {
        case 0:
            
                TonboMotion(t, 550, 300, &x, &y);
                TonboRespawn = 1;
                t += 0.03;

            
            break;
        case 1:
            
                TonboMotion(t, 1000, 300, &x, &y);
                TonboRespawn = 2;
                t += 0.03;
                break;
        case 2:
            TonboMotion(t, 1000, 100, &x, &y);
            TonboRespawn = 0;
            t += 0.03;
            break;
        }
       

        
    }
   
   
    


   /* TonboMotion(t, 550, 300, &x, &y);
    t += 0.03f;*/

}
// 描画関数（毎フレーム呼ばれる）
void Tonbo::TonboDraw(void)
{
  
  // 現在の時間tから座標を計算
  

  //TonboMotion(t, 550, 300, &x, &y);

  if (TonboDestroy == TRUE)
  {
      // 円を描画（赤っぽい色）
      Camera::DrawCircleW({ (float)x, (float)y }, 20, GetColor(255, 200, 100));
  }


  // 時間を進める（これが無いと動かない）
  //t += 0.03;
}

Vector2D* Tonbo::TonboLocation(void)
{
    tonbo = { (float)x,(float)y };
    return &tonbo;
}

void Tonbo::SetTonbo(class Bug* p)
{
    tonboscore = p;
}