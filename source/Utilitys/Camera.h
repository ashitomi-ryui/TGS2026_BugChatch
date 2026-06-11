#pragma once
#include "Math.h"
#include <DxLib.h>
#include <string>
#include <vector>

//==========================================================
// マクロ定義
//==========================================================

#define D_WIN_WIDTH		(1280.0f)	// スクリーンの横幅
#define D_WIN_HEIGHT	(720.0f)	// スクリーンの縦幅

#define D_STAGE_WIDTH	(D_WIN_WIDTH * 2.5f)	// ステージ横幅
#define D_STAGE_HEIGHT	(D_WIN_HEIGHT * 2.5f)	// ステージ縦幅

#define D_OBJECT_SIZE_RATIO	(2.0f / 3.0f)	// オブジェクトや移動などのサイズ比率

#define D_WORD_KANA_SIZE	(50)
#define D_WORD_HIRAGANA_SYMBOLS_SIZE	(10)
#define D_WORD_KATAKANA_SYMBOLS_SIZE	(15)
#define D_WORD_NUMBERS_SIZE		(10)
#define D_WORD_KANJI_SIZE		(18)

class Camera
{
private:
	static Vector2D m_location;	// カメラ座標

	static Vector2D m_screenLocation;	// 画面の位置
	static float m_screenRatioSize;		// 画面の比率

	static int word1[D_WORD_KANA_SIZE];	// ひらがな
	static int word2[D_WORD_HIRAGANA_SYMBOLS_SIZE];	// ひらがなとその他
	static int word3[D_WORD_KANA_SIZE];	// カタカナ
	static int word4[D_WORD_KATAKANA_SYMBOLS_SIZE];	// カタカナとその他
	static int word5[D_WORD_NUMBERS_SIZE];	// 数字
	static int word6[D_WORD_KANJI_SIZE];	// 漢字

	static std::vector<std::string> word1_0Data;
	static std::vector<std::string> word1_1Data;
	static std::vector<std::string> word1_2Data;
	static std::vector<std::string> word2Data;

	static std::vector<std::string> word3_0Data;
	static std::vector<std::string> word3_1Data;
	static std::vector<std::string> word4Data;

	static std::string word5_0Data;
	static std::vector<std::string> word5_1Data;
	static std::vector<std::string> word6Data;
	
public:
	Camera();
	~Camera();

public:
	static void Init();
	static void Update(Vector2D playerLocation);
	static void Draw();

public:
	/// <summary>
	/// 画面の位置を取得
	/// </summary>
	/// <returns>座標</returns>
	static Vector2D GetScreenLocation();
	/// <summary>
	/// 画面の比率を取得
	/// </summary>
	/// <returns>比率</returns>
	static float GetScreenRatioSize();
	/// <summary>
	/// 画面の位置を設定（初期値　{ D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f }）
	/// </summary>
	/// <param name="location">座標</param>
	static void SetScreenLocation(Vector2D location);
	/// <summary>
	/// 画面の比率を設定（初期値　1.0f）
	/// </summary>
	/// <param name="ratio">比率</param>
	static void SetScreenRatioSize(float ratio);

public:

	/// <summary>
	/// 線を描画
	/// </summary>
	/// <param name="location1">座標1</param>
	/// <param name="location2">座標2</param>
	/// <param name="Color">色</param>
	/// <param name="Thinckness">太さ</param>
	static void DrawLine(Vector2D location1, Vector2D location2, unsigned int Color, float Thinckness = 1.0f);

	/// <summary>
	/// ワールド座標に線を描画
	/// </summary>
	/// <param name="location1">座標1</param>
	/// <param name="location2">座標2</param>
	/// <param name="Color">色</param>
	/// <param name="Thinckness">太さ</param>
	static void DrawLineW(Vector2D location1, Vector2D location2, unsigned int Color, float Thinckness = 1.0f);

	/// <summary>
	/// 三角形を描画
	/// </summary>
	/// <param name="location1">座標1</param>
	/// <param name="location2">座標2</param>
	/// <param name="location3">座標3</param>
	/// <param name="Color">色</param>
	static void DrawTriangle(Vector2D location1, Vector2D location2, Vector2D location3, unsigned int Color);

