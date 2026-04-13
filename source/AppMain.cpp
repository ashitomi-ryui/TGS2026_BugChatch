#include <DxLib.h>

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(640, 480, 32);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() != -1)
	{
		ClearDrawScreen();
		
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}
