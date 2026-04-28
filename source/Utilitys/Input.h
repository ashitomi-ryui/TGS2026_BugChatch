#pragma once

#include "Math.h"

// 入力状態の列挙(キー/ボタン)
enum eInputState
{
	eNone,		// 非入力
	ePressed,	// 今フレームで押された
	eReleased,	// 今フレームで離された
	eHeld,		// 押しっぱなし
};

// 初期化・更新・状態取得
void InputInit(void);					// 入力バッファ初期化
void InputUpdate(void);					// 入力バッファ更新

eInputState GetKeyInputState(int key);	// キーの状態取得

/// <summary>
/// 左スティックの上下入力状態を取得
/// </summary>
/// <param name="direction">true:上, false:下</param>
/// <returns></returns>
eInputState GetLeftStickState_Y(bool direction);

/// <summary>
/// 左スティックの左右入力状態を取得
/// </summary>
/// <param name="direction">true:多分右, false:多分左</param>
/// <returns></returns>
eInputState GetLeftStickState_X(bool direction);

eInputState GetButtonState(int button);	// ボタンの状態取得

Vector2D GetLeftStick();				// 左スティック(正規化済み)
Vector2D GetRightStick();				// 右スティック(正規化済み)
float GetLeftTrigger();					// 左トリガー(0.0?1.0)
float GetRightTrigger();				// 右トリガー(0.0?1.0)