#include"InGameScene.h"
#include"SceneManager.h"
#include"../Object/ObjectManager.h"
#include"../Utilitys/Input.h"
#include"../Utilitys/Camera.h"
#include"../Utilitys/Random.h"
#include<DxLib.h>

#include"../Object/Cage.h"

int InGame::groundImage = -1;
int InGame::productionImage[6] = {};

InGame::InGame()
{
	get[3] = {};
	timer = 0.0f;

	BGM = -1;
	countSE = -1;
	FinishSE = -1;

	changeProduction = 0;	// シーン切替演出
	shiita = 0.0f;

	isCountSEPlayed = false;
	isFinishSE = false;
}

InGame::~InGame()
{
}



int InGame::Init()//各プログラムの初期化
{
	ObjectManager::Init();

	Cage::Init(eInGame);

	BGM = LoadSoundMem("assets/Audio/AS_1468345_Main.wav");
	if (BGM == -1)
	{
		return FALSE;
	}
	countSE = LoadSoundMem("assets/Audio/AS_1274842_３２１GO！・キャラクター達の競争.wav");
	if (countSE == -1)
	{
		return FALSE;
	}
	FinishSE = LoadSoundMem("assets/Audio/Finish.wav");
	if (FinishSE == -1)
	{
		return FALSE;
	}
	timer = 0.0f;

	for (int i = 0; i < 3; i++)
	{
		get[i] = 0;
	}
	groundImage = LoadGraph("assets/images/OtherObjects/Ground.PNG");
	productionImage[0] = LoadGraph("assets/images/UI/SceneProduction/Dragonfly1.PNG");
	productionImage[1] = LoadGraph("assets/images/UI/SceneProduction/Dragonfly2.PNG");
	productionImage[2] = LoadGraph("assets/images/UI/SceneProduction/Dragonfly3.PNG");
	productionImage[3] = LoadGraph("assets/images/UI/SceneProduction/Dragonfly4.PNG");
	productionImage[4] = LoadGraph("assets/images/UI/SceneProduction/Dragonfly5.PNG");
	productionImage[5] = LoadGraph("assets/images/UI/SceneProduction/Dragonfly6.PNG");

	ChangeVolumeSoundMem(130, BGM);
	PlaySoundMem(BGM, DX_PLAYTYPE_BACK);

	changeProduction = 0;
	shiita = 0.0f;

	animTime = 0.0f;
	animCount = 0;

	Camera::SetScreenLocation({ -D_WIN_WIDTH / 4.0f, D_WIN_HEIGHT / 4.0f });
	Camera::SetScreenRatioSize(0.2f);

	return TRUE;
}

eSceneType InGame::Update(float delta_second)
{
	if (changeProduction != 4)
	{
		animTime += delta_second;

		if (animTime >= 0.025f)
		{
			animCount = (animCount + 1) % 2;
			animTime = 0.0f;
		}
	}

	switch (changeProduction)
	{
	case 0:	// ==============================================ゲームスタート
		shiita -= 2.0f * delta_second;

		Vector2D loc = Camera::GetScreenLocation();

		loc.x += D_WIN_WIDTH * 1.5f * delta_second;
		loc.y = D_WIN_HEIGHT / 4.0f + sinf(shiita * DX_PI_F) * D_WIN_HEIGHT * 0.1f;

		if (loc.x >= D_WIN_WIDTH / 2.0f)
		{
			loc.x = D_WIN_WIDTH / 2.0f;
			// 次の演出
			changeProduction++;
		}

		Camera::SetScreenLocation(loc);

		break;
	case 1:
		shiita -= 2.0f * delta_second;

		if (shiita < -1.0f)
		{
			shiita = -1.0f; // 行き過ぎ防止

			// 次の演出
			changeProduction++;
			shiita = 0.0f;
		}

		Camera::SetScreenLocation({ D_WIN_WIDTH / 2.0f,
			D_WIN_HEIGHT / 4.0f + sinf(shiita * DX_PI_F) * D_WIN_HEIGHT * 0.1f });

		break;
	case 2:
		shiita -= 2.0f * delta_second;

		{
			float ratio = Camera::GetScreenRatioSize();
			ratio += ratio * 3.2f * delta_second;
			if (ratio > 1.0f)
			{
				ratio = 1.0f;
			}

			if (shiita < -1.0f)
			{
				shiita = -1.0f; // 行き過ぎ防止

				// 次の演出
				changeProduction++;
				timer = 0.0f;
				ratio = 1.0f;
			}

			//ジャンプの移動処理
			float height = sinf(shiita * DX_PI_F) * (D_WIN_HEIGHT / 2.0f);
			Camera::SetScreenLocation({ D_WIN_WIDTH / 2.0f,
				D_WIN_HEIGHT / 4.0f + (D_WIN_HEIGHT / -4.0f) * shiita - height });

			Camera::SetScreenRatioSize(ratio);
		}

		break;
	case 3:
		timer += delta_second;
		
		if (!isCountSEPlayed)
		{
			PlaySoundMem(countSE, DX_PLAYTYPE_BACK);
			isCountSEPlayed = true;
		}

		if (timer >= 3.0f)
		{
			// 次の演出
			changeProduction++;
			timer = 0.0f;
			isCountSEPlayed = false;
		}
		
		break;

	case 4:	// ==============================================ゲームプレイ
		timer += delta_second;
		if (timer > D_TIME_LIMIT)
		{
			if (!isFinishSE)
			{
				PlaySoundMem(FinishSE, DX_PLAYTYPE_BACK);
				isFinishSE = true;
			}

			timer = 0.0f;

			// 音を止める
			StopSoundMem(BGM);

			Grasshopper::StopAudio();
			Cicada::StopAudio();

			// 次の演出
			changeProduction++;
			isFinishSE = false;

			animTime = 0.0f;
			animCount = 0;

			break;
		}

		// 画面内にいるかの初期化
		Cicada::WithinTheScreenInit();

		for (int i = 0; i < 3; i++)
		{
			switch (i)
			{
			case 0:
				get[i] = Bug::GetCicadaCount();
				break;
			case 1:
				get[i] = Bug::GetDragonflyCount();
				break;
			case 2:
				get[i] = Bug::GetGrasshopperCount();
				break;
			}
		}

		// かごの更新
		Cage::Update(eInGame, delta_second);

		// 音再生・停止
		Cicada::PlayAudio();

		break;
	case 5:// ==============================================ゲーム終了
		timer += delta_second;

		if (timer > 2.0f)
		{
			timer = 0.0;
			changeProduction++;
		}

		break;
	case 6:	
		timer += delta_second;

		if (timer > 0.0f)
		{
			changeProduction++;
			shiita = 0.0f;
		}
		break;
	case 7:
		shiita -= 2.0f * delta_second;

		{
			float ratio = Camera::GetScreenRatioSize();
			ratio -= ratio * 3.2f * delta_second;
			if (ratio > 1.0f)
			{
				ratio = 1.0f;
			}

			if (shiita < -1.5f)
			{
				return eResult;	//ゲーム終了時にリザルトに遷移
				timer = 0.0f;
			}

			//ジャンプの移動処理
			float height = cosf(shiita * DX_PI_F) * (D_WIN_HEIGHT);
			Camera::SetScreenLocation({ D_WIN_WIDTH / 2.0f,
				D_WIN_HEIGHT * 3.0f / 2.0f + (D_WIN_HEIGHT * 3.0f / 2.0f) * shiita - height });

			Camera::SetScreenRatioSize(ratio);
		}
		break;
	}
	
	ObjectManager::Update(changeProduction, delta_second);

	return eInGame;
}

