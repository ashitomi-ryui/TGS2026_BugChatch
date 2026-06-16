#include"RankingScene.h"
#include"../Utilitys/Input.h"
#include"../Utilitys/Camera.h"
#include<DxLib.h>

int Ranking::netImage = -1;

Ranking::Ranking()
{
	Choicebgm2 = -1;
	DecisionSE2 = -1;
	RankingBGM2 = -1;
	back_ground = -1;
	select_x = 0;
	pressed = 0;

	shiita = 0.0f;
	changeProduction = 0;
}

Ranking::~Ranking()
{

}

int Ranking::Init()
{
	b.newtral = LoadGraph("assets/images/UI/ButtonDefault.PNG");
	b.select = LoadGraph("assets/images/UI/ButtonSelect.PNG");
	b.pressed = LoadGraph("assets/images/UI/ButtonPress.PNG");
	back_ground = LoadGraph("assets/images/UI/RankingBack.PNG");
	netImage = LoadGraph("assets/images/Player/BugNet.PNG");
	select_x,pressed = 0;//selectはメニューの選択に利用する変数、pressedはボタンが押された場合に利用する変数
	RankingBGM2 = LoadSoundMem("assets/Audio/AS_52281_RankingBGM.wav");
	if (RankingBGM2 == -1)
	{
		return FALSE;
	}
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

	ChangeVolumeSoundMem(200, RankingBGM2);
	PlaySoundMem(RankingBGM2, DX_PLAYTYPE_LOOP);
	int loadrankdata=LoadRankData();
	if (loadrankdata != TRUE)
	{
		return FALSE;
	}

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
			PlaySoundMem(Choicebgm2, DX_PLAYTYPE_BACK);
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
			StopSoundMem(RankingBGM2);

			changeProduction++;
			shiita = 0.0f;

			pressed = TRUE;
		}

		break;
	case 2:	// =======================================================次への演出

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
	case 3:

		shiita += 2.0f * delta_second;

		// 終了
		if (shiita > 1.6f)
		{
			// 選択したシーンへ遷移
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

	return eRanking;
}

void Ranking::Draw()const
{
	Camera::DrawGraph({ 640, 360 }, 1.0, 1.0, 0.0, back_ground);

	float selectSize = 0.84f;
	float notSelectSize = 0.7f;
	int selectCharSize = 60;
	int notSelectCharSize = 50;
	Vector2D startLoc = { 350.0f, 600.0f };
	Vector2D titleLoc = { 1000.0f, 600.0f };

	if (select_x == 0)	//スタートが選択されている場合
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
		Camera::DrawString({ startLoc.x - (float)selectCharSize * 1.5f, startLoc.y }, selectCharSize, GetColor(255, 255, 255), "スタート");
	}
	else
	{
		//通常サイズに戻す
		Camera::DrawGraph(startLoc, notSelectSize, notSelectSize, 0.0, b.newtral);
		Camera::DrawString({ startLoc.x - (float)notSelectCharSize * 1.5f, startLoc.y }, notSelectCharSize, GetColor(255, 255, 255), "スタート");
	}

	if (select_x == 1)	//タイトルが選択されている場合
	{
		if (pressed == TRUE)
		{
			//ボタンを大きくする
			Camera::DrawGraph(titleLoc, selectSize, selectSize, 0.0, b.pressed);
		}
		else
		{
			//ボタンを大きくする
			Camera::DrawGraph(titleLoc, selectSize, selectSize, 0.0, b.select);
		}

		Camera::DrawString({ titleLoc.x - (float)selectCharSize * 1.5f, titleLoc.y }, selectCharSize, GetColor(255, 255, 255), "タイトル");
	}
	else
	{
		//通常サイズに戻す
		Camera::DrawGraph(titleLoc, notSelectSize, notSelectSize, 0.0, b.newtral);
		Camera::DrawString({ titleLoc.x - (float)notSelectCharSize * 1.5f, titleLoc.y }, notSelectCharSize, GetColor(255, 255, 255), "タイトル");
	}

	unsigned int color;
	for (int i = 0;i < MAX_RANK;i++)
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

		Camera::DrawString({ (float)(150 + (i / 3) * 600), (float)(115 + (i % 3) * 120) },
			100, color, "%d位 %3d匹", i + 1, ranking[i]);
	}

	Camera::Draw();

	if (changeProduction == 3)
	{
		Vector2D location = { D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f + 750.0f };
		float angle = 0.5f - (shiita - 0.6f) * 1.5f;
		angle *= DX_PI_F;
		location.x += sinf(angle) * 500.0f;
		location.y -= cosf(angle) * 500.0f;
		DrawRotaGraphF(location.x, location.y, 15.0f, angle, netImage, true);
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
	if (p_point > ranking[MAX_RANK - 1])
	{
		ranking[MAX_RANK - 1] = p_point;

		if (SortRankData() != TRUE)
		{
			return -1;
		}

		return 1;
	}

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