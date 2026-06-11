#include"TitleScene.h"
#include"RankingScene.h"
#include"../Utilitys/Input.h"
#include"../Utilitys/Camera.h"
#include<DxLib.h>

Ranking title;

int Title::Titlebgm = -1;
int Title::ChoiceSE = -1;
int Title::DecisionSE = -1;
int Title::back_ground = -1;
int Title::title_logo = -1;

int Title::select_x = 0;
int Title::select_y = 0;
int Title::pressed = 0;
float Title::time = 0.0f;
float Title::time_rug = 0.5f;


Title::Title()
{

}

Title::~Title()
{
	
}

int Title::Init()
{
	back_ground = LoadGraph("assets/images/OtherObjects/Ground.PNG");
	title_logo = LoadGraph("assets/images/UI/TitleLogo.PNG");
	b.newtral = LoadGraph("assets/images/UI/ButtonDefault.PNG");
	b.select = LoadGraph("assets/images/UI/ButtonSelect.PNG");
	b.pressed = LoadGraph("assets/images/UI/ButtonPress.PNG");
	rank_b.newtral = LoadGraph("assets/images/UI/RankingDefault.PNG");
	rank_b.select = LoadGraph("assets/images/UI/RankingSelect.PNG");
	rank_b.pressed = LoadGraph("assets/images/UI/RankingPress.PNG");

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

	int rank_title = title.LoadRankData();
	if (rank_title != TRUE)
	{
		return FALSE;
	}
	
    PlaySoundMem(Titlebgm, DX_PLAYTYPE_LOOP);

	select_x, select_y, pressed = 0;
	time = 0.0f; time_rug = 0.5f;

	shiita = 0.0f;

	return TRUE;
}

eSceneType Title::Update(float delta_second)
{
	time += delta_second;

	if (pressed == 0)//決定ボタンが押されていない場合
	{
		time_rug += delta_second;
	}
	else
	{
		shiita += 2.0f * delta_second;

		if (shiita > 1.0f)
		{
			shiita = 1.0f; // 行き過ぎ防止
		}

		//ジャンプの移動処理
		float height = sinf(shiita * DX_PI_F) * (D_WIN_HEIGHT / 4.0f);
		Camera::SetScreenLocation({ D_WIN_WIDTH / 2.0f + (D_WIN_WIDTH * 2.0f / 3.0f) * shiita,
			D_WIN_HEIGHT / 2.0f + (D_WIN_HEIGHT / 2.0f) * shiita - height });

		
		Camera::SetScreenRatioSize(Camera::GetScreenRatioSize() - 2.0f * delta_second);

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
			PlaySoundMem(ChoiceSE, DX_PLAYTYPE_BACK, TRUE);
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
			PlaySoundMem(ChoiceSE, DX_PLAYTYPE_BACK, TRUE);
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
	Camera::DrawGraph({ 640, 360 }, 25.0, 12.0, 0.0, back_ground);

	Camera::DrawGraph({ 640,170 }, 1.5, 1.0, 0.0, title_logo);

	if (select_y == 0)//スタートが選択されている場合
	{
		if (pressed == 1)//ボタンが押されている場合
		{
			Camera::DrawGraph({ 640, 400 }, 0.7, 0.7, 0.0, b.pressed);//ボタンを押された状態にする
		}
		else
		{
			Camera::DrawGraph({ 640, 400 }, 0.7, 0.7, 0.0, b.select);//ボタンを押されていない状態にする
		}

		Camera::DrawString({ 561, 395 }, 55, GetColor(255, 255, 255), "スタート");
	}
	else
	{
		Camera::DrawGraph({ 640, 400 }, 0.6, 0.6, 0.0, b.newtral);//通常サイズに戻す
		Camera::DrawString({ 561, 395 }, 50, GetColor(255, 255, 255), "スタート");
	}

	if (select_y == 1 && select_x == 0)//ヘルプが選択されている場合
	{
		if (pressed == 1)
		{
			Camera::DrawGraph({ 640, 520 }, 0.7, 0.7, 0.0, b.pressed);//ボタンを大きくする
		}
		else
		{
			Camera::DrawGraph({ 640, 520 }, 0.7, 0.7, 0.0, b.select);//ボタンを大きくする
		}

		Camera::DrawString({ 580, 515 }, 55, GetColor(255, 255, 255), "ヘルプ");
	}
	else
	{
		Camera::DrawGraph({ 640, 520 }, 0.6, 0.6, 0.0, b.newtral);//通常サイズに戻す
		Camera::DrawString({ 580, 515 }, 50, GetColor(255, 255, 255), "ヘルプ");
	}

	if (select_y == 1 && select_x == 1)//ランキングが選択されている場合
	{
		if (pressed == 1)
		{
			Camera::DrawGraph({ 1000, 520 }, 0.7, 0.7, 0.0, rank_b.pressed);//ボタンを大きくする
		}
		else
		{
			Camera::DrawGraph({ 1000, 520 }, 0.7, 0.7, 0.0, rank_b.select);//ボタンを大きくする
		}
	}
	else
	{
		Camera::DrawGraph({ 1000, 520 }, 0.6, 0.6, 0.0, rank_b.newtral);//通常サイズに戻す
	}

	if (select_y == 2)//おわりが選択されている場合
	{
		if (pressed == 1)
		{
			Camera::DrawGraph({ 640, 640 }, 0.7, 0.7, 0.0, b.pressed);//ボタンを大きくする
		}
		else
		{
			Camera::DrawGraph({ 640, 640 }, 0.7, 0.7, 0.0, b.select);//ボタンを大きくする
		}

		Camera::DrawString({ 590, 635 }, 55, GetColor(255, 255, 255), "おわり");
	}
	else
	{
		Camera::DrawGraph({ 640, 640 }, 0.6, 0.6, 0.0, b.newtral);//通常サイズに戻す
		Camera::DrawString({ 590, 635 }, 50, GetColor(255, 255, 255), "おわり");
	}
}