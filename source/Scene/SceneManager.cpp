//概要：シーン切り替えとライフサイクル管理の実装
#include"SceneManager.h"
#include<DxLib.h>

#include"TitleScene.h"
#include"InGameScene.h"
#include"ResultScene.h"

eSceneType current_type;

Title title;

int ChangeScene(eSceneType new_scene_type);

int SceneInit(void)
{
	current_type = eTitle;//初期シーンをタイトルに設定
	if (ChangeScene(current_type) != TRUE)//タイトルシーンを初期化
	{
		return FALSE;//初期化失敗で異常
	}
	return TRUE;//初期化成功
}

int SceneUpdate(float delta_second)
{
	eSceneType next_type = eEnd;//次シーン種別を現在地で初期化
	switch (current_type)//現在シーンに応じた更新処理
	{
	case eTitle:
		next_type = title.TitleUpdate(delta_second);
		break;
	case eInGame:
		next_type = InGameUpdate(delta_second);
		break;
	case eResult:
		next_type = ResultUpdate(delta_second);
		break;
	case eRanking:
		break;
	case eEnd:
	default:
		break;
	}

	//シーン遷移が発生した場合は変更を適用
	if (next_type != current_type)
	{
		if (ChangeScene(next_type) != TRUE)
		{
			return FALSE;//遷移先初期化失敗
		}
	}

	return TRUE;//更新継続
}

void SceneDraw(void)
{
	switch (current_type)//現在シーンに応じて描画
	{
	case eTitle:
		title.TitleDraw();
		break;
	case eInGame:
		InGameDraw();
		break;
	case eResult:
		ResultDraw();
		break;
	case eRanking:
		break;
	default:
		DrawString(0, 10, "こいつはくせぇ", 0xFFFFFF);//デフォルト描画
		break;
	}
}

int ChangeScene(eSceneType new_scene_type)
{
	int result = FALSE;//遷移先初期化の成否
	switch (new_scene_type)//遷移先シーン種別に応じた初期化
	{
	case eTitle:
		result = title.TitleInit();
		break;
	case eRestart:
		new_scene_type = eInGame;
	case eInGame:
		result = InGameInit();
		break;
	case eResult:
		result = ResultInit();
		break;
	case eRanking:
		break;
	}
	current_type = new_scene_type;//現在シーンの更新
	return result;//初期化結果を返却
}