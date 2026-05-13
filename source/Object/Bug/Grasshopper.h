#pragma once

#include"../../Utilitys/Math.h"

class Grasshopper
{
private:
	Vector2D m_location;	// 座標
	bool m_isAppearance;	// 出現フラグ

public:
	Grasshopper();
	~Grasshopper();

public:
	void Set(Vector2D location);

private:
	/*Vector2D batta;*/
	float time;
	float time1;
	int count;
	bool BattaDestroy;
	int now_batta[10];
	int old_batta[10];
	int battacount;
	int battaspawn;
	float groundyY;
	float vx = 0.0f;
	float vy = 0.0f;
	float Watitime = 0.0f;

	bool Groundy;
	bool UpMove;      // 上昇中かどうか
	float JumpTopY;    // 今回のジャンプで止まるY座標

	bool TopStop;     // 頂点で停止中
	float TopStopTimer = 0.0f;

	void Init(int index);
	void BattaUpdate(float delta_second);
	void BattaDraw(void);
	Vector2D* BattaLocation(void);
	void SetBatta(class Bug* p);
};

