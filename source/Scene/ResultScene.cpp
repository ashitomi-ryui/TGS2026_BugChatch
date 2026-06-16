#include<DxLib.h>
#include"ResultScene.h"
#include"RankingScene.h"
#include"../Utilitys/Camera.h"

int Result::netImage = -1;

int Result::divisor[DISPLAY_LIMIT] = { 1,10,100,1000 };
int Result::display[DISPLAY_LIMIT][DISPLAY_LIMIT] = {};

Bug bug;
Ranking result;

Result::Result()
{
	isRankIn = false;
	colorHue = 0.0f;

	timer = 0.0f;

	shiita = 0.0f;
	changeProduction = 0;
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
	bugIcon[0] = LoadGraph("assets/images/UI/CicadaIcon.PNG");
	bugIcon[1] = LoadGraph("assets/images/UI/DragonflyIcon.PNG");
	bugIcon[2] = LoadGraph("assets/images/UI/GrasshopperIcon.PNG");
	netImage = LoadGraph("assets/images/Player/BugNet.PNG");

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
	if (rank_check == -1)
	{
		return FALSE;
	}
	if (rank_check == 1)
	{
		isRankIn = true;
	}
	else
	{
		isRankIn = false;
	}
	colorHue = 0.0f;

	timer = 0.0f;

	shiita = 0.0f;
	changeProduction = 0;

	Camera::SetScreenLocation({ 0.0f, D_WIN_HEIGHT });
	Camera::SetScreenRatioSize(0.0f);

	return TRUE;
}

eSceneType Result::Update(float delta_second)
{
	switch (changeProduction)
	{
	case 0:	// =========================================================================入る演出

		shiita += 1.5f * delta_second;

		if (shiita > 1.0f)
		{
			shiita = 1.0f; // 行き過ぎ防止

			timer = 0.0f;
			changeProduction++;
		}

		//ジャンプの移動処理
		{
			float height = sinf(shiita * DX_PI_F) * (D_WIN_HEIGHT * 1.0f / 2.0f);
			Camera::SetScreenLocation({ D_WIN_WIDTH / -6.0f + (D_WIN_WIDTH * 2.0f / 3.0f) * shiita,
				D_WIN_HEIGHT + (D_WIN_HEIGHT / -2.0f) * shiita - height });
		}
		Camera::SetScreenRatioSize(shiita * shiita);

		break;
	case 1:
		if (isRankIn)
		{
			timer += delta_second;

			if (timer >= 1.0f)
			{
				changeProduction++;
			}
		}
		else
		{
			changeProduction++;
		}
		break;
	case 2:	// ============================================================================選択

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

			changeProduction++;
			shiita = 0.0f;

			pressed = TRUE;
		}

		break;
	case 3:	// =======================================================次への演出

		shiita += 2.0f * delta_second;

		// 次へ
		if (shiita > 0.6f)
		{
			changeProduction++;
		}

		{
			//ジャンプの移動処理
			float height = sinf(shiita * DX_PI_F) * (D_WIN_HEIGHT / 2.0f);
			Camera::SetScreenLocation({ D_WIN_WIDTH / 2.0f,
				D_WIN_HEIGHT / 2.0f + (D_WIN_HEIGHT / 4.0f) * shiita - height });
		}
		Camera::SetScreenRatioSize(1.0f - shiita);

		break;
	case 4:

		shiita += 2.0f * delta_second;

		// 終了
		if (shiita > 1.6f)
		{
			// 選択したシーンへ遷移
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

		if (shiita <= 1.0f)
		{
			//ジャンプの移動処理
			float height = sinf(shiita * DX_PI_F) * (D_WIN_HEIGHT / 2.0f);
			Camera::SetScreenLocation({ D_WIN_WIDTH / 2.0f,
				D_WIN_HEIGHT / 2.0f + (D_WIN_HEIGHT / 4.0f) * shiita - height });
			Camera::SetScreenRatioSize(1.0f - shiita);
		}
		else
		{
			Camera::SetScreenLocation({ -10.0f, -10.0f });
			Camera::SetScreenRatioSize(0.0f);
		}

		break;
	}

	if (changeProduction > 1 && isRankIn)
	{
		colorHue += 1.0f * delta_second;
		if (colorHue >= 3.0f)
		{
			colorHue -= 3.0f;
		}
	}

	return eResult;
}

void Result::Draw()const
{

	Camera::DrawGraph({ 640, 360 }, 1.0, 1.0, 0.0, back_ground, true);

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

	for (int i = 0;i < 3;i++)
	{
		Camera::DrawGraph({ 200.0f + (i * 320.0f), 150.0f }, 3.0f, 3.0f, 0.0f, bugIcon[i]);
		Camera::DrawString({ 220.0f + (i * 320.0f), 150.0f }, 75, GetColor(255, 255, 255), "　%d匹", p.point[i]);
	}
	Camera::DrawString({ 400, 250 }, 100, GetColor(255, 255, 255), "合計　%d匹", p.point[3]);


	int r = 0, g = 0, b = 0;
	if (colorHue < 1.0f)
	{
		r = (int)(((1.0f - fabsf(colorHue))) * 255.0f);
	}
	else if (colorHue > 2.0f)
	{
		r = (int)((1.0f - fabsf(colorHue - 3.0f)) * 255.0f);
	}
	if (colorHue > 0.0f && colorHue < 2.0f)
	{
		g = (int)((1.0f - fabsf(colorHue - 1.0f)) * 255.0f);
	}
	if (colorHue > 1.0f && colorHue < 3.0f)
	{
		b = (int)((1.0f - fabsf(colorHue - 2.0f)) * 255.0f);
	}

	if(changeProduction > 1 && isRankIn)
	{
		Camera::DrawString({ 375, 375 }, 100, GetColor(r, g, b), "ランクイン！");
	}
	

	Camera::Draw();

	if (changeProduction == 4)
	{
		Vector2D location = { D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f + 750.0f };
		float angle = 0.5f - (shiita - 0.6f) * 1.5f;
		angle *= DX_PI_F;
		location.x += sinf(angle) * 500.0f;
		location.y -= cosf(angle) * 500.0f;
		DrawRotaGraphF(location.x, location.y, 15.0f, angle, netImage, true);
	}
}