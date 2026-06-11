#include<DxLib.h>
#include"ResultScene.h"
#include"RankingScene.h"
#include"../Utilitys/Camera.h"

int Result::divisor[DISPLAY_LIMIT] = { 1,10,100,1000 };
int Result::display[DISPLAY_LIMIT][DISPLAY_LIMIT] = {};

Bug bug;
Ranking result;

Result::Result()
{
	
}

Result::~Result()
{
	
}

int Result::Init()
{
	title_not_pressed = LoadGraph("assets/images/Result/title_off.png");
	title_pressed = LoadGraph("assets/images/Result/title_on.png");
	ranking_not_pressed = LoadGraph("assets/images/Result/ranking_off.png");
	ranking_pressed = LoadGraph("assets/images/Result/ranking_on.png");
	back_ground = LoadGraph("assets/images/Result/result.png");


	ResultBGM = LoadSoundMem("assets/Audio/Result.wav");
	ChoiceSE3 = LoadSoundMem("assets/Audio/AS_865704_8bitな選択音.wav");
	if (ChoiceSE3 == -1)
	{
		return FALSE;
	}
	DecisionSE3 = LoadSoundMem("assets/Audio/AS_134044_決定音.wav");
	if (DecisionSE3 == -1)
	{
		return FALSE;
	}
	select_x, pressed = 0;
	time = 0.0f;
	time_rug = 0.5f;

	PlaySoundMem(ResultBGM, DX_PLAYTYPE_LOOP);

	p.point[0] = bug.GetCicadaCount();
	p.point[1] = bug.GetDragonflyCount();
	p.point[2] = bug.GetGrasshopperCount();
	p.point[3] = p.point[0] + p.point[1] + p.point[2];

	for (int i = 0; i < DISPLAY_LIMIT; i++)
	{
		if (p.point[i] >= 1000)
		{
			if (p.point[i] >= 10000)
			{
				p.point[i] = 9999;
			}
			p.size[i] = 3;
		}
		else if (1000 > p.point[i] && p.point[i] >= 100)
		{
			p.size[i] = 2;
		}
		else if (100 > p.point[i] && p.point[i] >= 10)
		{
			p.size[i] = 1;
		}
		else
		{
			p.size[i] = 0;
		}

		for (int j = p.size[i]; j >= 0; j--)
		{
			display[i][j] = (p.point[i] / divisor[j]) % 10;
		}
		
	}

	int loadrankdata = result.LoadRankData();
	if (loadrankdata != TRUE)
	{
		return FALSE;
	}

	int rank_check = result.CheckRankData(p.point[3]);
	if (rank_check != TRUE)
	{
		return FALSE;
	}

	return TRUE;
}

eSceneType Result::Update(float delta_second)
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
			return eTitle;
			break;
		case 1:
			return eRanking;
			break;
		}
	}

	if (pressed == 0)
	{
		if (GetLeftStickState_X(true) == ePressed)//左スティックが上に入力された場合
		{
			PlaySoundMem(ChoiceSE3, DX_PLAYTYPE_BACK);
			if (select_x == 1)
			{
				select_x = 0;
			}
			else
			{
				select_x = 1;
			}
		}
		if (GetLeftStickState_X(false) == ePressed)//左スティックが下に入力された場合
		{
			PlaySoundMem(ChoiceSE3, DX_PLAYTYPE_BACK);
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
			PlaySoundMem(DecisionSE3, DX_PLAYTYPE_BACK);
			StopSoundMem(ResultBGM);
			pressed = TRUE;
		}
	}

	return eResult;
}

void Result::Draw()const
{

	DrawRotaGraph(640, 400, 1.0, 0.0, back_ground, TRUE);

	if (select_x == 0)
	{
		if (pressed == TRUE)
		{
			DrawRotaGraph(300, 600, 1.2, 0.0, title_pressed, TRUE);
		}
		else
		{
			DrawRotaGraph(300, 600, 1.2, 0.0, title_not_pressed, TRUE);
		}
	}
	else
	{
		DrawRotaGraph(300, 600, 1.0, 0.0, title_not_pressed, TRUE);
	}

	if (select_x == 1)
	{
		if (pressed == TRUE)
		{
			DrawRotaGraph(1000, 600, 1.2, 0.0, ranking_pressed, TRUE);
		}
		else
		{
			DrawRotaGraph(1000, 600, 1.2, 0.0, ranking_not_pressed, TRUE);
		}
	}
	else
	{
		DrawRotaGraph(1000, 600, 1.0, 0.0, ranking_not_pressed, TRUE);
	}

	Camera::DrawString({ 250,150 }, 100, GetColor(255,255,255), "せみ %d匹\nとんぼ %d匹\nばッた %d匹\n合計 %d匹", p.point[0], p.point[1], p.point[2], p.point[3]);

}