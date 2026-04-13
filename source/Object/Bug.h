#pragma once
#include"../Utilitys/Math.h"

struct Bug
{
	int flag;
	int x;
	int y;
};

void BugInit(void);
void BugUpdate(void);
void BugGet(void);