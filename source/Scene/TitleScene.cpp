#include"TitleScene.h"
#include"../Utilitys/Input.h"
#include<DxLib.h>

int TitleInit(void)//タイトルの初期化
{
	return TRUE;
}

eSceneType TitleUpdate(float delta_second)//タイトル更新処理
{
	if (GetKeyInputState(KEY_INPUT_SPACE) == ePressed)
	{
		return eInGame;
	}
	
	return eTitle;
}

void TitleDraw(void)//タイトル表示
{
	DrawString(200, 200, "SPACEを押してメイン画面へ移動",GetColor(225, 0, 0), TRUE);
}