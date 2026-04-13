#include <DxLib.h>
#include"../source/Utilitys/Input.h"
#include"../source/Scene/SceneManager.h"

float GetDeltaSecond();

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(640, 480, 32);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	if (SceneInit() != TRUE)//シーンの初期化
	{
		//異常終了を行う
		DxLib_End();//DXライブラリの使用を終了する
		return -1;
	}
	while (ProcessMessage() != -1)
	{
		InputUpdate();
		int result = SceneUpdate(GetDeltaSecond());

		//シーン継続不可orESCキーが離された瞬間
		if (result != TRUE || GetKeyInputState(KEY_INPUT_ESCAPE) == eReleased)
		{
			break;//ゲーム終了
		}
		ClearDrawScreen();
		SceneDraw();
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}

float GetDeltaSecond()
{
	static LONGLONG old_time = GetNowHiPerformanceCount();//前フレーム時刻を保持

	LONGLONG current_time = GetNowHiPerformanceCount();//現在時刻取得
	float result = (float)(current_time - old_time) * 1.0e-6f;//経過時間μs→秒に変換
	old_time = current_time;//前フレーム時刻を更新

	return result;//1フレームにかかった時間を返す
}