void InGame::Draw() const
{
	// 背景の表示
	for (float i = 0;i < D_STAGE_WIDTH;i += 30.0f * 2.0f)
	{
		for (float j = 0;j < D_STAGE_HEIGHT;j += 30.0f * 2.0f)
		{
			Camera::DrawGraphW({ i, j }, 2.0f, 2.0f, 0.0f, groundImage);
		}
	}

	ObjectManager::Draw();

	unsigned int color = 0xffffff;
	Vector2D playerLocation = ObjectManager::GetPlayerLocation();

	// UIがプレイヤーや虫と重なったとき
	if (ObjectManager::CheckUIOverlapping(180.0f * D_CAGE_RATIO, 160.0f * D_CAGE_RATIO + 50.0f))
	{
		// 色を薄くする
		color += 0x60000000;
	}

	switch(changeProduction)
	{
	case 3:
		Camera::DrawString({ D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f - 100.0f }, 75, 0xffffff, "%d", 3 - (int)timer);
		break;
	case 4:
		if (timer <= 1.0f)
		{
			Camera::DrawString({ D_WIN_WIDTH / 2.0f - 120.0f, D_WIN_HEIGHT / 2.0f - 100.0f }, 75, 0xffffff, "スタート！");
		}

		Camera::DrawString({ 25.0f, 150.0f * D_CAGE_RATIO }, 50, color, "のこり%d秒", 60 - (int)timer);

		//// スコアの表示
		//Camera::DrawString({ 75,75 }, 40, GetColor(255, 255, 255), "%d匹", get[0]);
		//Camera::DrawString({ 75,135 }, 40, GetColor(255, 255, 255), "%d匹", get[1]);
		//Camera::DrawString({ 75,195 }, 40, GetColor(255, 255, 255), "%d匹", get[2]);

		//Camera::DrawGraph({ 25,75 }, 1.7, 1.7, 0.0, icon.cicada);
		//Camera::DrawGraph({ 25,135 }, 1.7, 1.7, 0.0, icon.dragonfly);
		//Camera::DrawGraph({ 25,195 }, 1.7, 1.7, 0.0, icon.grasshopper);
		break;
	case 5:
		Camera::DrawString({ 465,260 }, 100, GetColor(255, 255, 255), "そこまで！");
		break;
	}

	if(changeProduction > 3)
	{
		Cage::Draw(eInGame, color);
	}

	Camera::Draw();

	switch (changeProduction)
	{
	case 0:
	case 1:

		Camera::DrawGraph({ D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f + 40.0f }, 80.0f, 80.0f, 0.0f, productionImage[animCount]);

		break;
	case 2:

		Camera::DrawGraph({ D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f + 40.0f }, 80.0f, 80.0f, 0.0f, productionImage[2 + animCount]);

		break;
	case 5:
	case 6:
	case 7:

		Camera::DrawGraph({ D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f + 40.0f }, 80.0f, 80.0f, 0.0f, productionImage[4 + animCount]);

		break;
	}
}
