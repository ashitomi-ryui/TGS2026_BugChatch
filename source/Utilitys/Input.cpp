//==========================================================
// ファイル: Input.cpp
// 概要: キーボードとゲームパッドの入力処理実装
//==========================================================
#include "Input.h"
#include <DxLib.h>
#include <math.h>

// キー/ボタンの最大数
#define D_KEYCODE_MAX	(256)
#define D_BUTTON_MAX	(16)

// 現在/前フレームの入力状態
char now_key[D_KEYCODE_MAX];				// 現在フレームのキー状態
char old_key[D_KEYCODE_MAX];				// 1フレーム前のキー状態
unsigned char now_button[16];				// 現在フレームのボタン状態
unsigned char old_button[16];				// 1フレーム前のボタン状態
Vector2D now_stick_left;
Vector2D old_stick_left;

// アナログ入力
Vector2D left_stick;						// 左スティック(正規化済み)
Vector2D right_stick;						// 右スティック(正規化済み)
float left_trigger;							// 左トリガー(0.0?1.0)
float right_trigger;						// 右トリガー(0.0?1.0)

// フィルタ関数
float Filter1D(unsigned char value);		// 0..UCHAR_MAX を 0.0..1.0 に正規化
Vector2D Filter2D(short vx, short vy);		// デッドゾーン&正規化

void InputInit(void)
{
	// 配列クリアとアナログ初期化
	memset(now_key, 0, (sizeof(char) * D_KEYCODE_MAX));
	memset(old_key, 0, (sizeof(char) * D_KEYCODE_MAX));

	memset(now_button, 0, (sizeof(char) * D_BUTTON_MAX));
	memset(old_button, 0, (sizeof(char) * D_BUTTON_MAX));

	left_stick.x = 0.0f; left_stick.y = 0.0f;
	right_stick.x = 0.0f; right_stick.y = 0.0f;
	left_trigger = 0.0f; right_trigger = 0.0f;
}

void InputUpdate(void)
{
	old_stick_left = left_stick;
	// キー状態更新(過去→現在)
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));
	GetHitKeyStateAll(now_key);

	// XInput のゲームパッド状態取得
	XINPUT_STATE controller = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &controller);
	memcpy(old_button, now_button, (sizeof(unsigned char) * D_BUTTON_MAX));
	memcpy(now_button, controller.Buttons, (sizeof(unsigned char) * D_BUTTON_MAX));
	left_stick = Filter2D(controller.ThumbLX, controller.ThumbLY);
	right_stick = Filter2D(controller.ThumbRX, controller.ThumbRY);
	left_trigger = Filter1D(controller.LeftTrigger);
	right_trigger = Filter1D(controller.RightTrigger);
}

eInputState GetKeyInputState(int key)
{
	// 指定キーの状態遷移を返す
	if (0 <= key && key < D_KEYCODE_MAX)
	{
		if (old_key[key] == TRUE)
		{
			if (now_key[key] == TRUE)
			{
				return eHeld;							// 押しっぱなし
			}
			else
			{
				return eReleased;						// 離された瞬間
			}
		}
		else
		{
			if (now_key[key] == TRUE) return ePressed;	// 押された瞬間
		}
	}
	return eNone;										// 非入力
}

eInputState GetLeftStickState_X(bool direction)
{
	int n;
	if (direction)
	{
		n = 1;
	}
	else
	{
		n = -1;
	}

	if (n * old_stick_left.x > 0.5f)
	{
		if (n * left_stick.x > 0.5f)
		{
			return eHeld;							// 押しっぱなし
		}
		else
		{
			return eReleased;						// 離された瞬間
		}
	}
	else
	{
		if (n * left_stick.x > 0.5f)
		{
			return ePressed;						// 押された瞬間
		}
	}
	return eNone;
}

eInputState GetLeftStickState_Y(bool direction)
{
	int n;
	if (direction)
	{
		n = 1;
	}
	else
	{
		n = -1;
	}

	if (n * old_stick_left.y > 0.5f)
	{
		if (n * left_stick.y > 0.5f)
		{
			return eHeld;							// 押しっぱなし
		}
		else
		{
			return eReleased;						// 離された瞬間
		}
	}
	else
	{
		if (n * left_stick.y > 0.5f)
		{
			return ePressed;						// 押された瞬間
		}
	}
	return eNone;
}

eInputState GetButtonState(int button)
{
	// 指定ボタンの状態遷移を返す
	if (0 <= button && button < D_BUTTON_MAX)
	{
		if (old_button[button] == TRUE)
		{
			if (now_button[button] == TRUE)
			{
				return eHeld;							// 押しっぱなし
			}
			else
			{
				return eReleased;						// 離された瞬間
			}
		}
		else
		{
			if (now_button[button] == TRUE)
			{
				return ePressed;						// 押された瞬間
			}
		}
	}
	return eNone;										// 非入力
}

Vector2D GetLeftStick()
{
	return left_stick;									// 左スティック
}

Vector2D GetRightStick()
{
	return right_stick;									// 右スティック
}

float GetLeftTrigger()
{
	return left_trigger;								// 左トリガー
}

float GetRightTrigger()
{
	return right_trigger;								// 右トリガー
}

float Filter1D(unsigned char value)
{
	// 0?UCHAR_MAX を 0.0?1.0 に正規化
	float result = (float)value / (float)UCHAR_MAX;
	return result;
}

Vector2D Filter2D(short vx, short vy)
{
	// スティック入力のデッドゾーン処理 + 正規化
	const float dead_zone = 8000.0f;	// A value < dead zone is interpreted as 0%
	const float max_value = 30000.0f;	// A value > max value is interpreted as 100%
	Vector2D result = {};
	result.x = (float)vx;
	result.y = (float)vy;

	float len = Length(result);

	if (len < dead_zone)
	{
		result.x = 0.0f;
		result.y = 0.0f;
	}
	else
	{
		float f = (len - dead_zone) / (max_value - dead_zone);
		f = Clamp(f, 0.0f, 1.0f);
		result.x *= f / len;
		result.y *= f / len;
	}

	return result;
}
