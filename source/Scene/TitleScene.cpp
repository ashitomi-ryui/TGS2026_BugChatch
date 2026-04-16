#include"TitleScene.h"
#include"../Utilitys/Input.h"
#include<DxLib.h>

//Title title;

//int TitleInit(void)//タイトルの初期化
//{
//	return TRUE;
//}
//
//eSceneType TitleUpdate(float delta_second)//タイトル更新処理
//{
//	if (GetKeyInputState(KEY_INPUT_SPACE) == ePressed)
//	{
//		return eInGame;
//	}
//	
//	return eTitle;
//}
//
//void TitleDraw(void)//タイトル表示
//{
//	DrawString(200, 200, "SPACEを押してメイン画面へ移動",GetColor(225, 0, 0), TRUE);
//}

Title::Title()
{
	start_not_pressed = LoadGraph("assets/Title/start_off.png");
}

Title::~Title()
{

}

int Title::TitleInit()
{
	/*start_not_pressed = LoadGraph("assets/Title/start_off.png");*/
	start_pressed = LoadGraph("assets/Title/start_on.png");
	help_not_pressed = LoadGraph("assets/Title/help_off.png");
	help_pressed = LoadGraph("assets/Title/help_on.png");
	end_not_pressed = LoadGraph("assets/Title/end_off.png");
	end_pressed = LoadGraph("assets/Title/end_on.png");
	
	return TRUE;
}

eSceneType Title::TitleUpdate(float delta_second)
{
	if (GetKeyInputState(KEY_INPUT_SPACE) == ePressed)
	{
		return eInGame;
	}

	return eTitle;
}

void Title::TitleDraw()const
{
	DrawRotaGraph(640, 400, 1.0, 0.0, start_not_pressed, TRUE);
	DrawRotaGraph(640, 520, 1.0, 0.0, help_not_pressed, TRUE);
	DrawRotaGraph(640, 640, 1.0, 0.0, end_not_pressed, TRUE);
}