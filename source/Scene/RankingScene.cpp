#include"RankingScene.h"
#include"../Utilitys/Input.h"
#include"../Utilitys/Camera.h"
#include<DxLib.h>

int Ranking::ranking[MAX_RANK] = {};
int Ranking::new_data = -1;
int Ranking::new_rank = -1;

int Ranking::netImage = -1;
int Ranking::productionImage[2] = {};
int Ranking::buttonImage = -1;

Ranking::Ranking()
{
	ChoiceSE = -1;
	DecisionSE = -1;
	RankingBGM = -1;
	back_ground = -1;
	buttonSelect = 0;
	pressed = false;

	shiita = 0.0f;
	changeProduction = 0;
}

Ranking::~Ranking()
{

}

int Ranking::Init()
{
	buttonImage = LoadGraph("assets/images/UI/Button.PNG");
	back_ground = LoadGraph("assets/images/UI/RankingBack.PNG");
	netImage = LoadGraph("assets/images/Player/BugNet.PNG");
	productionImage[0] = LoadGraph("assets/images/UI/SceneProduction/Grasshopper1.PNG");
	productionImage[1] = LoadGraph("assets/images/UI/SceneProduction/Grasshopper2.PNG");

	buttonSelect = 0;
	pressed = false;//selectはメニューの選択に利用する変数、pressedはボタンが押された場合に利用する変数
	RankingBGM = LoadSoundMem("assets/Audio/AS_52281_RankingBGM.wav");
	if (RankingBGM == -1)
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

	int loadrankdata=LoadRankData();
	if (loadrankdata != TRUE)
	{
		return FALSE;
	}

	ChangeVolumeSoundMem(150, ChoiceSE);
	ChangeVolumeSoundMem(150, DecisionSE);
	ChangeVolumeSoundMem(130, RankingBGM);
	PlaySoundMem(RankingBGM, DX_PLAYTYPE_LOOP);

	buttonSelect = 0;
	pressed = false;

	shiita = 0.0f;
	changeProduction = 0;

	Camera::SetScreenLocation({ 0.0f, D_WIN_HEIGHT });
	Camera::SetScreenRatioSize(0.0f);

	return TRUE;
}

eSceneType Ranking::Update(float delta_second)
{
	switch (changeProduction)
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

		if (GetLeftStickState_X(true) == ePressed)//左スティックが右に入力された場合
		{
			if (buttonSelect != 1 )
				PlaySoundMem(ChoiceSE, DX_PLAYTYPE_BACK);
			buttonSelect = 1;
		}
		if (GetLeftStickState_X(false) == ePressed)//左スティックが左に入力された場合
		{
			if (buttonSelect != 0 )
				PlaySoundMem(ChoiceSE, DX_PLAYTYPE_BACK);
			buttonSelect = 0;
		}

		if (GetButtonState(XINPUT_BUTTON_A) == ePressed)//スタートが選択されているかつAボタンが押された場合
		{
			PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
			StopSoundMem(RankingBGM);

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
				return eTitle;
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

	return eRanking;
}

void Ranking::Draw()const
{
	Camera::DrawGraph({ 640, 360 }, 1.0, 1.0, 0.0, back_ground);

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
	Vector2D botLoc[4] = { { D_WIN_WIDTH / 2.0f - 300.0f, D_WIN_HEIGHT - 120.0f },		// スタート
						   { D_WIN_WIDTH / 2.0f + 300.0f, D_WIN_HEIGHT - 120.0f } };	// タイトル
	// 文字の位置ずらす
	Vector2D charVec[4] = { { -1.5f, -10.0f },		// スタート
							 { -1.5f, -10.0f } };	// タイトル
	// 文字
	char character[4][20] = { "スタート",		// スタート
							  "タイトル", };	// タイトル
	for (int i = 0;i < 2;i++)
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

		charSize = (int)(50.0f * ratio);

		// ボタンを表示
		Camera::DrawGraph(botLoc[i], ratio, ratio, 0.0, buttonImage, false, isPress, buttonColor);
		// 文字を表示
		Camera::DrawString(Vec2Add(botLoc[i], { charVec[i].x * (float)charSize, charVec[i].y }), charSize * 1.2f, charColor, character[i]);
	}


	unsigned int color;
	for (int i = 0;i < MAX_RANK;i++)
	{
		{
			switch (i)
			{

			case 0:
				color = GetColor(255, 255, 120);
				break;
			case 1:
				color = GetColor(200, 200, 200);
				break;
			case 2:
				color = GetColor(180, 120, 20);
				break;
			default:
				color = GetColor(100, 100, 100);
				break;
			}
		}
		

		Camera::DrawString({ (float)(150 + (i / 3) * 600), (float)(115 + (i % 3) * 120) },
			100, color, "%d位 %3d匹", i + 1, ranking[i]);


		/*Camera::DrawBox({ 42,47 }, { 650,186 }, GetColor(255, 255, 255));*/

		if (new_rank != -1)
		{
			float horizontal_line = 0;
			if (new_rank > 2)
			{
				 horizontal_line = 590;
			}
			float Vertical_line = (float)121 * (new_rank % 3);
			Camera::DrawBox({ 42+horizontal_line,47 + Vertical_line }, { 60 + horizontal_line,186 + Vertical_line }, GetColor(255, 255, 255));//縦線１
			Camera::DrawBox({ 632 + horizontal_line,47 + Vertical_line }, { 650 + horizontal_line,186 + Vertical_line }, GetColor(255, 255, 255));//縦線2
			Camera::DrawBox({ 42 + horizontal_line,47 + Vertical_line }, { 650 + horizontal_line,65 + Vertical_line }, GetColor(255, 255, 255));//横線１
			Camera::DrawBox({ 42 + horizontal_line,163 + Vertical_line }, { 650 + horizontal_line,186 + Vertical_line }, GetColor(255, 255, 255));//横線2
		}
		
		DrawFormatString(100, 100, GetColor(255, 0, 0), "%d", new_data);
		DrawFormatString(100, 150, GetColor(255, 0, 0), "%d", new_rank);
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

int Ranking::LoadRankData()
{
	FILE* fp = NULL;
	errno_t result = fopen_s(&fp, "assets/dat/Ranking_Data.txt", "r");

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
	if (p_point >= ranking[MAX_RANK - 1])
	{
		new_data = p_point;
		ranking[MAX_RANK - 1] = p_point;

		if (SortRankData() != TRUE)
		{
			return -1;
		}

		return 1;
	}

	new_data = -1;
	new_rank = -1;
	return 0;
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

	for (int i = 0; i < MAX_RANK; i++)
	{
		if (ranking[i] == new_data)
		{
			new_rank = i;
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
	errno_t result = fopen_s(&fp, "assets/dat/Ranking_Data.txt", "w");

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