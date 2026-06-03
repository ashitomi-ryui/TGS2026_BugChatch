#include<DxLib.h>
#include"ResultScene.h"

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

	c_count = bug.GetCicadaCount();
	d_count = bug.GetDragonflyCount();
	g_count = bug.GetGrasshopperCount();

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

	DrawFormatString(100, 100, GetColor(255, 255, 255), "%d", c_count);
}