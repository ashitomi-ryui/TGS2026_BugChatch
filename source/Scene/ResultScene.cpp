#include<DxLib.h>
#include"ResultScene.h"
#include"RankingScene.h"
#include"../Object/Cage.h"
#include"../Utilitys/Camera.h"

int Result::netImage = -1;
int Result::productionImage[2] = {};
int Result::buttonImage = -1;

int Scorecount;

int Result::divisor[DISPLAY_LIMIT] = { 1,10,100,1000 };
int Result::display[DISPLAY_LIMIT][DISPLAY_LIMIT] = {};

Bug bug;

Result::point Result::p = {};

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
	buttonImage = LoadGraph("assets/images/UI/Button.PNG");
	
	back_ground = LoadGraph("assets/images/UI/ResultBack.PNG");
	bugIcon[0] = LoadGraph("assets/images/UI/CicadaIcon.PNG");
	bugIcon[1] = LoadGraph("assets/images/UI/DragonflyIcon.PNG");
	bugIcon[2] = LoadGraph("assets/images/UI/GrasshopperIcon.PNG");
	netImage = LoadGraph("assets/images/Player/BugNet.PNG");
	productionImage[0] = LoadGraph("assets/images/UI/SceneProduction/Grasshopper1.PNG");
	productionImage[1] = LoadGraph("assets/images/UI/SceneProduction/Grasshopper2.PNG");


	ResultBGM = LoadSoundMem("assets/Audio/Result.wav");
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
	Scorecount = LoadSoundMem("assets/Audio/HitSE.wav");
	if (Scorecount == -1)
	{
		return FALSE;
	}
	pressed = false;

	ChangeVolumeSoundMem(150, ChoiceSE);
	ChangeVolumeSoundMem(150, DecisionSE);
	ChangeVolumeSoundMem(130, ResultBGM);
	PlaySoundMem(ResultBGM, DX_PLAYTYPE_LOOP);

	p.point[0] = 0;
	p.point[1] = 0;
	p.point[2] = 0;
	p.point[3] = 0; 

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

	Cage::Init(eResult);

	colorHue = 0.0f;

	timer = 0.0f;

	shiita = 0.0f;
	changeProduction = 0;

	Camera::SetScreenLocation({ 0.0f, D_WIN_HEIGHT });
	Camera::SetScreenRatioSize(0.0f);

	buttonSelect = 1;

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
	case 1:	// ============================================================================虫を射出

		Cage::Update(eResult, delta_second);

		if (Cage::GetRemovedAll())
		{
			p.point[0] = bug.GetCicadaCount();
			p.point[1] = bug.GetDragonflyCount();
			p.point[2] = bug.GetGrasshopperCount();
			p.point[3] = p.point[0] + p.point[1] + p.point[2];

			int loadrankdata = Ranking::LoadRankData();

			int rank_check = Ranking::CheckRankData(p.point[3]);
			if (rank_check == 1)
			{
				isRankIn = true;
			}
			else
			{
				isRankIn = false;
			}

			changeProduction++;
		}

		break;
	case 2:	// ============================================================================ランクイン

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
			buttonSelect = 1;
			changeProduction++;
		}

		break;
	case 3:	// ============================================================================選択

		if (GetLeftStickState_X(true) == ePressed)//左スティックが右に入力された場合
		{
			if (buttonSelect < 2)
			{
				PlaySoundMem(ChoiceSE, DX_PLAYTYPE_BACK);
				buttonSelect++;
			}
		}
		if (GetLeftStickState_X(false) == ePressed)//左スティックが左に入力された場合
		{
			if (buttonSelect > 0)
			{
				PlaySoundMem(ChoiceSE, DX_PLAYTYPE_BACK);
				buttonSelect--;
			}
		}

		if (GetButtonState(XINPUT_BUTTON_A) == ePressed)//スタートが選択されているかつAボタンが押された場合
		{
			PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
			StopSoundMem(ResultBGM);

			changeProduction++;
			shiita = 0.0f;

			pressed = true;
		}

		break;
	case 4:	// =======================================================次への演出
		
		shiita += 1.7f * delta_second;

		// 終了
		if (shiita > 1.15f)
		{
			// 選択したシーンへ遷移
			switch (buttonSelect)
			{
			case 0:
				return eTitle;
				break;
			case 1:
				return eInGame;
				break;
			case 2:
				return eRanking;
				break;
			}

		}

		if (shiita <= 0.95f)
		{
			//ジャンプの移動処理
			float height = sinf(shiita * DX_PI_F) * (D_WIN_HEIGHT / 2.0f);
			Camera::SetScreenLocation({ D_WIN_WIDTH / 2.0f,
				D_WIN_HEIGHT / 2.0f - height });
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

	for (int i = 0;i < 3;i++)
	{
		Camera::DrawGraph({ 200.0f + (i * 320.0f), 150.0f }, 3.0f, 3.0f, 0.0f, bugIcon[i]);
		Camera::DrawString({ 220.0f + (i * 320.0f), 150.0f }, 75, GetColor(255, 255, 255), "　%d匹", p.point[i]);
	}

	if(changeProduction > 1)
	{
		Camera::DrawString({ 400, 250 }, 100, GetColor(255, 255, 255), "合計　%d匹", p.point[3]);
	}

	{
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

		if (changeProduction > 2 && isRankIn)
		{
			Camera::DrawString({ 375, 375 }, 100, GetColor(r, g, b), "ランクイン！");
		}
	}

	if(changeProduction > 1)
	{
		float selectSize = 0.84f;
		float notSelectSize = 0.7f;
		int selectCharSize = 60;
		int notSelectCharSize = 50;
		Vector2D startLoc = { 300.0f, 600.0f };
		Vector2D titleLoc = { 1000.0f, 600.0f };

		// ボタンのサイズ比率
		float ratio = 1.0f;
		// 文字サイズ
		int charSize = 50;
		// 押されている見た目か
		bool isPress = false;
		// ボタンの色
		unsigned int buttonColor = 0xc0c0c0;
		// 文字の色
		unsigned int charColor = 0xffffff;
		// ボタンの位置
		Vector2D botLoc[4] = { { D_WIN_WIDTH / 2.0f - 400.0f, D_WIN_HEIGHT - 100.0f },		// タイトル
							   { D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT - 150.0f },		// リスタート
							   { D_WIN_WIDTH / 2.0f + 400.0f, D_WIN_HEIGHT - 100.0f } };	// ランキング
		// 文字の位置ずらす
		Vector2D charVec[4] = { { -1.5f, -10.0f },		// タイトル
								 { -2.0f, -10.0f },		// リスタート
								 { -2.2f, -10.0f } };	// ランキング
		// 文字
		char character[4][20] = { "タイトル",		// タイトル
								  "リスタート",		// リスタート
								  "ランキング", };	// ランキング
		for (int i = 0;i < 3;i++)
		{
			// 選択されている場合
			if (buttonSelect == i)
			{
				ratio = 1.2f;
				// ボタンが押されている場合
				if (pressed)
				{
					// 押されている見た目にする
					isPress = true;
					// 色を暗くする
					buttonColor = 0x777777;
					// 文字の枠を暗い黄色にする
					charColor = 0x773c00;
				}
				else
				{
					// 色をそのままにする
					buttonColor = 0xffffff;
					// 文字の枠を黄色にする
					charColor = 0xff7700;
				}
			}
			else
			{
				ratio = 1.0f;
				// 押されている見た目にする
				isPress = false;
				// 色を少し暗くする
				buttonColor = 0xc0c0c0;
				// 文字の枠を白にする
				charColor = 0xffffff;
			}

			if (i > 0)
			{
				charSize = (int)(40.0f * ratio);
			}
			else
			{
				charSize = (int)(50.0f * ratio);
			}

			// ボタンを表示
			Camera::DrawGraph(botLoc[i], ratio, ratio, 0.0, buttonImage, false, isPress, buttonColor);
			// 文字を表示
			Camera::DrawString(Vec2Add(botLoc[i], { charVec[i].x * (float)charSize, charVec[i].y }), charSize * 1.2f, charColor, character[i]);
		}
	}

	if(changeProduction < 2)
	{
		Cage::Draw(eResult);
	}

	Camera::Draw();

	switch (changeProduction)
	{
	case 0:

		Camera::DrawGraph({ D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f + 40.0f }, 80.0f, 80.0f, 0.0f, productionImage[0]);

		break;
	case 4:

		Camera::DrawGraph({ D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f + 40.0f }, 80.0f, 80.0f, 0.0f, productionImage[1]);

		if (shiita > 0.6f)
		{
			Vector2D location = { D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f + 1350.0f };
			float angle = 0.5f - (shiita - 0.6f) * 1.5f;
			angle *= DX_PI_F;
			location.x += sinf(angle) * 1000.0f;
			location.y -= cosf(angle) * 1000.0f;
			DrawRotaGraphF(location.x, location.y, 30.0f, angle, netImage, true);
		}

		break;
	}
}

void Result::AddPoint(Cage::Type type)
{
	switch (type)
	{
	case Cage::eCicada:
		p.point[0]++;
		break;
	case Cage::eDragonfly:
		p.point[1]++;
		break;
	case Cage::eGrasshopper:
		p.point[2]++;
		break;
	}

	PlaySoundMem(Scorecount, DX_PLAYTYPE_BACK);
}
