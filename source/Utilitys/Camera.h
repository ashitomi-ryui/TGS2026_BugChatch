#pragma once
#include "Math.h"

//==========================================================
// マクロ定義
//==========================================================

#define D_WIN_WIDTH		(1280.0f)	// スクリーンの横幅
#define D_WIN_HEIGHT	(720.0f)	// スクリーンの縦幅

#define D_STAGE_WIDTH	(D_WIN_WIDTH * 2.0f)		// ステージ横幅
#define D_STAGE_HEIGHT	(D_WIN_HEIGHT * 2.0f)// ステージ縦幅

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
	/// <param name="location1">座標1</param>
	/// <param name="location2">座標2</param>
	/// <param name="Color">色</param>
	/// <param name="Thinckness">太さ</param>
	static void DrawLineW(Vector2D location1, Vector2D location2, unsigned int Color, int Thinckness = 1);
	
	/// <summary>
	/// ワールド座標に三角形を描画
	/// </summary>
	/// <param name="location1">座標1</param>
	/// <param name="location2">座標2</param>
	/// <param name="location3">座標3</param>
	/// <param name="Color">色</param>
	static void DrawTriangleW(Vector2D location1, Vector2D location2, Vector2D location3, unsigned int Color);
	
	/// <summary>
	/// ワールド座標で円を描画
	/// </summary>
	/// <param name="location">座標</param>
	/// <param name="radius">半径</param>
	/// <param name="Color">色</param>
	static void DrawCircleW(Vector2D location, float radius, unsigned int Color, bool FillFlag = true);

	/// <summary>
	/// ワールド座標で四角を描画
	/// </summary>
	/// <param name="location1">座標1</param>
	/// <param name="location2">座標2</param>
	/// <param name="Color">色</param>
	static void DrawBoxW(Vector2D location1, Vector2D location2, unsigned int Color);

	/// <summary>
	/// ワールド座標で画像を描画
	/// </summary>
	/// <param name="location">座標</param>
	/// <param name="ExRote">比率</param>
	/// <param name="Angle">向き</param>
	/// <param name="GrHandle">画像情報</param>
	/// <param name="ReverseXFlag">横反転</param>
	/// <param name="ReverseYFlage">縦反転</param>
	static void DrawGraphW(Vector2D location, double ExRate, double Angle, int GrHandle, bool ReverseXFlag = false, bool ReverseYFlage = false);

	/// <summary>
	/// 画面内か調べる
	/// </summary>
	/// <param name="location">調べたい座標</param>
	/// <param name="radius">調べたい物の半径</param>
	/// <returns>画面内ならtrue</returns>
	static bool CheckItsOnTheScreen(Vector2D location, float radius = 0.0f);
};
