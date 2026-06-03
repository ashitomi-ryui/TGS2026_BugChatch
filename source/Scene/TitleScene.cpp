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

int Title::Init()
{
	start_not_pressed = LoadGraph("assets/images/Title/start_off.png");
	start_pressed = LoadGraph("assets/images/Title/start_on.png");
	help_not_pressed = LoadGraph("assets/images/Title/help_off.png");
	help_pressed = LoadGraph("assets/images/Title/help_on.png");
	end_not_pressed = LoadGraph("assets/images/Title/end_off.png");
	end_pressed = LoadGraph("assets/images/Title/end_on.png");
	ranking_not_pressed = LoadGraph("assets/images/Title/ranking_off.png");
	ranking_pressed = LoadGraph("assets/images/Title/ranking_on.png");
	back_ground = LoadGraph("assets/images/Title/mori.jpg");

	Titlebgm = LoadSoundMem("assets/Audio/Title.wav");
	if (Titlebgm == -1)
	{
		return FALSE;
	}
	ChoiceSE = LoadSoundMem("assets/Audio/AS_865704_8bitな選択音.wav");
	if (ChoiceSE == -1)
	{
		return FALSE;
	}
	DecisionSE = LoadSoundMem("assets/Audio/AS_134044_決定音.wav");
	if (DecisionSE == -1)
	{
		return FALSE;
	}
	
	select_x, select_y, pressed = 0;//selectはメニューの選択に利用する変数、pressedはボタンが押された場合に利用する変数
	time = 0.0f;
	time_rug = 0.5f;
PlaySoundMem(Titlebgm, DX_PLAYTYPE_BACK);
	return TRUE;
}

eSceneType Title::Update(float delta_second)
{
	

	time += delta_second;

	if (pressed == 0)//決定ボタンが押されていない場合
	{
		time_rug += delta_second;
	}
	if (time >= time_rug)
	{
		if (select_x == 0)
		{

			switch (select_y)
			{
			case 0:
				return eInGame;
				break;
			case 1:
				return eHelp;
				break;
			case 2:
				return eEnd;
				break;
			}
		}
		else
		{
			return eRanking;
		}
	}

	if (pressed == 0)
	{

		if (GetLeftStickState_Y(true) == ePressed)//左スティックが上に入力された場合
		{
			PlaySoundMem(ChoiceSE, DX_PLAYTYPE_BACK,TRUE);
			if (select_x == 1)
			{
				select_x = 0;
			}
			if (select_y == 0)//一番上が選択されている状態の場合
			{
				select_y = 2;//一番下へ戻す
			}
			else
			{
				select_y--;//上へ移動する
			}
		}
		if (GetLeftStickState_Y(false) == ePressed)//左スティックが下に入力された場合
		{
			PlaySoundMem(ChoiceSE, DX_PLAYTYPE_BACK,TRUE);
			if (select_x == 1)
			{
				select_x = 0;
			}
			if (select_y == 2)//一番下が選択されている状態の場合
			{
				select_y = 0;//一番上へ戻す
			}
			else
			{
				
				
				select_y++;//下へ移動する
			}
		}
		if (GetLeftStickState_X(true) == ePressed)//左スティックが右に入力された場合
		{
			if (select_y == 0 || select_y == 2)
			{
				select_y = 1;
			}
			if (select_x == 1)//一番右が選択されている状態の場合
			{
				select_x = 0;//左へ戻す
			}
			else
			{
				select_x++;//右へ移動する
			}
		}
		if (GetLeftStickState_X(false) == ePressed)//左スティックが左に入力された場合
		{
			if (select_x == 0)//一番左が選択されている場合
			{
				select_x = 1;//右へ戻す
			}
			else
			{
				select_x--;//左へ移動する
			}
		}
	
		if (GetButtonState(XINPUT_BUTTON_A) == ePressed)//スタートが選択されているかつAボタンが押された場合
		{
			PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
			pressed = 1;
			StopSoundMem(Titlebgm);
		}
	}
	
	return eTitle;//タイトル画面を維持
}

void Title::Draw()const
{
	DrawRotaGraph(640, 360, 1.0, 0.0, back_ground, TRUE);

	if (select_y == 0)//スタートが選択されている場合
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

	if (select_y == 1 && select_x == 0)//ヘルプが選択されている場合
	{
		if (pressed == 1)
		{
			DrawRotaGraph(640, 520, 1.2, 0.0, help_pressed, TRUE);//ボタンを大きくする
		}
		else
		{
			DrawRotaGraph(640, 520, 1.2, 0.0, help_not_pressed, TRUE);//ボタンを大きくする
		}
	}
	else
	{
		DrawRotaGraph(640, 520, 1.0, 0.0, help_not_pressed, TRUE);//通常サイズに戻す
	}

	if (select_y == 1 && select_x == 1)//ランキングが選択されている場合
	{
		if (pressed == 1)
		{
			DrawRotaGraph(1000, 520, 1.2, 0.0, ranking_pressed, TRUE);//ボタンを大きくする
		}
		else
		{
			DrawRotaGraph(1000, 520, 1.2, 0.0, ranking_not_pressed, TRUE);//ボタンを大きくする
		}
	}
	else
	{
		DrawRotaGraph(1000, 520, 1.0, 0.0, ranking_not_pressed, TRUE);//通常サイズに戻す
	}

	if (select_y == 2)//おわりが選択されている場合
	{
		if (pressed == 1)
		{
			DrawRotaGraph(640, 640, 1.2, 0.0, end_pressed, TRUE);//ボタンを大きくする
		}
		else
		{
			DrawRotaGraph(640, 640, 1.2, 0.0, end_not_pressed, TRUE);//ボタンを大きくする
		}
	}
	else
	{
		DrawRotaGraph(640, 640, 1.0, 0.0, end_not_pressed, TRUE);//通常サイズに戻す
	}

	SetFontSize(50);
	DrawString(200, 200, "Aボタンで開始できます", GetColor(255, 255, 255), TRUE);//仮タイトル
	/*DrawFormatString(100, 100, GetColor(255, 255, 255), "%d", select_y);*/
	/*DrawFormatString(100, 100, GetColor(255, 255, 255), "%f", time);*/
}