	/// <summary>
	/// ワールド座標に三角形を描画
	/// </summary>
	/// <param name="location1">座標1</param>
	/// <param name="location2">座標2</param>
	/// <param name="location3">座標3</param>
	/// <param name="Color">色</param>
	static void DrawTriangleW(Vector2D location1, Vector2D location2, Vector2D location3, unsigned int Color);

	/// <summary>
	/// 円を描画
	/// </summary>
	/// <param name="location">座標</param>
	/// <param name="radius">半径</param>
	/// <param name="Color">色</param>
	static void DrawCircle(Vector2D location, float radius, unsigned int Color, bool FillFlag = true);

	/// <summary>
	/// ワールド座標で円を描画
	/// </summary>
	/// <param name="location">座標</param>
	/// <param name="radius">半径</param>
	/// <param name="Color">色</param>
	static void DrawCircleW(Vector2D location, float radius, unsigned int Color, bool FillFlag = true);

	/// <summary>
	/// 四角を描画
	/// </summary>
	/// <param name="location1">座標1</param>
	/// <param name="location2">座標2</param>
	/// <param name="Color">色</param>
	static void DrawBox(Vector2D location1, Vector2D location2, unsigned int Color);

	/// <summary>
	/// ワールド座標で四角を描画
	/// </summary>
	/// <param name="location1">座標1</param>
	/// <param name="location2">座標2</param>
	/// <param name="Color">色</param>
	static void DrawBoxW(Vector2D location1, Vector2D location2, unsigned int Color);

	/// <summary>
	/// 画像を描画
	/// </summary>
	/// <param name="location">座標</param>
	/// <param name="ExRote">比率</param>
	/// <param name="Angle">向き</param>
	/// <param name="GrHandle">画像情報</param>
	/// <param name="ReverseXFlag">横反転</param>
	/// <param name="ReverseYFlage">縦反転</param>
	static void DrawGraph(Vector2D location, double ExRateX, double ExRateY, double Angle, int GrHandle, bool ReverseXFlag = false, bool ReverseYFlag = false);

	/// <summary>
	/// ワールド座標で画像を描画
	/// </summary>
	/// <param name="location">座標</param>
	/// <param name="ExRote">比率</param>
	/// <param name="Angle">向き</param>
	/// <param name="GrHandle">画像情報</param>
	/// <param name="ReverseXFlag">横反転</param>
	/// <param name="ReverseYFlage">縦反転</param>
	static void DrawGraphW(Vector2D location, double ExRateX, double ExRateY, double Angle, int GrHandle, bool ReverseXFlag = false, bool ReverseYFlag = false);

	/// <summary>
	/// 文章を描画
	/// </summary>
	/// <param name="location">座標</param>
	/// <param name="size">大きさ</param>
	/// <param name="Color">色</param>
	/// <param name="FormatString">文字情報</param>
	/// <param name=""></param>
	static void DrawString(Vector2D location, int size, unsigned int Color, const TCHAR* FormatString, ...);

	/// <summary>
	/// ワールド座標で文章を描画
	/// </summary>
	/// <param name="location">座標</param>
	/// <param name="size">大きさ</param>
	/// <param name="Color">色</param>
	/// <param name="FormatString">文字情報</param>
	/// <param name=""></param>
	static void DrawStringW(Vector2D location, int size, unsigned int Color, const TCHAR *FormatString, ...);

	/// <summary>
	/// 画面の比率に合わせて位置を調整する
	/// </summary>
	/// <param name="location">位置</param>
	/// <returns>比率に合わせた位置</returns>
	static Vector2D FitLocationToScreen(Vector2D location);

	/// <summary>
	/// 画面内か調べる
	/// </summary>
	/// <param name="location">調べたい座標</param>
	/// <param name="radius">調べたい物の半径</param>
	/// <returns>画面内ならtrue</returns>
	static bool CheckItsOnTheScreen(Vector2D location, float radius = 0.0f);
};
