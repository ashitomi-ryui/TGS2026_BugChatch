#pragma once
#include"../Utilitys/Math.h"

class Bug
{
private:
	int getcount[3];
private:
	void BugHitCheck(Vector2D NetLocation);

public:
	void BugInit(void);
	void BugUpdate(void);
	void BugDraw(void);
	void SetPlayer(class Player* p);
	int GetBattaScore(void);
	int GetSemiScore(void);
	int GetTonboScore(void);
	int GetBugScore(void);

};
//void BugRespawn(float delta_second,int count);




