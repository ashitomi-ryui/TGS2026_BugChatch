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
	static Vector2D m_location;	// カメラ座標

public:
	Camera(Vector2D location);
	~Camera();

public:

	void Update(Vector2D playerLocation);
	void Draw() const;

public:
	
	/// <summary>
	/// ワールド座標に線を描画
	/// </summary>
	/// <param name="location1"></param>
	/// <param name="location2"></param>
	/// <param name="Color"></param>
	static void DrawLineW(Vector2D location1, Vector2D location2, unsigned int Color, int Thinckness);
	
	/// <summary>
	/// ワールド座標に三角形を描画
	/// </summary>
	/// <param name="location1"></param>
	/// <param name="location2"></param>
	/// <param name="location3"></param>
	/// <param name="Color"></param>
	static void DrawTriangleW(Vector2D location1, Vector2D location2, Vector2D location3, unsigned int Color);
	
	/// <summary>
	/// ワールド座標で円を描画
	/// </summary>
	/// <param name="location"></param>
	/// <param name="r"></param>
	/// <param name="Color"></param>
	static void DrawCircleW(Vector2D location, int r, unsigned int Color);
};
