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

	select, pressed = 0;//selectはメニューの選択に利用する変数、pressedはボタンが押された場合に利用する変数
	time = 0.0f;
	time_rug = 0.5f;

	return TRUE;
}

eSceneType Title::TitleUpdate(float delta_second)
{
	time += delta_second;

	if (pressed == 0)//決定ボタンが押されていない場合
	{
		time_rug += delta_second;
	}
	if (time >= time_rug)
	{
		return eInGame;
	}

	if (GetLeftStickState(true) == ePressed)//左スティックが上に入力された場合
	{
		if (select <= 0)//一番上が選択されている状態の場合
		{
			select = 2;//一番下へ戻す
		}
		else
		{
			select--;//上へ移動する
		}
	}
	if (GetLeftStickState(false) == ePressed)//左スティックが下に入力された場合
	{
		if (select >= 2)//一番下が選択されている状態の場合
		{
			select = 0;//一番上へ戻す
		}
		else
		{
			select++;//下へ移動する
		}
	}
	if (GetButtonState(XINPUT_BUTTON_A) == ePressed)//スタートが選択されているかつAボタンが押された場合
	{
		pressed = 1;
		//return eInGame;//ゲーム画面へ移行
	}

	return eTitle;//タイトル画面を維持
}

void Title::TitleDraw()const
{
	if (select == 0)//スタートが選択されている場合
	{
		if (pressed == 1)//ボタンが押されている場合
		{
			DrawRotaGraph(640, 400, 1.2, 0.0, start_pressed, TRUE);//ボタンを押された状態にする
		}
		else
		{
			DrawRotaGraph(640, 400, 1.2, 0.0, start_not_pressed, TRUE);//ボタンを押されていない状態にする
		}
	}
	else
	{
		DrawRotaGraph(640, 400, 1.0, 0.0, start_not_pressed, TRUE);//通常サイズに戻す
	}

	if (select == 1)//ヘルプが選択されている場合
	{
		DrawRotaGraph(640, 520, 1.2, 0.0, help_not_pressed, TRUE);//ボタンを大きくする
	}
	else
	{
		DrawRotaGraph(640, 520, 1.0, 0.0, help_not_pressed, TRUE);//通常サイズに戻す
	}

	if (select == 2)//おわりが選択されている場合
	{
		DrawRotaGraph(640, 640, 1.2, 0.0, end_not_pressed, TRUE);//ボタンを大きくする
	}
	else
	{
		DrawRotaGraph(640, 640, 1.0, 0.0, end_not_pressed, TRUE);//通常サイズに戻す
	}

	SetFontSize(50);
	DrawString(200, 200, "Aボタンで開始できます", GetColor(255, 255, 255), TRUE);//仮タイトル
	/*DrawFormatString(100, 100, GetColor(255, 255, 255), "%f", time);*/
}