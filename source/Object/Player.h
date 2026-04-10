#pragma once

struct Vector2D
{
	float x;
	float y;
};

struct Player
{
	Vector2D location;
	Vector2D move;

};

struct BugNet
{
	Vector2D stickLocation;
	Vector2D netLocation;
	Vector2D move;
};