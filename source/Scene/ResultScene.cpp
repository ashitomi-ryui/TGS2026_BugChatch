#include<DxLib.h>
#include"ResultScene.h"

int Result::word1[50] = {};
int Result::word2[15] = {};
int Result::word3[10] = {};
int Result::word4[18] = {};
int Result::divisor[DISPLAY_LIMIT] = { 1,10,100,1000 };
int Result::display[DISPLAY_LIMIT][DISPLAY_LIMIT] = {};

Bug bug;

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
	result = LoadGraph("assets/images/Result/result.png");

	select_x, pressed = 0;
	time = 0.0f;
	time_rug = 0.5f;

	LoadDivGraph("assets/images/OtherObjects/word1.png", 50, 5, 10, 30, 30, word1);
	LoadDivGraph("assets/images/OtherObjects/word2.png", 15, 5, 3, 30, 30, word2);
	LoadDivGraph("assets/images/OtherObjects/word3.png", 10, 10, 1, 30, 30, word3);
	LoadDivGraph("assets/images/OtherObjects/word4.png", 18, 6, 3, 30, 30, word4);

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
			pressed = TRUE;
		}
	}

	return eResult;
}

void Result::Draw()const
{

	DrawRotaGraph(640, 400, 1.0, 0.0, result, TRUE);

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

	for (int i = 0; i < DISPLAY_LIMIT; i++)
	{
		for (int j = p.size[i]; j >= 0; j--)
		{
			DrawRotaGraph(750 + 80 * (p.size[i] - j), 200 + 100 * i, 3.5, 0.0, word3[display[i][j]], TRUE);
		}

		DrawRotaGraph(750 + 80 * (p.size[i] + 1), 200 + 100 * i, 3.5, 0.0, word4[17], TRUE);
	}
}