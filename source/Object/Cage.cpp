#include "Cage.h"

#include <DxLib.h>
#include "Bug/Bug.h"
#include "Player.h"
#include "../Utilitys/Camera.h"
#include "../Utilitys/Random.h"
#include "../Scene/SceneType.h"
#include "../Scene/ResultScene.h"

Player* Cage::targetPlayer;
int Cage::oldCicada = 0;
int Cage::oldDragonfly = 0;
int Cage::oldGrasshopper = 0;
Vector2D Cage::location = {};

int Cage::bugId = 0;
bool Cage::isRemovedAll = false;

float Cage::time = 0.0f;
float Cage::animTime = 0.0f;
int Cage::animCount = 6;

int Cage::cicadaImage = -1;
int Cage::dragonflyImage[2] = {};
int Cage::grasshopperImage[4] = {};
int Cage::cageImage[2][4] = {};

Cage bug[D_CAGE_MAX];	// かご内の虫

Cage::Cage()
{
	m_type = eCicada;
	m_display = false;
	m_location = {};
	m_moveSpeed = {};
	m_angle = 0.0f;
	m_theta = 0.0f;

	m_state = eJoin;

	m_time = 0.0f;
	m_animTime = 0.0f;
	m_animCount = 0;
}

Cage::~Cage()
{
}

void Cage::Init(eSceneType sceneType)
{
	time = 0.0f;
	animTime = 0.0f;

	switch(sceneType)
	{
	case eInGame:

		oldCicada = 0;
		oldDragonfly = 0;
		oldGrasshopper = 0;

		location = { 80.0f * D_CAGE_RATIO, 80.0f * D_CAGE_RATIO };

		animCount = 6;

		cicadaImage = LoadGraph("assets/images/Bugs/Cicada/Cicada.PNG");

		dragonflyImage[0] = LoadGraph("assets/images/Bugs/Dragonfly/Dragonfly1.PNG");
		dragonflyImage[1] = LoadGraph("assets/images/Bugs/Dragonfly/Dragonfly2.PNG");

		grasshopperImage[0] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper1.PNG");
		grasshopperImage[1] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper2.PNG");
		grasshopperImage[2] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper3.PNG");
		grasshopperImage[3] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper4.PNG");

		cageImage[0][0] = LoadGraph("assets/images/OtherObjects/Cage/Cage1.PNG");
		cageImage[0][1] = LoadGraph("assets/images/OtherObjects/Cage/Cage2.PNG");
		cageImage[0][2] = LoadGraph("assets/images/OtherObjects/Cage/Cage3.PNG");
		cageImage[0][3] = LoadGraph("assets/images/OtherObjects/Cage/Cage4.PNG");

		cageImage[1][0] = LoadGraph("assets/images/OtherObjects/Cage/Cage5.PNG");
		cageImage[1][1] = LoadGraph("assets/images/OtherObjects/Cage/Cage6.PNG");
		cageImage[1][2] = LoadGraph("assets/images/OtherObjects/Cage/Cage7.PNG");
		cageImage[1][3] = LoadGraph("assets/images/OtherObjects/Cage/Cage8.PNG");

		break;
	case eResult:

		animCount = 0;

		location = { D_WIN_WIDTH / 2.0f, 600.0f };

		// 最後に入った虫のIDから始める
		for (int id = D_CAGE_MAX - 1;id >= 0;id--)
		{
			if (bug[id].GetDisplay())
			{
				bugId = id;
				break;
			}
		}

		isRemovedAll = false;

		break;
	}

	for (int id = 0;id < D_CAGE_MAX;id++)
	{
		bug[id].BugInit(sceneType);	// かご内の虫の初期化
	}
}

