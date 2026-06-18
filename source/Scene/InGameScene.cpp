#include"InGameScene.h"
#include"SceneManager.h"
#include"../Object/ObjectManager.h"
#include"../Utilitys/Input.h"
#include"../Utilitys/Camera.h"
#include"../Utilitys/Random.h"
#include<DxLib.h>

#include"../Object/Cage.h"

Icon icon;
int get[3] = {};
float timer;
int BGM;
int groundImage = -1;

int changeProduction;	// シーン切替演出
float shiita;

int InGameInit(void)//各プログラムの初期化
{
	ObjectManager::Init();

	Cage::Init(eInGame);

	BGM = LoadSoundMem("assets/Audio/AS_1468345_Main.wav");
	if (BGM == -1)
	{
		return FALSE;
	}

	timer = 0.0f;
	
	icon.cicada = LoadGraph("assets/images/UI/CicadaIcon.PNG");
	icon.dragonfly = LoadGraph("assets/images/UI/DragonflyIcon.PNG");
	icon.grasshopper = LoadGraph("assets/images/UI/GrasshopperIcon.PNG");
	
	for (int i = 0; i < 3; i++)
	{
		get[i] = 0;
	}
	groundImage = LoadGraph("assets/images/OtherObjects/Ground.PNG");

	ChangeVolumeSoundMem(230, BGM);
	PlaySoundMem(BGM, DX_PLAYTYPE_BACK);

	changeProduction = 0;
	shiita = 0.0f;

	Camera::SetScreenLocation({ -D_WIN_WIDTH / 4.0f, D_WIN_HEIGHT / 4.0f });
	Camera::SetScreenRatioSize(0.2f);

	return TRUE;
}

eSceneType InGameUpdate(float delta_second)
{
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
			changeProduction = 1;
		}

		Camera::SetScreenLocation(loc);

		break;
	case 1:
		shiita -= 2.0f * delta_second;

		if (shiita < -1.0f)
		{
			shiita = -1.0f; // 行き過ぎ防止

			// 次の演出
			changeProduction = 2;
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
				changeProduction = 3;
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

		if (timer >= 3.0f)
		{
			// 次の演出
			changeProduction = 4;
			timer = 0.0f;
		}

		break;

	case 4:	// ==============================================ゲームプレイ
		timer += delta_second;
#ifndef _DEBUG
		if (timer > 0)
		{
			timer = 0.0f;

			// 音を止める
			StopSoundMem(BGM);

			Grasshopper::StopAudio();
			Cicada::StopAudio();
			
			// 次の演出
			changeProduction = 5;

			break;
		}
#endif
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
			changeProduction = 6;
		}

		break;
	case 6:	
		timer += delta_second;

		if (timer > 0.0f)
		{
			changeProduction = 7;
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

void InGameDraw(void)
{
	// 背景の表示
	for (float i = 0;i < D_STAGE_WIDTH;i += 30.0f * 3.0f * D_OBJECT_SIZE_RATIO)
	{
		for (float j = 0;j < D_STAGE_HEIGHT;j += 30.0f * 3.0f * D_OBJECT_SIZE_RATIO)
		{
			Camera::DrawGraphW({ i, j }, 3.0f * D_OBJECT_SIZE_RATIO, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, groundImage);
		}
	}

	ObjectManager::Draw();

	unsigned int color = 0xffffff;
	// UIがプレイヤーと重なったとき
	Vector2D playerLocation = ObjectManager::GetPlayerLocation();
	if (playerLocation.x < 180.0f * D_CAGE_RATIO &&
		playerLocation.y < 160.0f * D_CAGE_RATIO + 50.0f)
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
}