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
	/*start_not_pressed = LoadGraph("assets/Title/start_off.png");*/
}

Title::~Title()
{

}

int Title::TitleInit()
{
	start_not_pressed = LoadGraph("assets/Title/start_off.png");
	start_pressed = LoadGraph("assets/Title/start_on.png");
	help_not_pressed = LoadGraph("assets/Title/help_off.png");
	help_pressed = LoadGraph("assets/Title/help_on.png");
	end_not_pressed = LoadGraph("assets/Title/end_off.png");
	end_pressed = LoadGraph("assets/Title/end_on.png");

	select, pressed = 0;
	time = 0.0f;
	time_rug = 0.5f;

	return TRUE;
}

eSceneType Title::TitleUpdate(float delta_second)
{
	time += delta_second;
	if (pressed == 0)
	{
		time_rug += delta_second;
	}

	left = GetLeftStick();
	right = GetRightStick();

	if (GetKeyInputState(KEY_INPUT_SPACE) == ePressed)
	{
		return eInGame;
	}
	if (GetKeyInputState(KEY_INPUT_UP) == ePressed || GetLeftStickState(true)==ePressed)
	{
		if (select <= 0)
		{
			select = 2;
		}
		else
		{
			select--;
		}
	}
	if (GetKeyInputState(KEY_INPUT_DOWN) == ePressed || GetLeftStickState(false) == ePressed)
	{
		if (select >= 2)
		{
			select = 0;
		}
		else
		{
			select++;
		}
	}

	return eTitle;
}

void Title::TitleDraw()const
{
	if (select == 0)
	{
		DrawRotaGraph(640, 400, 1.2, 0.0, start_not_pressed, TRUE);
	}
	else
	{
		DrawRotaGraph(640, 400, 1.0, 0.0, start_not_pressed, TRUE);
	}

	if (select == 1)
	{
		DrawRotaGraph(640, 520, 1.2, 0.0, help_not_pressed, TRUE);
	}
	else
	{
		DrawRotaGraph(640, 520, 1.0, 0.0, help_not_pressed, TRUE);
	}

	if (select == 2)
	{
		DrawRotaGraph(640, 640, 1.2, 0.0, end_not_pressed, TRUE);
	}
	else
	{
		DrawRotaGraph(640, 640, 1.0, 0.0, end_not_pressed, TRUE);
	}

	SetFontSize(50);
	DrawString(200, 200, "コントローラーで動かせるようにします", GetColor(255, 255, 255), TRUE);
	/*DrawFormatString(100, 100, GetColor(255, 255, 255), "%f", time);*/
}