#pragma once
#include "../Utilitys/Math.h"

class FlowingTime
{
private:
	bool m_isDisplay;
	float m_x;
	int m_time;
	unsigned int m_color;

public:
	FlowingTime();
	~FlowingTime();

public:
	void Init();

	/// <summary>
	/// ê∂ê¨
	/// </summary>
	/// <param name="time">ï\é¶éûä‘</param>
	/// <param name="color">êF</param>
	void Flow(int time, unsigned int color);

	void Update(float delta);
	void Draw() const;
};