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
	back_ground = LoadGraph("assets/images/Help/teacher.jpg");
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
	select_y, pressed = 0;//selectはメニューの選択に利用する変数、pressedはボタンが押された場合に利用する変数
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
		switch (select_y)
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
		if (GetLeftStickState_Y(true) == ePressed)//左スティックが上に入力された場合
		{
			PlaySoundMem(ChoiceSE2, DX_PLAYTYPE_BACK);
			if (select_y == 0)
			{
				select_y = 1;
			}
			else
			{
				select_y = 0;
			}
		}
		if (GetLeftStickState_Y(false) == ePressed)//左スティックが下に入力された場合
		{
			PlaySoundMem(ChoiceSE2, DX_PLAYTYPE_BACK);
			if (select_y == 1)
			{
				select_y = 0;
			}
			else
			{
				select_y = 1;
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
	Camera::DrawGraph({ 640,280 }, 1.0, 1.0, 0.0, controller);

	Camera::DrawString({ 360,115 }, 60, GetColor(255, 255, 255), "網で虫をいっぱい捕れ！");
	Camera::DrawString({ 180,195 }, 55, GetColor(255, 255, 255), "キャラ操作");
	Camera::DrawString({ 860,375 }, 55, GetColor(255, 255, 255), "網を操作");

	if (select_y == 0)
	{
		if (pressed == TRUE)
		{
			Camera::DrawGraph({ 640, 465 }, 0.7, 0.7, 0.0, b.pressed);//ボタンを押された状態にする
		}
		else
		{
			Camera::DrawGraph({ 640, 465 }, 0.7, 0.7, 0.0, b.select);
		}

		Camera::DrawString({ 561, 460 }, 55, GetColor(255, 255, 255), "スタート");
	}
	else
	{
		Camera::DrawGraph({ 640, 465 }, 0.6, 0.6, 0.0, b.newtral);
		Camera::DrawString({ 561, 460 }, 50, GetColor(255, 255, 255), "スタート");
	}
	
	if (select_y == 1)
	{
		if (pressed == TRUE)
		{
			Camera::DrawGraph({ 640, 605 }, 0.7, 0.7, 0.0, b.pressed);//ボタンを押された状態にする
		}
		else
		{
			Camera::DrawGraph({ 640, 605 }, 0.7, 0.7, 0.0, b.select);//ボタンを押された状態にする
		}

		Camera::DrawString({ 561, 600 }, 55, GetColor(255, 255, 255), "タイトル");
	}
	else
	{
		Camera::DrawGraph({ 640, 605 }, 0.6, 0.6, 0.0, b.newtral);//ボタンを押された状態にする
		Camera::DrawString({ 561, 600 }, 50, GetColor(255, 255, 255), "タイトル");
	}
}

