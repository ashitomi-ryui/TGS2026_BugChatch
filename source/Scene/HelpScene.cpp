#include"HelpScene.h"
#include"../Utilitys/Input.h"
#include"../Utilitys/Camera.h"
#include<DxLib.h>

Help::Help()
{
	
}

Help::~Help()
{

}

int Help::Init()
{
	b.newtral = LoadGraph("assets/images/UI/ButtonDefault.PNG");
	b.select = LoadGraph("assets/images/UI/ButtonSelect.PNG");
	b.pressed = LoadGraph("assets/images/UI/ButtonPress.PNG");
	back_ground = LoadGraph("assets/images/UI/HelpBack.PNG");
	controller = LoadGraph("assets/images/UI/Controller.PNG");

	HelpBGM = LoadSoundMem("assets/Audio/HelpBGM.wav");
	if (HelpBGM == -1)
	{
		return FALSE;
	}
	ChoiceSE2 = LoadSoundMem("assets/Audio/AS_865704_8bitな選択音.wav");
	if (ChoiceSE2 == -1)
	{
		return FALSE;
	}
	DecisionSE2 = LoadSoundMem("assets/Audio/AS_134044_決定音.wav");
	if (DecisionSE2 == -1)
	{
		return FALSE;
	}

	PlaySoundMem(HelpBGM, DX_PLAYTYPE_LOOP);
	select_x, pressed = 0;//selectはメニューの選択に利用する変数、pressedはボタンが押された場合に利用する変数
	time = 0.0f;
	time_rug = 0.5f;

	return TRUE;
}

eSceneType Help::Update(float delta_second)
{
	time += delta_second;

	if (pressed == FALSE)//決定ボタンが押されていない場合
	{
		time_rug += delta_second;
	}
	if (time >= time_rug)
	{
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

	if (pressed == 0)
	{
		if (GetLeftStickState_X(true) == ePressed)//左スティックが上に入力された場合
		{
			PlaySoundMem(ChoiceSE2, DX_PLAYTYPE_BACK);
			if (select_x == 0)
			{
				select_x = 1;
			}
			else
			{
				select_x = 0;
			}
		}
		if (GetLeftStickState_X(false) == ePressed)//左スティックが下に入力された場合
		{
			PlaySoundMem(ChoiceSE2, DX_PLAYTYPE_BACK);
			if (select_x == 1)
			{
				select_x = 0;
			}
			else
			{
				select_x = 1;
			}
		}

		if (GetButtonState(XINPUT_BUTTON_A) == ePressed)//スタートが選択されているかつAボタンが押された場合
		{
			PlaySoundMem(DecisionSE2, DX_PLAYTYPE_BACK);
			StopSoundMem(HelpBGM);

			pressed = TRUE;
		}
	}

	return eHelp;
}

void Help::Draw()const
{
	Camera::DrawGraph({ 640,365 }, 1.0, 1.0, 0.0, back_ground);
	Camera::DrawGraph({ 640,230 }, 1.0, 1.0, 0.0, controller);

	Camera::DrawString({ 200,130 }, 55, GetColor(255, 255, 255), "キャラ操作");
	Camera::DrawString({ 850,320 }, 55, GetColor(255, 255, 255), "網を操作");

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
}

