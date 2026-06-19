#include "DxLib.h"

#include "Bug.h"

#include "../../Utilitys/Camera.h"
#include "../../Utilitys/Random.h"


Player* Bug::targetPlayer;

int Bug::cicadaGetCount = 0;
int Bug::dragonflyGetCount = 0;
int Bug::grasshopperGetCount = 0;
int Bug::HitSE = -1;

Bug::Bug()
{
	// 画像情報の格納例
	// 変数名 = LoadGraph(ファイル名);
	// エラー情報 = LoadDivGraph(ファイル名, 合計分割数, 横分割数, 縦分割数, Xサイズ, Yサイズ, 変数名);
	// エラーなら-1


	m_isAppearance = false;
	m_isEscape = false;
	m_state = eStand;
	m_isBack = false;
	m_location = { 0.0f, 0.0f };
	m_radius = 0.0f;
	m_direction = 0.0f;
	m_Angle = 0.0f;
	m_moveSpeed = { 0.0f, 0.0f };
	m_destination = { 0.0f, 0.0f };
	m_height = 0.0f;
	m_detectionRange = 0.0f;
	m_detectionTime = 0.0f;
	m_transitionTime = 0.0f;
	m_animTime = 0.0f;
	m_animCount = 0;
	
}
Bug::~Bug()
{
}

void Bug::Init()
{
	ChangeVolumeSoundMem(1500, HitSE);
	HitSE = LoadSoundMem("assets/Audio/HitSE.wav");
}

void Bug::Set(Vector2D location)
{
	// 出現している
	m_isAppearance = true;
	// 逃げていない
	m_isEscape = false;
	// 待機
	m_state = eStand;
	// 背面に描画するか
	m_isBack = false;
	// 座標
	m_location = location;
	// 半径
	m_radius = 13.0f;
	// 移動方向
	m_direction = 0.0f;
	// 画像の向き
	m_Angle = 0.0f;
	// 動き
	m_moveSpeed = { 0.0f, 0.0f };
	// 目的地
	m_destination = { 0.0f, 0.0f };
	// 察知時間
	m_detectionTime = 0.0f;
	// 遷移時間を0.1fごとに区切った0.0f~10.0fにする
	m_transitionTime = Random::GetRand(10.0f, 0.1f);
	// アニメーション
	m_animTime = 0.0f;
	m_animCount = 0;
}

void Bug::Update(int id, float delta)
{
	// 移動
	m_location = Vec2Add(m_location, Vec2Mult(m_moveSpeed, delta));
}

void Bug::Draw() const
{
}

void Bug::DrawOnTheBack() const
{
	// 出現しているかつ、背面なら
	if (m_isAppearance && m_isBack)
	{
		Draw();
	}
}

void Bug::DrawOnTheFront() const
{
	// 出現しているかつ、背面ではないならなら
	if (m_isAppearance && !m_isBack)
	{
		Draw();
	}
}

void Bug::SetPlayer(Player* p)
{
	targetPlayer = p;
}

void Bug::Acceleration(float acceleration, float maxSpeed, float direction, float delta)
{
	m_moveSpeed.x += sinf(direction) * acceleration * delta;
	m_moveSpeed.y -= cosf(direction) * acceleration * delta;

	if (Length(m_moveSpeed) > maxSpeed)
	{
		float moveDirection = VecATan2({ 0.0f, 0.0f }, m_moveSpeed);
		m_moveSpeed.x = sinf(moveDirection) * maxSpeed;
		m_moveSpeed.y = -cosf(moveDirection) * maxSpeed;
	}
}

void Bug::Deceleration(float deceleration, float delta)
{
	// 減速
	// X座標を減速する
	if (m_moveSpeed.x > deceleration * delta)
	{
		m_moveSpeed.x -= deceleration * delta;
	}
	else if (m_moveSpeed.x < -deceleration * delta)
	{
		m_moveSpeed.x += deceleration * delta;
	}
	else
	{
		m_moveSpeed.x = 0.0f;
	}
	// Y座標を減速する
	if (m_moveSpeed.y > deceleration * delta)
	{
		m_moveSpeed.y -= deceleration * delta;
	}
	else if (m_moveSpeed.y < -deceleration * delta)
	{
		m_moveSpeed.y += deceleration * delta;
	}
	else
	{
		m_moveSpeed.y = 0.0f;
	}
}

void Bug::Animation(float delta)
{
	m_detectionTime -= delta;
	m_transitionTime -= delta;
	m_animTime += delta;
}

Vector2D Bug::GetLocation() const
{
	return m_location;
}

float Bug::GetRadius() const
{
	return m_radius;
}

float Bug::GetHeight() const
{
	return m_height;
}

bool Bug::GetIsAppearance() const
{
	return m_isAppearance;
}

bool Bug::GetIsBack() const
{
	return m_isBack;
}

int Bug::GetCicadaCount()
{
	return cicadaGetCount;
}

int Bug::GetDragonflyCount()
{
	return dragonflyGetCount;
}

int Bug::GetGrasshopperCount()
{
	return grasshopperGetCount;
}
