#pragma once

#include"SceneType.h"
#include"../Utilitys/Math.h"

int InGameInit(void);
eSceneType InGameUpdate(float delta_second);
void InGameDraw(void);

/// <summary>
/// Å‚à‹ß‚¢–Ø‚ÌÀ•W‚ğæ“¾‚·‚é
/// </summary>
/// <param name="location">À•W</param>
/// <returns>Å‚à‹ß‚¢–Ø‚ÌÀ•W</returns>
Vector2D FindNearestTree(Vector2D location);

Vector2D FindNearestLeaf(Vector2D location);

Vector2D FindNearestGround(Vector2D location);