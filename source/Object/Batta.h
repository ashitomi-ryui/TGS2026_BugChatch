#pragma once

#include"../Utilitys/Math.h"

class Batta
{
private:
	static Vector2D batta;
	float time;
	int count;
	bool BattaDestroy;
	int now_batta;
	int old_batta;
	int battacount;
	int battaspawn;
	float groundyY;
public:
	void BattaInit(void);
	void BattaUpdate(float delta_second);
	void BattaDraw(void);
	Vector2D* BattaLocation(void);
	void SetBatta(class Bug* p);
};