void Cage::Update(eSceneType sceneType, float delta)
{
	switch (sceneType)
	{
	case eInGame:

		animTime += delta;
		if (animCount == 2)
		{
			if (animTime >= 1.0f)
			{
				animCount++;
				animTime = 0.0f;
			}
		}
		else
		{
			if (animTime >= 0.25f)
			{
				animCount++;
				animTime = 0.0f;
			}
		}
		
		{
			int cicadaCount = Bug::GetCicadaCount();
			int dragonflyCount = Bug::GetDragonflyCount();
			int grasshopperCount = Bug::GetGrasshopperCount();

			// セミの数が前のセミの数より大きいなら
			if (cicadaCount > oldCicada)
			{
				// このフレームで捕ったセミの数繰り返す
				for (int i = 0;i < cicadaCount - oldCicada;i++)
				{
					// 虫の最大数繰り返す
					for (int j = 0;j < D_CAGE_MAX;j++)
					{
						// 非表示なら
						if (!bug[j].GetDisplay())
						{
							// セミを追加
							bug[j].Add(eCicada);
							break;
						}
					}
				}
			}
			// トンボの数が前のトンボの数より大きいなら
			if (dragonflyCount > oldDragonfly)
			{
				// このフレームで捕ったトンボの数繰り返す
				for (int i = 0;i < dragonflyCount - oldDragonfly;i++)
				{
					// 虫の最大数繰り返す
					for (int j = 0;j < D_CAGE_MAX;j++)
					{
						// 非表示なら
						if (!bug[j].GetDisplay())
						{
							// トンボを追加
							bug[j].Add(eDragonfly);
							break;
						}
					}
				}
			}
			// バッタの数が前のバッタの数より大きいなら
			if (grasshopperCount > oldGrasshopper)
			{
				// このフレームで捕ったバッタの数繰り返す
				for (int i = 0;i < grasshopperCount - oldGrasshopper;i++)
				{
					// 虫の最大数繰り返す
					for (int j = 0;j < D_CAGE_MAX;j++)
					{
						// 非表示なら
						if (!bug[j].GetDisplay())
						{
							// バッタを追加
							bug[j].Add(eGrasshopper);
							break;
						}
					}
				}
			}

			for (int id = 0;id < D_CAGE_MAX;id++)
			{
				bug[id].BugUpdate(sceneType, delta);	// かご内の虫の更新
			}

			// 前の数を今の数にする
			oldCicada = cicadaCount;
			oldDragonfly = dragonflyCount;
			oldGrasshopper = grasshopperCount;
		}

		break;
	case eResult:

		// アニメーションカウントが4より少ないとき
		if (animCount < 3)
		{
			animTime += delta;
			if (animTime >= 0.25f)
			{
				animCount++;
				animTime = 0.0f;
			}
		}
		// アニメーションカウントが4以上のとき
		else
		{
			time += delta;
			// 虫のIDの始まりが0より大きいとき
			if (bugId > 0)
			{
				if (time >= 0.1f)
				{
					bugId--;
					time = 0.0f;
				}
			}
			// 虫のIDの始まりが0のとき
			else
			{
				location.y += 300.0f * delta;
				if (location.y >= D_WIN_HEIGHT + 300.0f)
				{
					// 全て出した
					isRemovedAll = true;
				}
			}

			for (int id = bugId;id < D_CAGE_MAX;id++)
			{
				bug[id].BugUpdate(sceneType, delta);	// かご内の虫の更新
			}
		}

		// Aボタンを押したら
		if (GetButtonState(XINPUT_BUTTON_A) == ePressed)
		{
			// 全て出した
			isRemovedAll = true;
		}

		break;
	}
}

void Cage::Draw(eSceneType sceneType, unsigned int color)
{
	switch (sceneType)
	{
	case eInGame:

	{
		int num = 0;	// 画像番号

		// 空けて閉じるアニメーション
		switch (animCount)
		{
		case 0:
		case 4:
			num = 1;
			break;
		case 1:
		case 3:
			num = 2;
			break;
		case 2:
			num = 3;
			break;
		default:
			num = 0;
			break;
		}

		// かごを表示
		Camera::DrawGraph(location, 3.0f * D_CAGE_RATIO, 3.0f * D_CAGE_RATIO, 0.0f, cageImage[0][num], false, false, color);

		for (int id = 0;id < D_CAGE_MAX;id++)
		{
			bug[id].BugDraw(sceneType, color);	// かご内の虫の描画
		}
	}

	break;
	case eResult:

		// かごを表示
		Camera::DrawGraph(location, 4.5f, 4.5f, 0.0f, cageImage[0][animCount]);

		for (int id = 0;id < D_CAGE_MAX;id++)
		{
			bug[id].BugDraw(sceneType);	// かご内の虫の描画
		}

		// かごの外装を表示
		Camera::DrawGraph(location, 4.5f, 4.5f, 0.0f, cageImage[1][animCount]);

		break;
	}

}

