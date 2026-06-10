#include "DxLib.h"
#include "Camera.h"
#include <cmath>
#include <string.h>
#include <string>

Vector2D Camera::m_location = { 0.0f, 0.0f };

Vector2D Camera::m_screenLocation = { D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f };
float Camera::m_screenRatioSize = 1.0f;


// ひらがな
int Camera::word1[D_WORD_KANA_SIZE] = {};

// その他
// ぁぃぅぇぉぅゃゅょ：
int Camera::word2[D_WORD_HIRAGANA_SYMBOLS_SIZE] = {};

// ひらがな
int Camera::word3[D_WORD_KANA_SIZE] = {};

// その他
// ァィゥェォッャュョー・！？
int Camera::word4[D_WORD_KATAKANA_SYMBOLS_SIZE] = {};

// 数字
int Camera::word5[D_WORD_NUMBERS_SIZE] = {};

// 漢字
// 操作説明終了網振回虫乱獲捕秒合計位匹
int Camera::word6[D_WORD_KANJI_SIZE] = {};

// 文字データ
std::vector<std::string> Camera::word1_0Data = {};
std::vector<std::string> Camera::word1_1Data = {};
std::vector<std::string> Camera::word1_2Data = {};
std::vector<std::string> Camera::word2Data = {};

std::vector<std::string> Camera::word3_0Data = {};
std::vector<std::string> Camera::word3_1Data = {};
std::vector<std::string> Camera::word4Data = {};

std::string Camera::word5_0Data = {};
std::vector<std::string> Camera::word5_1Data = {};
std::vector<std::string> Camera::word6Data = {};

// コンストラクタ
Camera::Camera()
{
}

// デストラクタ
Camera::~Camera()
{
}

void Camera::Init()
{
	LoadDivGraph("assets/images/OtherObjects/word1.png", 50, 5, 10, 30, 30, word1);
	LoadDivGraph("assets/images/OtherObjects/word2.png", 15, 5, 3, 30, 30, word2);
	LoadDivGraph("assets/images/OtherObjects/word3.png", 10, 10, 1, 30, 30, word3);
	LoadDivGraph("assets/images/OtherObjects/word4.png", 18, 6, 3, 30, 30, word4);
	LoadDivGraph("assets/images/OtherObjects/word5.png", 18, 6, 3, 30, 30, word5);
	LoadDivGraph("assets/images/OtherObjects/word6.png", 18, 6, 3, 30, 30, word6);

	word1_0Data =
	{
		"あ", "い", "う", "え", "お",
		"か", "き", "く", "け", "こ",
		"さ", "し", "す", "せ", "そ",
		"た", "ち", "つ", "て", "と",
		"な", "に", "ぬ", "ね", "の",
		"は", "ひ", "ふ", "へ", "ほ",
		"ま", "み", "む", "め", "も",
		"や", "ゆ", "よ",
		"ら", "り", "る", "れ", "ろ",
		"わ", "を", "ん",
	};
	word1_1Data =
	{
		"ぱ", "ぴ", "ぷ", "ぺ", "ぽ",
		"が", "ぎ", "ぐ", "げ", "ご",
		"ざ", "じ", "ず", "ぜ", "ぞ",
		"だ", "ぢ", "づ", "で", "ど",
		"な", "に", "ぬ", "ね", "の",
		"ば", "び", "ぶ", "べ", "ぼ",
	};
	word1_2Data =
	{
		"゛", "゜", "。", "、",
	};

	word2Data =
	{
		"ぁ", "ぃ", "ぅ", "ぇ", "ぉ",
		"っ", "ゃ", "ゅ", "ょ", "ー",
		"：",
	};

	word3_0Data =
	{
		"ア", "イ", "ウ", "エ", "オ",
		"カ", "キ", "ク", "ケ", "コ",
		"サ", "シ", "ス", "セ", "ソ",
		"タ", "チ", "ツ", "テ", "ト",
		"ナ", "ニ", "ヌ", "ネ", "ノ",
		"ハ", "ヒ", "フ", "ヘ", "ホ",
		"マ", "ミ", "ム", "メ", "モ",
		"ヤ", "ユ", "ヨ",
		"ラ", "リ", "ル", "レ", "ロ",
		"ワ", "ヲ", "ン",
	};
	word3_1Data =
	{
		"パ", "ピ", "プ", "ペ", "ポ",
		"ガ", "ギ", "グ", "ゲ", "ゴ",
		"ザ", "ジ", "ズ", "ゼ", "ゾ",
		"ダ", "ヂ", "ヅ", "デ", "ド",
		"ナ", "ニ", "ヌ", "ネ", "ノ",
		"バ", "ビ", "ブ", "ベ", "ボ",
	};

	word4Data =
	{
		"ァ", "ィ", "ゥ", "ェ", "ォ",
		"ッ", "ャ", "ュ", "ョ",
		"・", "！", "？",
	};

	word5_0Data = "0123456789";
	word5_1Data =
	{
		"０", "１", "２", "３", "４", "５", "６", "７", "８", "９",
	};

	word6Data =
	{
		"操", "作", "説", "明", "終", "了",
		"網", "振", "回", "虫", "乱", "獲",
		"捕", "秒", "合", "計", "位", "匹",
	};

	m_location = { D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f };
}

