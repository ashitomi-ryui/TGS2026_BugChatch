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
int Title::netImage = -1;

int Title::select_x = 0;
int Title::select_y = 0;
int Title::pressed = 0;


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
	b.newtral = LoadGraph("assets/images/UI/ButtonDefault.PNG");
	b.select = LoadGraph("assets/images/UI/ButtonSelect.PNG");
	b.pressed = LoadGraph("assets/images/UI/ButtonPress.PNG");
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
		select_x = 0;
		select_y = 0;
		pressed = 0;

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
		Camera::SetScreenRatioSize(shiita);

		break;
	case 1:	// ============================================================================選択
		Camera::SetScreenLocation({ D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f });
		Camera::SetScreenRatioSize(1.0f);

		if (GetLeftStickState_Y(true) == ePressed)//左スティックが上に入力された場合
		{
			PlaySoundMem(ChoiceSE, DX_PLAYTYPE_BACK, TRUE);
			if (select_x == 1)
			{
				select_x = 0;
			}
			if (select_y == 0)//一番上が選択されている状態の場合
			{
				select_y = 2;//一番下へ戻す
			}
			else
			{
				select_y--;//上へ移動する
			}
		}
		if (GetLeftStickState_Y(false) == ePressed)//左スティックが下に入力された場合
		{
			PlaySoundMem(ChoiceSE, DX_PLAYTYPE_BACK, TRUE);
			if (select_x == 1)
			{
				select_x = 0;
			}
			if (select_y == 2)//一番下が選択されている状態の場合
			{
				select_y = 0;//一番上へ戻す
			}
			else
			{
				select_y++;//下へ移動する
			}
		}
		if (GetLeftStickState_X(true) == ePressed)//左スティックが右に入力された場合
		{
			PlaySoundMem(ChoiceSE, DX_PLAYTYPE_BACK, TRUE);
			if (select_y == 0 || select_y == 2)
			{
				select_y = 1;
			}
			if (select_x == 1)//一番右が選択されている状態の場合
			{
				select_x = 0;//左へ戻す
			}
			else
			{
				select_x++;//右へ移動する
			}
		}
		if (GetLeftStickState_X(false) == ePressed)//左スティックが左に入力された場合
		{
			PlaySoundMem(ChoiceSE, DX_PLAYTYPE_BACK, TRUE);
			if (select_x == 0)//一番左が選択されている場合
			{
				select_x = 1;//右へ戻す
			}
			else
			{
				select_x--;//左へ移動する
			}
		}

		if (GetButtonState(XINPUT_BUTTON_A) == ePressed)//Aボタンが押された場合
		{
			PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
			StopSoundMem(Titlebgm);

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
			if (select_x == 0)
			{
				switch (select_y)
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
				}
			}
			else
			{
				return eRanking;
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
	
	return eTitle;//タイトル画面を維持
}

void Title::Draw()const
{
	Camera::DrawGraph({ 640, 360 }, 25.0, 12.0, 0.0, back_ground);

	Camera::DrawGraph({ 640,170 }, 1.5, 1.0, 0.0, title_logo);

	float selectSize = 0.75f;
	float notSelectSize = 0.5f;
	int selectCharSize = 75;
	int notSelectCharSize = 50;

	Vector2D startLoc = { 640.0f, 400.0f };
	Vector2D helpLoc = { 640.0f, 520.0f };
	Vector2D rankingLoc = { 1000.0f, 520.0f };
	Vector2D endLoc = { 640.0f, 640.0f };

	if (select_y == 0)	//スタートが選択されている場合
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
		Camera::DrawString({ startLoc.x - (float)selectCharSize * 1.5f, startLoc.y - 5.0f }, selectCharSize, GetColor(255, 255, 255), "スタート");
	}
	else
	{
		//通常サイズに戻す
		Camera::DrawGraph(startLoc, notSelectSize, notSelectSize, 0.0, b.newtral);
		Camera::DrawString({ startLoc.x - (float)notSelectCharSize * 1.5f, startLoc.y - 5.0f }, notSelectCharSize, GetColor(255, 255, 255), "スタート");
	}

	if (select_y == 1 && select_x == 0)	//ヘルプが選択されている場合
	{
		if (pressed == TRUE)
		{
			//ボタンを大きくする
			Camera::DrawGraph(helpLoc, selectSize, selectSize, 0.0, b.pressed);
		}
		else
		{
			//ボタンを大きくする
			Camera::DrawGraph(helpLoc, selectSize, selectSize, 0.0, b.select);
		}

		Camera::DrawString({ helpLoc.x - (float)selectCharSize * 1.0f, helpLoc.y - 5.0f }, selectCharSize, GetColor(255, 255, 255), "ヘルプ");
	}
	else
	{
		//通常サイズに戻す
		Camera::DrawGraph(helpLoc, notSelectSize, notSelectSize, 0.0, b.newtral);
		Camera::DrawString({ helpLoc.x - (float)notSelectCharSize * 1.0f, helpLoc.y - 5.0f }, notSelectCharSize, GetColor(255, 255, 255), "ヘルプ");
	}

	if (select_y == 1 && select_x == 1)	//ランキングが選択されている場合
	{
		if (pressed == TRUE)
		{
			//ボタンを大きくする
			Camera::DrawGraph(rankingLoc, selectSize, selectSize, 0.0, rank_b.pressed);
		}
		else
		{
			//ボタンを大きくする
			Camera::DrawGraph(rankingLoc, selectSize, selectSize, 0.0, rank_b.select);
		}
	}
	else
	{
		//通常サイズに戻す
		Camera::DrawGraph(rankingLoc, notSelectSize, notSelectSize, 0.0, rank_b.newtral);
	}

	if (select_y == 2)	//おわりが選択されている場合
	{
		if (pressed == TRUE)
		{
			//ボタンを大きくする
			Camera::DrawGraph(endLoc, selectSize, selectSize, 0.0, b.pressed);
		}
		else
		{
			//ボタンを大きくする
			Camera::DrawGraph(endLoc, selectSize, selectSize, 0.0, b.select);
		}

		Camera::DrawString({ endLoc.x - (float)selectCharSize * 1.0f, endLoc.y - 10.0f }, selectCharSize, GetColor(255, 255, 255), "おわり");
	}
	else
	{
		//通常サイズに戻す
		Camera::DrawGraph(endLoc, notSelectSize, notSelectSize, 0.0, b.newtral);
		Camera::DrawString({ endLoc.x - (float)notSelectCharSize * 1.0f, endLoc.y - 10.0f }, notSelectCharSize, GetColor(255, 255, 255), "おわり");
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