void Cage::BugInit(eSceneType sceneType)
{
	m_moveSpeed = {};

	m_time = 0.0f;
	m_animTime = 0.0f;
	m_animCount = 0;

	switch (sceneType)
	{
	case eInGame:

		m_display = false;
		m_location = { Random::GetRand(-15.0f, 15.0f), -100.0f * D_CAGE_RATIO };
		m_angle = 1.0f * DX_PI_F;

		m_state = eJoin;

		break;
	case eResult:

		m_location = location;
		m_angle = 0.0f;
		m_theta = 0.0f;

		break;
	}
}

void Cage::BugUpdate(eSceneType sceneType, float delta)
{
	if (m_display)
	{
		switch (sceneType)
		{
		case eInGame:

			m_time -= delta;
			m_animTime += delta;

			// 状態によって処理を変える
			switch (m_state)
			{
			case eJoin:
				Join(delta);
				break;
			case eStand:
				Stand(delta);
				break;
			case eMove:
				Move(delta);
				break;
			}

			// 移動
			m_location = Vec2Add(m_location, Vec2Mult(m_moveSpeed, delta));

			// 移動制限
			if (m_location.x < -D_CAGE_WIDTH)
			{
				m_location.x = -D_CAGE_WIDTH;
				m_moveSpeed.x = 0.0f;
			}
			else if (m_location.x > D_CAGE_WIDTH)
			{
				m_location.x = D_CAGE_WIDTH;
				m_moveSpeed.x = 0.0f;
			}
			if (m_location.y < -D_CAGE_HEIGHT && m_state != eJoin)
			{
				m_location.y = -D_CAGE_HEIGHT;
				m_moveSpeed.y = 0.0f;
			}
			else if (m_location.y > D_CAGE_HEIGHT)
			{
				m_location.y = D_CAGE_HEIGHT;
				m_moveSpeed.y = 0.0f;
			}

			break;
		case eResult:

			m_theta += 1.0f * delta;
			if (m_theta > 1.0f || isRemovedAll)
			{
				// ポイントを追加
				Result::AddPoint(m_type);
				// 非表示
				m_display = false;

				break;
			}

			Vector2D start = { D_WIN_WIDTH / 2.0f, 600.0f };
			Vector2D goal;
			float s = 0.0f;
			switch (m_type)
			{
			case eCicada:
				s = 0.0f;
				break;
			case eDragonfly:
				s = 1.0f;
				break;
			case eGrasshopper:
				s = 2.0f;
				break;
			}
			goal = { 200.0f + (s * 320.0f) , 150.0f };

			float top = 100.0f;
			float height = sinf(m_theta * DX_PI_F) * top;
			// 移動処理
			m_location.x = start.x + (goal.x - start.x) * m_theta;
			m_location.y = start.y + (goal.y - start.y) * m_theta - height;

			break;
		}
	}
}

void Cage::BugDraw(eSceneType sceneType, unsigned int color) const
{
	if (m_display)
	{
		switch (sceneType)
		{
		case eInGame:

		{
			// 座標をかごに合わせる
			Vector2D loc = {};
			loc.x = location.x + m_location.x;
			loc.y = location.y + m_location.y;
			float angle = m_angle;

			switch (m_type)
			{
			case eCicada:
				// セミを表示
				Camera::DrawGraph(loc, 2.0f * D_CAGE_RATIO, 2.0f * D_CAGE_RATIO, angle, cicadaImage, false, false, color);
				break;
			case eDragonfly:
				// トンボを表示
				angle += 0.70f * DX_PI_F;
				Camera::DrawGraph(loc, 2.0f * D_CAGE_RATIO, 2.0f * D_CAGE_RATIO, angle, dragonflyImage[m_animCount], false, false, color);
				break;
			case eGrasshopper:
				// バッタを表示
				angle += 0.6f * DX_PI_F;
				Camera::DrawGraph(loc, 2.0f * D_CAGE_RATIO, 2.0f * D_CAGE_RATIO, angle, grasshopperImage[m_animCount], false, false, color);
				break;
			}
		}

			break;
		case eResult:

			switch (m_type)
			{
			case eCicada:
				// セミを表示
				Camera::DrawGraph(m_location, 3.0f, 3.0f, 0.0f, cicadaImage);
				break;
			case eDragonfly:
				// トンボを表示
				Camera::DrawGraph(m_location, 3.0f, 3.0f, 0.0f, dragonflyImage[0]);
				break;
			case eGrasshopper:
				// バッタを表示
				Camera::DrawGraph(m_location, 3.0f, 3.0f, 0.0f, grasshopperImage[0]);
				break;
			}

			break;
		}
	}
}