// 更新処理
void Camera::Update(Vector2D playerLocation)
{
	m_location = playerLocation;
	if (playerLocation.x < D_WIN_WIDTH / 2)
	{
		m_location.x = D_WIN_WIDTH / 2;
	}
	if (playerLocation.x > D_STAGE_WIDTH - D_WIN_WIDTH / 2)
	{
		m_location.x = D_STAGE_WIDTH - D_WIN_WIDTH / 2;
	}
	if (playerLocation.y < D_WIN_HEIGHT / 2)
	{
		m_location.y = D_WIN_HEIGHT / 2;
	}
	if (playerLocation.y > D_STAGE_HEIGHT - D_WIN_HEIGHT / 2)
	{
		m_location.y = D_STAGE_HEIGHT - D_WIN_HEIGHT / 2;
	}

}

void Camera::Draw()
{
	Vector2D location1 = FitLocationToScreen({ 0.0f, 0.0f });
	Vector2D location2 = FitLocationToScreen({ D_WIN_WIDTH, 0.0f });
	Vector2D location3 = FitLocationToScreen({ 0.0f, D_WIN_HEIGHT });
	Vector2D location4 = FitLocationToScreen({ D_WIN_WIDTH, D_WIN_HEIGHT });
	DxLib::DrawBox(D_WIN_WIDTH, 0.0f, location1.x, location1.y, 0x000000, true);
	DxLib::DrawBox(D_WIN_WIDTH, D_WIN_HEIGHT, location2.x, location2.y, 0x000000, true);
	DxLib::DrawBox(0.0f, 0.0f, location3.x, location3.y, 0x000000, true);
	DxLib::DrawBox(0.0f, D_WIN_HEIGHT, location4.x, location4.y, 0x000000, true);
}

Vector2D Camera::GetScreenLocation()
{
	return m_screenLocation;
}

float Camera::GetScreenRatioSize()
{
	return m_screenRatioSize;
}

void Camera::SetScreenLocation(Vector2D location)
{
	m_screenLocation = location;
}

void Camera::SetScreenRatioSize(float ratio)
{
	m_screenRatioSize = ratio;
}

void Camera::DrawLine(Vector2D location1, Vector2D location2, unsigned int Color, float Thinckness)
{
	location1 = FitLocationToScreen(location1);
	location2 = FitLocationToScreen(location2);
	Thinckness *= m_screenRatioSize;

	DxLib::DrawLine((int)location1.x, (int)location1.y, (int)location2.x, (int)location2.y, Color, (int)Thinckness);
}

void Camera::DrawLineW(Vector2D location1, Vector2D location2, unsigned int Color, float Thinckness)
{
	location1.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location1.y += -m_location.y + D_WIN_HEIGHT / 2.0f;
	location2.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location2.y += -m_location.y + D_WIN_HEIGHT / 2.0f;

	DrawLine(location1, location2, Color, Thinckness);
}

void Camera::DrawTriangle(Vector2D location1, Vector2D location2, Vector2D location3, unsigned int Color)
{
	location1 = FitLocationToScreen(location1);
	location2 = FitLocationToScreen(location2);
	location3 = FitLocationToScreen(location3);

	DxLib::DrawTriangle((int)location1.x, (int)location1.y, (int)location2.x, (int)location2.y, (int)location3.x, (int)location3.y, Color, true);
}

void Camera::DrawTriangleW(Vector2D location1, Vector2D location2, Vector2D location3, unsigned int Color)
{
	location1.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location1.y += -m_location.y + D_WIN_HEIGHT / 2.0f;
	location2.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location2.y += -m_location.y + D_WIN_HEIGHT / 2.0f;
	location3.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location3.y += -m_location.y + D_WIN_HEIGHT / 2.0f;

	DrawTriangle(location1, location2, location3, Color);
}

void Camera::DrawCircle(Vector2D location, float radius, unsigned int Color, bool FillFlag)
{
	location = FitLocationToScreen(location);
	radius *= m_screenRatioSize;

	DxLib::DrawCircle((int)location.x, (int)location.y, (int)radius, Color, FillFlag);
}

