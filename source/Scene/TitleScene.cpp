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
int Title::buttonImage = -1;
int Title::netImage = -1;
int Title::productionImage[2] = {};

int Title::buttonSelect = 0;	// 0スタート、1ヘルプ、2おわり、3ランキング
bool Title::pressed = false;


Title::Title()
{
	shiita = 0.0f;
	changeProduction = 0;
}

Title::~Title()
{
	
}

int Title::Init()
{

	back_ground = LoadGraph("assets/images/OtherObjects/Ground.PNG");
	title_logo = LoadGraph("assets/images/UI/TitleLogo.PNG");
	netImage = LoadGraph("assets/images/Player/BugNet.PNG");
	productionImage[0] = LoadGraph("assets/images/UI/SceneProduction/Grasshopper1.PNG");
	productionImage[1] = LoadGraph("assets/images/UI/SceneProduction/Grasshopper2.PNG");
	buttonImage = LoadGraph("assets/images/UI/Button.PNG");
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

	ChangeVolumeSoundMem(150, ChoiceSE);
	ChangeVolumeSoundMem(150, DecisionSE);
	ChangeVolumeSoundMem(130, Titlebgm);
    PlaySoundMem(Titlebgm, DX_PLAYTYPE_LOOP);

	buttonSelect = 0;
	pressed = false;

	shiita = 0.0f;
	changeProduction = 0;

	Camera::SetScreenLocation({ 0.0f, D_WIN_HEIGHT });
	Camera::SetScreenRatioSize(0.0f);

	return TRUE;
}

eSceneType Title::Update(float delta_second)
{
	switch(changeProduction)
	{
	case 0:	// =========================================================================入る演出

		shiita += 1.5f * delta_second;

		if (shiita > 1.0f)
		{
			shiita = 1.0f; // 行き過ぎ防止

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
	case 1:	// ============================================================================選択
		Camera::SetScreenLocation({ D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f });
		Camera::SetScreenRatioSize(1.0f);

		if (GetLeftStickState_Y(true) == ePressed)//左スティックが上に入力された場合
		{
			if (buttonSelect != 0)
				PlaySoundMem(ChoiceSE, DX_PLAYTYPE_BACK, TRUE);
			buttonSelect = 0;
		}
		if (GetLeftStickState_Y(false) == ePressed)//左スティックが下に入力された場合
		{
			if (buttonSelect != 2)
				PlaySoundMem(ChoiceSE, DX_PLAYTYPE_BACK, TRUE);
			buttonSelect = 2;
		}
		if (GetLeftStickState_X(true) == ePressed)//左スティックが右に入力された場合
		{
			if (buttonSelect != 3)
				PlaySoundMem(ChoiceSE, DX_PLAYTYPE_BACK, TRUE);
			buttonSelect = 3;
		}
		if (GetLeftStickState_X(false) == ePressed)//左スティックが左に入力された場合
		{
			if (buttonSelect != 1)
				PlaySoundMem(ChoiceSE, DX_PLAYTYPE_BACK, TRUE);
			buttonSelect = 1;
		}

		if (GetButtonState(XINPUT_BUTTON_A) == ePressed)//Aボタンが押された場合
		{
			PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
			StopSoundMem(Titlebgm);

			changeProduction++;
			shiita = 0.0f;

			pressed = true;
		}

		break;
	case 2:	// =======================================================次への演出

		shiita += 1.7f * delta_second;

		// 終了
		if (shiita > 1.15f)
		{
			// 選択したシーンへ遷移

			switch (buttonSelect)
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
			case 3:
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
	
	return eTitle;//タイトル画面を維持
}

void Title::Draw()const
{
	Camera::DrawGraph({ D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f }, 25.0f, 12.0f, 0.0f, back_ground);

	Camera::DrawGraph({ 440.0f, D_WIN_HEIGHT / 2.0f }, 2.0f, 2.0f, 0.0f, title_logo);

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
	Vector2D botLoc[4] = { { D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT - 320.0f },		// スタート
						   { D_WIN_WIDTH / 2.0f - 350.0f, D_WIN_HEIGHT - 200.0f },		// ヘルプ
						   { D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT - 80.0f },		// おわり
						   { D_WIN_WIDTH / 2.0f + 350.0f, D_WIN_HEIGHT - 200.0f } };	// ランキング
	// 文字の位置ずらす
	Vector2D charVec[4] = { { -1.5f, -10.0f },		// スタート
							 { -1.2f, -10.0f },		// ヘルプ
							 { -1.0f, -10.0f },		// おわり
							 { -2.2f, -10.0f } };	// ランキング
	// 文字
	char character[4][20] = { "スタート",		// スタート
							  "ヘルプ",			// ヘルプ
							  "おわり",			// おわり
							  "ランキング",};	// ランキング
	for (int i = 0;i < 4;i++)
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

		if (i == 3)
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

	Camera::Draw();

	switch (changeProduction)
	{
	case 0:

		Camera::DrawGraph({ D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f + 40.0f }, 80.0f, 80.0f, 0.0f, productionImage[0]);

		break;
	case 2:

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