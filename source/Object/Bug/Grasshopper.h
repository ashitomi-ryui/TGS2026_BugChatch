#pragma once

#include"Bug.h"
#include"../../Utilitys/Math.h"

class Grasshopper :public Bug
{
private:
	static int images[7];
	static int Audio[2];

	bool m_isWallHit;
	bool m_isTurn;
	bool m_isJump;	// ジャンプするか
	float shiita;  //ジャンプがどれぐらい完了しているかのやつ
	float top;     //ジャンプ時の頂点
	Vector2D m_startLocation;   //ジャンプ開始地点
	bool escape;   //逃げフラグ
	bool jougai;   //画面外にでたか
	Vector2D nearleaf;  //一番近くの草
	bool isRouteBlock;// ルート上に木があるかどうかのフラグ


public:
	Grasshopper();
	~Grasshopper();

public:
	static void Init();
	virtual void Update(int id, float delta) override;
	virtual void DrawOnTheBack() const override;
	virtual void DrawOnTheFront() const;	// 前面に描画
	virtual void Draw() const override;


	static void StopAudio();

	//スポーン
	void Spawn();

	//リスポーン
	void ReSpawn(float delta);

	//ジャンプ位置の決定
	void SetDestination(Vector2D location);

	void EscapeSetDestination(Vector2D location,Vector2D Plocation);

	//アニメーション
	virtual void Animation(float delta) override;

	//逃げる処理
	void Escape(float delta);

	//待機
	void Stand(float delta);

	//
	void Move(float delta);

	//木の衝突判定
	bool CheckTreeCollision(Vector2D current_loc);

	//察知判定
	void PerceptionJudgment();

	//逃げる状態へ移行
	void TransitionToEscape();

	//前面へ移動
	void PutInFront();

	void CheckOverlap();

};