void Camera::DrawCircleW(Vector2D location, float radius, unsigned int Color, bool FillFlag)
{
	location.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location.y += -m_location.y + D_WIN_HEIGHT / 2.0f;

	DrawCircle(location, radius, Color, FillFlag);
}

void Camera::DrawBox(Vector2D location1, Vector2D location2, unsigned int Color)
{
	location1 = FitLocationToScreen(location1);
	location2 = FitLocationToScreen(location2);

	DxLib::DrawBox((int)location1.x, (int)location1.y, (int)location2.x, (int)location2.y, Color, true);
}

void Camera::DrawBoxW(Vector2D location1, Vector2D location2, unsigned int Color)
{
	location1.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location1.y += -m_location.y + D_WIN_HEIGHT / 2.0f;
	location2.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location2.y += -m_location.y + D_WIN_HEIGHT / 2.0f;

	DrawBoxW(location1, location2, Color);
}

void Camera::DrawGraph(Vector2D location, double ExRate, double Angle, int GrHandle, bool ReverseXFlag, bool ReverseYFlage)
{
	location = FitLocationToScreen(location);
	ExRate *= m_screenRatioSize;

	DxLib::DrawRotaGraphF(location.x, location.y, ExRate, Angle, GrHandle, true, ReverseXFlag, ReverseYFlage);
}

void Camera::DrawGraphW(Vector2D location, double ExRate, double Angle, int GrHandle, bool ReverseXFlag, bool ReverseYFlage)
{
	location.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location.y += -m_location.y + D_WIN_HEIGHT / 2.0f;

	DrawGraph(location, ExRate, Angle, GrHandle, ReverseXFlag, ReverseYFlage);
}

