#include"RankingScene.h"
#include"../Utilitys/Input.h"
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
	ranking = LoadGraph("assets/images/Ranking/ranking.png");
	select_x,pressed = 0;//selectはメニューの選択に利用する変数、pressedはボタンが押された場合に利用する変数
	time = 0.0f;
	time_rug = 0.5f;
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

	return eRanking;
}

void Ranking::Draw()const
{
	DrawRotaGraph(640, 400, 2.0, 0.0, back_ground, TRUE);

	DrawRotaGraph(640, 420, 1.4, 0.0, ranking, TRUE);

	if (select_x == 0)
	{
		if (pressed == TRUE)
		{
			DrawRotaGraph(410, 595, 1.2, 0.0, start_pressed, TRUE);
		}
		else
		{
			DrawRotaGraph(410, 595, 1.2, 0.0, start_not_pressed, TRUE);
		}
	}
	else
	{
		DrawRotaGraph(410, 595, 1.0, 0.0, start_not_pressed, TRUE);
	}

	if (select_x == 1)
	{
		if (pressed == TRUE)
		{
			DrawRotaGraph(860, 595, 1.2, 0.0, title_pressed, TRUE);
		}
		else
		{
			DrawRotaGraph(860, 595, 1.2, 0.0, title_not_pressed, TRUE);
		}
	}
	else
	{
		DrawRotaGraph(860, 595, 1.0, 0.0, title_not_pressed, TRUE);
	}
}