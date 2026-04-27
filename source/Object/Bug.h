#pragma once
#include"../Utilitys/Math.h"

class Bug
{
private:
	int getcount[3][10];
private:
	void BugHitCheck(Vector2D NetLocation, float NetRadius);

public:
	void BugInit(void);
	void BugUpdate(void);
	void BugDraw(void);
	void SetPlayer(class Player* p);
	void SetBatta(class Batta* p);
	void SetSemi(class Semi* p);
	void SetTonbo(class Tonbo* p);

	int GetBattaScore(int index);
	int GetSemiScore(int index);
	int GetTonboScore(int index);
	/*int GetBugScore(void);*/

};
//void BugRespawn(float delta_second,int count);