void Cage::Add(Type type)
{
	m_type = type;
	m_display = true;

	// かごを開ける
	animTime = 0.0f;
	switch (animCount)
	{
	case 1:
	case 3:
		animCount = 1;
		break;
	case 2:
		animCount = 2;
		break;
	default:
		animCount = 0;
		break;
	}
}

void Cage::Join(float delta)
{
	switch (m_type)
	{
	case eDragonfly:
		m_animCount = 1;
		break;
	case eGrasshopper:
		m_animCount = 0;
		break;
	}

	// 落とす
	m_moveSpeed.y += 100.0f * delta * D_CAGE_RATIO;

	// 速度制限
	int len = Length(m_moveSpeed);
	if (len > 100.0f * D_CAGE_RATIO)
	{
		len -= 100.0f * D_CAGE_RATIO;
		float shiita = VecATan2(m_moveSpeed, { 0.0f, 0.0f });
		m_moveSpeed.x += sinf(shiita) * len;
		m_moveSpeed.y -= cosf(shiita) * len;
	}

	// 底についたら
	if (m_location.y + m_moveSpeed.y * delta >= D_CAGE_HEIGHT)
	{
		// 状態を待機にする
		m_state = eStand;
		// 遷移時間を0にする
		m_time = 0.0f;
	}
}

void Cage::Stand(float delta)
{
	switch (m_type)
	{
	case eDragonfly:
		m_animCount = 1;
		break;
	case eGrasshopper:
		m_animCount = 0;
		break;
	}

	// 遷移時間が0以下なら
	if (m_time <= 0.0f)
	{
		// 向きをランダムにする
		m_angle = Random::GetRand(0.0f, 2.0f, 0.125f) * DX_PI_F;

		// 状態を動くにする
		m_state = eMove;
		// 遷移する時間を0～5秒のランダムにする
		m_time = Random::GetRand(0.0f, 5.0f, 0.1f);
	}
}

void Cage::Move(float delta)
{
	// アニメーション
	switch (m_type)
	{
	case eDragonfly:
		if (m_animTime >= 0.5f)
		{
			m_animCount = (m_animCount + 1) % 2;
			m_animTime = 0.0f;
		}
		break;
	case eGrasshopper:
		if (m_animTime >= 0.25f)
		{
			m_animCount = (m_animCount + 1) % 4;
			m_animTime = 0.0f;
		}
		break;
	}

	if (m_time <= 0.0f)
	{
		// 状態を待機にする
		m_state = eStand;
		// 遷移する時間を1～10秒のランダムにする
		m_time = Random::GetRand(1.0f, 10.0f, 0.1f);
	}

	// 向きに合わせて移動する
	m_moveSpeed.x += sinf(m_angle) * 100.0f * D_CAGE_RATIO;
	m_moveSpeed.y -= cosf(m_angle) * 100.0f * D_CAGE_RATIO;

	// 速度制限
	int len = Length(m_moveSpeed);
	if (len > 10.0f * D_CAGE_RATIO)
	{
		len -= 10.0f * D_CAGE_RATIO;
		float shiita = VecATan2(m_moveSpeed, { 0.0f, 0.0f });
		m_moveSpeed.x += sinf(shiita) * len;
		m_moveSpeed.y -= cosf(shiita) * len;
	}
}

bool Cage::GetDisplay() const
{
	return m_display;
}

bool Cage::GetRemovedAll()
{
	return isRemovedAll;
}
