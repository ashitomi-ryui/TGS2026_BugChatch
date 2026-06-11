#include"RankingScene.h"
#include"../Utilitys/Input.h"
#include"../Utilitys/Camera.h"
#include<DxLib.h>

Ranking::Ranking()
{

}

Ranking::~Ranking()
{

}

int Ranking::Init()
{
	start_not_pressed = LoadGraph("assets/images/Ranking/start_off.png");
	start_pressed = LoadGraph("assets/images/Ranking/start_on.png");
	title_not_pressed = LoadGraph("assets/images/Ranking/title_off.png");
	title_pressed = LoadGraph("assets/images/Ranking/title_on.png");
	back_ground = LoadGraph("assets/images/Ranking/mori.jpg");
	back_ground2 = LoadGraph("assets/images/Ranking/ranking.png");
	select_x,pressed = 0;//selectはメニューの選択に利用する変数、pressedはボタンが押された場合に利用する変数
	time = 0.0f;
	time_rug = 0.5f;

	Choicebgm2 = LoadSoundMem("assets/Audio/AS_865704_8bitな選択音.wav");
	if (Choicebgm2 == -1)
	{
		return FALSE;
	}
	DecisionSE2 = LoadSoundMem("assets/Audio/AS_134044_決定音.wav");
	if (DecisionSE2 == -1)
	{
		return FALSE;
	}

	int loadrankdata=LoadRankData();
	if (loadrankdata != TRUE)
	{
		return FALSE;
	}
	return TRUE;
}

eSceneType Ranking::Update(float delta_second)
{
	time += delta_second;

	if (pressed == FALSE)
	{
		time_rug += delta_second;
	}
	if (time >= time_rug)
	{
		switch (select_x)
		{
		case 0:
			return eInGame;
			break;
		case 1:
			return eTitle;
			break;
		}
	}
	
	if (pressed == 0)
	{
		if (GetLeftStickState_X(true) == ePressed)//左スティックが右に入力された場合
		{
			PlaySoundMem(Choicebgm2,DX_PLAYTYPE_BACK);
			if (select_x == 1)
			{
				select_x = 0;
			}
			else
			{
				select_x = 1;
			}
		}
		if (GetLeftStickState_X(false) == ePressed)//左スティックが左に入力された場合
		{
			PlaySoundMem(Choicebgm2, DX_PLAYTYPE_BACK);
			if (select_x == 0)
			{
				select_x = 1;
			}
			else
			{
				select_x = 0;
			}
		}

		if (GetButtonState(XINPUT_BUTTON_A) == ePressed)//スタートが選択されているかつAボタンが押された場合
		{
			PlaySoundMem(DecisionSE2, DX_PLAYTYPE_BACK);
			pressed = TRUE;
		}
	}

	return eRanking;
}

void Ranking::Draw()const
{
	Camera::DrawGraph({ 640, 400 }, 2.0, 2.0, 0.0, back_ground);

	Camera::DrawGraph({ 640, 420 }, 1.4, 1.4, 0.0, back_ground2);

	if (select_x == 0)
	{
		if (pressed == TRUE)
		{
			Camera::DrawGraph({ 410, 595 }, 1.2, 1.2, 0.0, start_pressed);
		}
		else
		{
			Camera::DrawGraph({ 410, 595 }, 1.2, 1.2, 0.0, start_not_pressed);
		}
	}
	else
	{
		Camera::DrawGraph({ 410, 595 }, 1.0, 1.0, 0.0, start_not_pressed);
	}

	if (select_x == 1)
	{
		if (pressed == TRUE)
		{
			Camera::DrawGraph({ 860, 595 }, 1.2, 1.2, 0.0, title_pressed);
		}
		else
		{
			Camera::DrawGraph({ 860, 595 }, 1.2, 1.2, 0.0, title_not_pressed);
		}
	}
	else
	{
		Camera::DrawGraph({ 860, 595 }, 1.0, 1.0, 0.0, title_not_pressed);
	}

	/*for (int i = 0; i < 3; i++)
	{
		DrawFormatString(100, 100 + 50 * i, GetColor(255, 255, 255), "%d", ranking[i]);
	}*/

	Camera::DrawString({ 480,250 }, 100, GetColor(255, 255, 160), "1位 %d匹", ranking[0]);
	Camera::DrawString({ 480,350 }, 100, GetColor(120, 120, 120), "2位 %d匹", ranking[1]);
	Camera::DrawString({ 480,450 }, 100, GetColor(180, 120, 20), "3位 %d匹", ranking[2]);
}

int Ranking::LoadRankData()
{
	FILE* fp = NULL;
	errno_t result = fopen_s(&fp, "assets/images/Ranking/Ranking_Data.txt", "r");

	if (result != NULL)
	{
		return FALSE;
	}

	for (int i = 0; i < MAX_RANK; i++)
	{
		fscanf_s(fp, "%d", &ranking[i]);
	}

	fclose(fp);
	return TRUE;
}

int Ranking::CheckRankData(int p_point)
{
	if (p_point > ranking[MAX_RANK - 1])
	{
		ranking[MAX_RANK - 1] = p_point;

		if (SortRankData() != TRUE)
		{
			return FALSE;
		}
	}

	return TRUE;
}

int Ranking::SortRankData()
{
	int swap = {};

	for (int i = 0; i < MAX_RANK - 1; i++)
	{
		for (int j = i + 1; j < MAX_RANK; j++)
		{
			if (ranking[j] > ranking[i])
			{
				swap = ranking[i];
				ranking[i] = ranking[j];
				ranking[j] = swap;
			}
		}
	}

	if (AddRankData() != TRUE)
	{
		return FALSE;
	}

	return TRUE;
}

int Ranking::AddRankData()
{
	FILE* fp = NULL;
	errno_t result = fopen_s(&fp, "assets/images/Ranking/Ranking_Data.txt", "w");

	if (result != NULL)
	{
		return FALSE;
	}

	for (int i = 0; i < MAX_RANK; i++)
	{
		fprintf_s(fp, "%d\n", ranking[i]);
	}

	fclose(fp);

	return TRUE;
}