void Camera::DrawString(Vector2D location, int size, unsigned int Color, const TCHAR* FormatString, ...)
{
	// 変数の当てはめ
	char buffer[1024];	// 文字列
	va_list args;
	va_start(args, FormatString);
	// FormatStringを基に、続く変数をbufferに当てはめる
	vsnprintf(buffer, sizeof(buffer), FormatString, args);
	va_end(args);

	// 位置を画面に合わせる
	location = FitLocationToScreen(location);
	size *= m_screenRatioSize;

	// カラーコードをRGBに分ける
	int r = Color / 0x10000;
	Color %= 0x10000;
	int g = Color / 0x100;
	Color %= 0x100;
	int b = Color;

	// 色を変える
	SetDrawBright(r, g, b);

	float x = 0.0f;
	int y = 0;
	int len = strlen(buffer);
	bool isFound;
	for (int i = 0;i < len;i++)
	{
		isFound = false;
		if (buffer[i] == '\n')
		{
			y++;
			x = 0.0f;

			isFound = true;
		}
		if (!isFound)
		{
			for (int j = 0;j < word5_0Data.size();j++)
			{
				if (buffer[i] == word5_0Data[j])
				{
					x -= 0.2f;
					DxLib::DrawRotaGraphF(location.x + x * size, location.y + y * size, size / 25.0f, 0.0f, word3[j], true);
					x += 0.8f;

					isFound = true;
					break;
				}
			}
		}
		if (!isFound)
		{
			for(int j=0;j<word1_0Data.size();j++)
			{
				if (buffer[i] == word1_0Data[j][0] &&
					buffer[i + 1] == word1_0Data[j][1])
				{
					DxLib::DrawRotaGraphF(location.x + x * size, location.y + y * size, size / 25.0f, 0.0f, word1[j], true);
					x++;
					i++;

					isFound = true;
				}
			}
		}
		if (!isFound)
		{
			for (int j = 0;j < word1_1Data.size();j++)
			{
				if (buffer[i] == word1_1Data[j][0] &&
					buffer[i + 1] == word1_1Data[j][1])
				{
					if (j >= 5)
					{
						DxLib::DrawRotaGraphF(location.x + x * size, location.y + y * size, size / 25.0f, 0.0f, word1[j], true);
						DxLib::DrawRotaGraphF(location.x + (x + 0.8f)*size, location.y + y * size, size / 25.0f, 0.0f, word1[46], true);
					}
					else
					{
						DxLib::DrawRotaGraphF(location.x + x * size, location.y + y * size, size / 25.0f, 0.0f, word1[25 + j], true);
						DxLib::DrawRotaGraphF(location.x + (x + 0.8f)*size, location.y + y * size, size / 25.0f, 0.0f, word1[47], true);
					}
					x++;
					i++;

					isFound = true;
				}
			}
		}
		if (!isFound)
		{
			for (int j = 0;j < word1_2Data.size();j++)
			{
				if (buffer[i] == word1_2Data[j][0] &&
					buffer[i + 1] == word1_2Data[j][1])
				{
					DxLib::DrawRotaGraphF(location.x + x * size, location.y + y * size, size / 25.0f, 0.0f, word1[46 + j], true);
					x++;
					i++;

					isFound = true;
				}
			}
		}
		if (!isFound)
		{
			for (int j = 0;j < word2Data.size();j++)
			{
				if (buffer[i] == word2Data[j][0] &&
					buffer[i + 1] == word2Data[j][1])
				{
					DxLib::DrawRotaGraphF(location.x + x * size, location.y + y * size, size / 25.0f, 0.0f, word6[j], true);
					x++;
					i++;

					isFound = true;
				}
			}
		}

		if (!isFound)
		{
			for (int j = 0;j < word3_0Data.size();j++)
			{
				if (buffer[i] == word3_0Data[j][0] &&
					buffer[i + 1] == word3_0Data[j][1])
				{
					DxLib::DrawRotaGraphF(location.x + x * size, location.y + y * size, size / 25.0f, 0.0f, word5[j], true);
					x++;
					i++;

					isFound = true;
				}
			}
		}
		if (!isFound)
		{
			for (int j = 0;j < word3_1Data.size();j++)
			{
				if (buffer[i] == word3_1Data[j][0] &&
					buffer[i + 1] == word3_1Data[j][1])
				{
					if (j >= 5)
					{
						DxLib::DrawRotaGraphF(location.x + x * size, location.y + y * size, size / 25.0f, 0.0f, word5[j], true);
						DxLib::DrawRotaGraphF(location.x + (x + 0.8f) * size, location.y + y * size, size / 25.0f, 0.0f, word1[46], true);
					}
					else
					{
						DxLib::DrawRotaGraphF(location.x + x * size, location.y + y * size, size / 25.0f, 0.0f, word5[25 + j], true);
						DxLib::DrawRotaGraphF(location.x + (x + 0.8f) * size, location.y + y * size, size / 25.0f, 0.0f, word1[47], true);
					}
					x++;
					i++;

					isFound = true;
				}
			}
		}
		if (!isFound)
		{
			for (int j = 0;j < word4Data.size();j++)
			{
				if (buffer[i] == word4Data[j][0] &&
					buffer[i + 1] == word4Data[j][1])
				{
					DxLib::DrawRotaGraphF(location.x + x * size, location.y + y * size, size / 25.0f, 0.0f, word2[j], true);
					x++;
					i++;

					isFound = true;
				}
			}
		}

		if (!isFound)
		{
			for (int j = 0;j < word5_1Data.size();j++)
			{
				if (buffer[i] == word5_1Data[j][0] &&
					buffer[i + 1] == word5_1Data[j][1])
				{
					DxLib::DrawRotaGraphF(location.x + x * size, location.y + y * size, size / 25.0f, 0.0f, word3[j], true);
					x++;
					i++;

					isFound = true;
				}
			}
		}
		if (!isFound)
		{
			for (int j = 0;j < word6Data.size();j++)
			{
				if (buffer[i] == word6Data[j][0] &&
					buffer[i + 1] == word6Data[j][1])
				{
					DxLib::DrawRotaGraphF(location.x + x * size, location.y + y * size, size / 25.0f, 0.0f, word4[j], true);
					x++;
					i++;

					isFound = true;
				}
			}
		}
		if (!isFound)
		{
			x+=0.5;
		}
	}
}

void Camera::DrawStringW(Vector2D location, int size, unsigned int Color, const TCHAR * FormatString, ...)
{
	// 変数の当てはめ
	char buffer[1024];	// 文字列
	va_list args;
	va_start(args, FormatString);
	// FormatStringを基に、続く変数をbufferに当てはめる
	vsnprintf(buffer, sizeof(buffer), FormatString, args);
	va_end(args);

	location.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location.y += -m_location.y + D_WIN_HEIGHT / 2.0f;

	DrawString(location, size, Color, buffer);
}

Vector2D Camera::FitLocationToScreen(Vector2D location)
{
	location = Vec2Mult(location, m_screenRatioSize);
	location = Vec2Add(location, Vec2Mult(Vec2Mult({ D_WIN_WIDTH, D_WIN_HEIGHT }, 1.0f - m_screenRatioSize), 0.5f));
	location = Vec2Add(location, Vec2Sub(m_screenLocation, { D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f }));

	return location;
}

bool Camera::CheckItsOnTheScreen(Vector2D location, float radius)
{
	// カメラ座標に直す
	location.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location.y += -m_location.y + D_WIN_HEIGHT / 2.0f;

	if (location.x + radius < 0 ||
		location.x - radius > D_WIN_WIDTH ||
		location.y + radius < 0 ||
		location.y - radius > D_WIN_HEIGHT)
	{
		// 画面外
		return false;
	}

	// 画面内
	return true;
}
