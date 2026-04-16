#pragma once
#include"../Utilitys/Math.h"

void BugInit(void);
void BugUpdate(void);
void BugDraw(void);
void BugGet(void);

void SetPlayer(class Player* p);
void BugHitCheck(Vector2D NetLocation);
int GetBattaScore(void);
int GetSemiScore(void);