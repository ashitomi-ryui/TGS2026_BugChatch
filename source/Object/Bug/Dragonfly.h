#pragma once
#include "math.h"
#include "Bug.h"

#include "../../Utilitys/Math.h"

class Dragonfly : public Bug
{
private:
	Vector2D m_destinations[5] = {};	// 目的地（5つ）
	int m_destinationSub;	// 目的地の添え字
	int m_destinationNum;	// 目的地の数

	bool m_isHovering;	// ホバリングしているかどうか
	int m_hoveringCount;	// ホバリング回数
	bool m_isFlapping;		// 羽ばたき

	float shiita;  // ホバリングがどれぐらい完了しているか
	float bottom;     // ホバリング時の底辺
	Vector2D m_startLocation;   // ホバリング開始地点

	bool m_isBreak;	// 休憩

	static int images[4];	// 画像情報
	bool m_isFlip;			// 反転
public:
	Dragonfly();
	~Dragonfly();

public:
	static void Init();
	virtual void Update(float delta) override;
	virtual void Draw() const override;
	virtual void DrawOnTheBack() const override;
	virtual void DrawOnTheFront() const override;

	/// <summary>
	/// 出現
	/// </summary>
	void Spawn();

	/// <summary>
	/// 再出現
	/// </summary>
	void ReSpawn(float delta);

	/// <summary>
	/// 目的地の設定
	/// </summary>
	void SetDestination();


	/// <summary>
	/// アニメーション
	/// </summary>
	/// <param name="delta"></param>
	virtual void Animation(float delta) override;

	/// <summary>
	/// 逃げる処理
	/// </summary>
	void Escape(float delta);

	/// <summary>
	/// 待機
	/// </summary>
	/// <param name="delta"></param>
	void Stand(float delta);

	/// <summary>
	/// 移動
	/// </summary>
	void Move(float delta);

	/// <summary>
	/// パニック
	/// </summary>
	/// <param name="delta"></param>
	void Panic(float delta);

	/// <summary>
	/// ホバリング
	/// </summary>
	/// <param name="delta"></param>
	void Hovering(float delta);

	/// <summary>
	/// 休憩に向かう
	/// </summary>
	/// <param name="delta"></param>
	void HeadingForABreak(float delta);

	/// <summary>
	/// 察知判定
	/// </summary>
	/// <param name="delta"></param>
	void PerceptionJudgment();

	/// <summary>
	/// 逃げ状態への遷移
	/// </summary>
	void TransitionToEscape();

	/// <summary>
	/// 前面に置く
	/// </summary>
	void PutInFront();
};
