#pragma once

#include "Bug.h"

#include "../../Utilitys/Math.h"

class Cicada : public Bug
{
private:
	static int images[5];
	static int CicadaSE;
	

public:
	static bool isWithinTheScreen;

public:
	Cicada();
	~Cicada();
	
public:
	static void Init();
	virtual void Update(int id, float delta) override;
	virtual void Draw() const override;
	virtual void DrawOnTheBack() const override;
	virtual void DrawOnTheFront() const override;

	static void WithinTheScreenInit();
	static void PlayAudio();
	static void StopAudio();
	
	/// <summary>
	/// 出現
	/// </summary>
	void Spawn();

private:
	/// <summary>
	/// 再出現
	/// </summary>
	void ReSpawn(float delta);

	/// <summary>
	/// 目的地の設定
	/// </summary>
	/// <param name="location">移動したい場所</param>
	void SetDestination(Vector2D location);


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
