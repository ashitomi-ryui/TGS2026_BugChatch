#pragma once

#include"SceneType.h"
#include"../Utilitys/Math.h"

int InGameInit(void);
eSceneType InGameUpdate(float delta_second);
void InGameDraw(void);


struct Icon
{
	int cicada;
	int dragonfly;
	int grasshopper;
};


/// <summary>
/// 最も近い木の座標を取得する
/// </summary>
/// <param name="location">座標</param>
/// <returns>最も近い木の座標</returns>
Vector2D FindNearestTree(Vector2D location);

/// <summary>
/// 最も近い草の座標を取得する
/// </summary>
/// <param name="location">座標</param>
/// <returns>最も近い草の座標</returns>
Vector2D FindNearestLeaf(Vector2D location);

/// <summary>
/// エフェクトを生成
/// </summary>
/// <param name="location">座標</param>
/// <param name="color">色</param>
void SetEffect(Vector2D location, unsigned int color = 0xffff00);