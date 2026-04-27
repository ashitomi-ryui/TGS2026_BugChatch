#pragma once

#include"../Utilitys/Math.h"

class Batta
{
private:
	Vector2D batta;
	float time;
	float time1;
	int count;
	bool BattaDestroy;
	int now_batta[10];
	int old_batta[10];
	int battacount;
	int battaspawn;
	float groundyY;
public:
	Batta();
	~Batta();

public:
	void Init(Vector2D location = { 0.0f, 0.0f });
	void BattaUpdate(float delta_second);
	void BattaDraw(void);
	Vector2D* BattaLocation(void);
	void SetBatta(class Bug* p);
};

