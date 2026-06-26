#include"InGameScene.h"
#include"SceneManager.h"
#include"../Object/ObjectManager.h"
#include"../Utilitys/Input.h"
#include"../Utilitys/Camera.h"
#include"../Utilitys/Random.h"
#include<DxLib.h>

#include"../Object/Cage.h"
#include "../Object/FlowingTime.h"

int InGame::groundImage = -1;
int InGame::productionImage[6] = {};

FlowingTime flowingTime;

InGame::InGame()
{
	get[3] = {};
	timer = 0.0f;
	timeStep = 0;

	BGM = -1;
	countSE = -1;
	FinishSE = -1;
	ThirtycountSE = -1;
	FcountSE = -1;

	changeProduction = 0;	// シーン切替演出
	shiita = 0.0f;

	isCountSEPlayed = false;
	isFinishSE = false;
	isThirtySEPlayed = false;
	isFcountSEPlayed = false;
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
	countSE = LoadSoundMem("assets/Audio/countSE.wav");
	if (countSE == -1)
	{
		return FALSE;
	}
	ThirtycountSE = LoadSoundMem("assets/Audio/jihou_30byou_01.wav");
	if (ThirtycountSE == -1)
	{
		return FALSE;
	}
	TFifteencountSE = LoadSoundMem("assets/Audio/15count.wav");
	if (TFifteencountSE == -1)
	{
		return FALSE;
	}
	FinishSE = LoadSoundMem("assets/Audio/Finish.wav");
	if (FinishSE == -1)
	{
		return FALSE;
	}
	FcountSE = LoadSoundMem("assets/Audio/54321.wav");
	if (FcountSE == -1)
	{
		return FALSE;
	}
	/*whistleSE = LoadSoundMem("assets/Audio/AS_41577_ビーッ（ホイッスル、警笛の音）.wav");
	if(whistleSE==-1)
	{
		return FALSE;
	}*/
	timer = 3.0f;
	timeStep = 0;

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
				timer = 3.0f;
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
		timer -= delta_second;
		
		if (!isCountSEPlayed)
		{
			PlaySoundMem(countSE, DX_PLAYTYPE_BACK);
			isCountSEPlayed = true;
		}

		if (timer <= 0.0f)
		{
			// 次の演出
			changeProduction++;
			timer = D_TIME_LIMIT;
			isCountSEPlayed = false;
		}
		
		break;

	case 4:	// ==============================================ゲームプレイ
		timer -= delta_second;

		if (timer <= 5.0f && !isFcountSEPlayed)
		{
			PlaySoundMem(FcountSE, DX_PLAYTYPE_BACK);
			FcountSE = true;
		}

		if (timer <= 15.0f && !isTFifteenSEPlayed)
		{
			PlaySoundMem(TFifteencountSE, DX_PLAYTYPE_BACK);
			TFifteencountSE = true;
		}

		if (timer <= 30.0f && !isThirtySEPlayed)
		{
			PlaySoundMem(ThirtycountSE, DX_PLAYTYPE_BACK);
			isThirtySEPlayed = true;
		}

		if (timer <= 0.0f)
		{
			if (!isFinishSE)
			{
				PlaySoundMem(FinishSE, DX_PLAYTYPE_BACK);
				isFinishSE = true;
			}

			timer = 2.0f;

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

		switch (timeStep)
		{
		case 0:
			if (timer <= (float)((int)(D_TIME_LIMIT / 2.0f) / 10 * 10))
			{
				flowingTime.Flow((int)(D_TIME_LIMIT / 2.0f) / 10 * 10, 0xffffff);
				timeStep++;
			}
			break;
		case 1:
			if (timer <= (float)((int)(D_TIME_LIMIT / 4.0f) / 5 * 5))
			{
				flowingTime.Flow((int)(D_TIME_LIMIT / 4.0f) / 5 * 5, 0xffff00);
				timeStep++;
			}
			break;
		default:
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

		ObjectManager::UpdateCicadaAudio();
		ObjectManager::UpdateGrasshopperAudio();


		// かごの更新
		Cage::Update(eInGame, delta_second);

		//// 音再生・停止
		//Cicada::PlayAudio();

		flowingTime.Update(delta_second);

		break;
	case 5:// ==============================================ゲーム終了
		timer -= delta_second;

		if (timer <= 0.0f)
		{
			timer = 0.0;
			changeProduction++;
			shiita = 0.0f;
		}

		break;
	case 6:
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

	unsigned int cageColor = 0xffffff;
	unsigned int timeColor = 0xff0000;
	Vector2D playerLocation = ObjectManager::GetPlayerLocation();

	// 虫かごがプレイヤーや虫と重なったとき
	if (ObjectManager::CheckUIOverlapping(240.0f, 210.0f + 50.0f))
	{
		// 色を薄くする
		cageColor += 0x60000000;
	}

	// 54321の残り時間がプレイヤーや虫と重なったとき
	if (ObjectManager::CheckUIOverlapping(0.0f, 0.0f, { D_WIN_WIDTH / 2.0f + 10.0f, D_WIN_HEIGHT / 2.0f - 150.0f }))
	{
		// 色を薄くする
		timeColor += 0xe0000000;
	}

	switch(changeProduction)
	{
	case 3:
		Camera::DrawString({ D_WIN_WIDTH / 2.0f + 10.0f, D_WIN_HEIGHT / 2.0f - 150.0f }, 100, 0xffffff, "%d", (int)timer + 1);
		break;
	case 4:
		if (timer >= 59.0f)
		{
			Camera::DrawString({ D_WIN_WIDTH / 2.0f - 150.0f, D_WIN_HEIGHT / 2.0f - 150.0f }, 100, 0xffffff, "スタート！");
		}

		Camera::DrawString({ 25.0f, 230.0f }, 50, cageColor, "のこり%d秒", (int)timer + 1);

		// 54321を表示
		if (timer < 5.0f)
		{
			Camera::DrawString({ D_WIN_WIDTH / 2.0f + 10.0f, D_WIN_HEIGHT / 2.0f - 150.0f }, 100, timeColor, "%d", (int)timer + 1);
		}

		break;
	case 5:
		Camera::DrawString({ D_WIN_WIDTH / 2.0f - 150.0f, D_WIN_HEIGHT / 2.0f - 150.0f }, 100, 0xffffff, "そこまで！");
		break;
	}

	flowingTime.Draw();

	if(changeProduction > 3)
	{
		Cage::Draw(eInGame, cageColor);
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

		Camera::DrawGraph({ D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f + 40.0f }, 80.0f, 80.0f, 0.0f, productionImage[4 + animCount]);

		break;
	}
}
