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
	start_not_pressed = LoadGraph("assets/images/Help/start_off.png");
	start_pressed = LoadGraph("assets/images/Help/start_on.png");
	title_not_pressed = LoadGraph("assets/images/Help/title_off.png");
	title_pressed = LoadGraph("assets/images/Help/title_on.png");
	back_ground = LoadGraph("assets/images/Help/teacher.jpg");
	controller = LoadGraph("assets/images/Help/controller.jpg");

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
	DrawRotaGraph(640, 360, 1.0, 0.0, back_ground, TRUE);

	if (select_y == 0)
	{
		if (pressed == TRUE)
		{
			DrawRotaGraph(640, 465, 1.2, 0.0, start_pressed, TRUE);
		}
		else
		{
			DrawRotaGraph(640, 465, 1.2, 0.0, start_not_pressed, TRUE);
		}
	}
	else
	{
		DrawRotaGraph(640, 465, 1.0, 0.0, start_not_pressed, TRUE);
	}
	
	if (select_y == 1)
	{
		if (pressed == TRUE)
		{
			DrawRotaGraph(640, 605, 1.2, 0.0, title_pressed, TRUE);
		}
		else
		{
			DrawRotaGraph(640, 605, 1.2, 0.0, title_not_pressed, TRUE);
		}
	}
	else
	{
		DrawRotaGraph(640, 605, 1.0, 0.0, title_not_pressed, TRUE);
	}

	Camera::DrawString({ 500,250 }, 50, GetColor(255,255,255), "ひだりすてぃっく　きゃらを操作\n　みぎすてぃっく　網を操作", NULL);
}

