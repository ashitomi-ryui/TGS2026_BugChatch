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
	b.newtral = LoadGraph("assets/images/UI/ButtonDefault.PNG");
	b.select = LoadGraph("assets/images/UI/ButtonSelect.PNG");
	b.pressed = LoadGraph("assets/images/UI/ButtonPress.PNG");
	rank_b.newtral = LoadGraph("assets/images/UI/RankingDefault.PNG");
	rank_b.select = LoadGraph("assets/images/UI/RankingSelect.PNG");
	rank_b.pressed = LoadGraph("assets/images/UI/RankingPress.PNG");
	back_ground = LoadGraph("assets/images/UI/ResultBack.PNG");

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

	p.point[0] = bug.GetDragonflyCount();
	p.point[1] = bug.GetGrasshopperCount();
	p.point[2] = bug.GetCicadaCount();
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

	DrawRotaGraph(640, 360, 1.0, 0.0, back_ground, TRUE);

	float selectSize = 0.84f;
	float notSelectSize = 0.7f;
	int selectCharSize = 60;
	int notSelectCharSize = 50;
	Vector2D startLoc = { 300.0f, 600.0f };
	Vector2D titleLoc = { 1000.0f, 600.0f };

	if (select_x == 0)	//タイトルが選択されている場合
	{
		if (pressed == TRUE)	//ボタンが押されている場合
		{
			//ボタンを押された状態にする
			Camera::DrawGraph(startLoc, selectSize, selectSize, 0.0, b.pressed);
		}
		else
		{
			//ボタンを押されていない状態にする
			Camera::DrawGraph(startLoc, selectSize, selectSize, 0.0, b.select);
		}
		Camera::DrawString({ startLoc.x - (float)selectCharSize * 1.5f, startLoc.y }, selectCharSize, GetColor(255, 255, 255), "タイトル");
	}
	else
	{
		//通常サイズに戻す
		Camera::DrawGraph(startLoc, notSelectSize, notSelectSize, 0.0, b.newtral);
		Camera::DrawString({ startLoc.x - (float)notSelectCharSize * 1.5f, startLoc.y }, notSelectCharSize, GetColor(255, 255, 255), "タイトル");
	}

	if (select_x == 1)	//ランキングが選択されている場合
	{
		if (pressed == TRUE)
		{
			//ボタンを大きくする
			Camera::DrawGraph(titleLoc, selectSize, selectSize, 0.0, rank_b.pressed);
		}
		else
		{
			//ボタンを大きくする
			Camera::DrawGraph(titleLoc, selectSize, selectSize, 0.0, rank_b.select);
		}
	}
	else
	{
		//通常サイズに戻す
		Camera::DrawGraph(titleLoc, notSelectSize, notSelectSize, 0.0, rank_b.newtral);
	}

	Camera::DrawString({ 250,150 }, 100, GetColor(255,255,255), "とんぼ %d匹\nばッた %d匹\nせみ 　%d匹\n合計 　%d匹", p.point[0], p.point[1], p.point[2], p.point[3]);

}