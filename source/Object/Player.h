#pragma once
#include "../Utilitys/Input.h"
#include "../Utilitys/Math.h"

struct Player
{
	int score;
	Vector2D location;	// ç¿ïW
	Vector2D moveSpeed;	// ìÆÇ≠ë¨ìx
	Vector2D maxSpeed;	// ç≈ëÂë¨ìx

};

struct BugNet
{
	Vector3D stickLocation;
	Vector2D netLocation;
	Vector2D move;
};