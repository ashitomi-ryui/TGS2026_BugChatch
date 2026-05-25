#pragma once

#include"Bug.h"
#include"../../Utilitys/Math.h"

class Grasshopper :public Bug
{
private:
	static int images[7];
	float shiita;
	float top;
	float count;
	Vector2D m_startLocation;
	bool escape;
public:
	Grasshopper();
	~Grasshopper();

public:
	static void Init();
	virtual void Update(float delta) override;
	virtual void DrawOnTheBack() const override;
	virtual void DrawOnTheFront() const;	// 前面に描画
	virtual void Draw() const override;

	//スポーン
	void Spawn();

	//リスポーン
	void ReSpawn(float delta);

	//ジャンプ位置の決定
	void SetDestination(Vector2D location);

	void EscapeSetDestination(Vector2D location);

	//アニメーション
	virtual void Animation(float delta) override;

	//逃げる処理
	void Escape(float delta);

	//待機
	void Stand(float delta);

	//
	void Move(float delta);

	//
	void Panic(float delta);

	////通常移動
	//void Patrol(float delta);

	//察知判定
	void PerceptionJudgment();

	//逃げる状態へ移行
	void TransitionToEscape();

	//前面へ移動
	void PutInFront();

};