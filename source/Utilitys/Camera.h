#pragma once
#include "Math.h"

//==========================================================
// マクロ定義
//==========================================================

#define D_WIN_WIDTH		(1280)	// スクリーンの横幅
#define D_WIN_HEIGHT	(720)	// スクリーンの縦幅

#define D_STAGE_WIDTH	(D_WIN_WIDTH * 2)		// ステージ横幅
#define D_STAGE_HEIGHT	(D_WIN_HEIGHT * 2)// ステージ縦幅

class Camera
{
private:
	Vector2D location;	// カメラ座標

public:
	Camera();
	~Camera();

public:

	void Update();
	void Draw() const;

public:
	/// <summary>
	/// ワールド座標に線を描画
	/// </summary>
	/// <param name="x1"></param>
	/// <param name="y1"></param>
	/// <param name="x2"></param>
	/// <param name="y2"></param>
	/// <param name="Color"></param>
	void DrawLineW(int x1, int y1, int x2, int y2, unsigned int Color);

	/// <summary>
	/// ワールド座標に三角形を描画
	/// </summary>
	/// <param name="x1"></param>
	/// <param name="y1"></param>
	/// <param name="x2"></param>
	/// <param name="y2"></param>
	/// <param name="x3"></param>
	/// <param name="y3"></param>
	/// <param name="Color"></param>
	void DrawTriangleW(int x1, int y1, int x2, int y2, int x3, int y3, unsigned int Color);

	/// <summary>
	/// ワールド座標で円を描画
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="r"></param>
	/// <param name="Color"></param>
	void DrawCircleW(int x, int y, int r, unsigned int Color);
};
