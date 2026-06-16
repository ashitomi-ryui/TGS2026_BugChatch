#include "Cage.h"

#include <DxLib.h>
#include"Bug/Bug.h"
#include"../Utilitys/Camera.h"
#include"../Utilitys/Random.h"

int Cage::oldCicada = 0;
int Cage::oldDragonfly = 0;
int Cage::oldGrasshopper = 0;
Vector2D Cage::location = { 100.0f * D_CAGE_RATIO, 75.0f * D_CAGE_RATIO };

float Cage::animTime = 0.0f;
int Cage::animCount = 6;

int Cage::cicadaImage = -1;
int Cage::dragonflyImage[2] = {};
int Cage::grasshopperImage[4] = {};
int Cage::cageImage[4] = {};

Cage bug[D_CAGE_MAX];	// ‚©‚²“à‚Ì’Ž

Cage::Cage()
{
	m_type = eCicada;
	m_display = false;
	m_location = {};
	m_moveSpeed = {};
	m_angle = 0.0f;

	m_state = eJoin;

	m_time = 0.0f;
	m_animTime = 0.0f;
	m_animCount = 0;
}

Cage::~Cage()
{
}

void Cage::Init()
{
	oldCicada = 0;
	oldDragonfly = 0;
	oldGrasshopper = 0;

	animTime = 0.0f;
	animCount = 6;

	cicadaImage = LoadGraph("assets/images/Bugs/Cicada/Cicada.PNG");

	dragonflyImage[0] = LoadGraph("assets/images/Bugs/Dragonfly/Dragonfly1.PNG");
	dragonflyImage[1] = LoadGraph("assets/images/Bugs/Dragonfly/Dragonfly2.PNG");

	grasshopperImage[0] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper1.PNG");
	grasshopperImage[1] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper2.PNG");
	grasshopperImage[2] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper3.PNG");
	grasshopperImage[3] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper4.PNG");

	cageImage[0] = LoadGraph("assets/images/OtherObjects/Cage/Cage1.PNG");
	cageImage[1] = LoadGraph("assets/images/OtherObjects/Cage/Cage2.PNG");
	cageImage[2] = LoadGraph("assets/images/OtherObjects/Cage/Cage3.PNG");
	cageImage[3] = LoadGraph("assets/images/OtherObjects/Cage/Cage4.PNG");

	for (int id = 0;id < D_CAGE_MAX;id++)
	{
		bug[id].BugInit();
	}
}

void Cage::Update(float delta)
{
	animTime += delta;
	
	if (animTime >= 0.25f)
	{
		animCount++;
		animTime = 0.0f;
	}


	int cicadaCount = Bug::GetCicadaCount();
	int dragonflyCount = Bug::GetDragonflyCount();
	int grasshopperCount = Bug::GetGrasshopperCount();

	if (cicadaCount > oldCicada)
	{
		for (int i = 0;i < cicadaCount - oldCicada;i++)
		{
			for (int j = 0;j < D_CAGE_MAX;j++)
			{
				if (!bug[j].GetDisplay())
				{
					bug[j].Add(eCicada);
					break;
				}
			}
		}
	}
	if (dragonflyCount > oldDragonfly)
	{
		for (int i = 0;i < dragonflyCount - oldDragonfly;i++)
		{
			for (int j = 0;j < D_CAGE_MAX;j++)
			{
				if (!bug[j].GetDisplay())
				{
					bug[j].Add(eDragonfly);
					break;
				}
			}
		}
	}
	if (grasshopperCount > oldGrasshopper)
	{
		for (int i = 0;i < grasshopperCount - oldGrasshopper;i++)
		{
			for (int j = 0;j < D_CAGE_MAX;j++)
			{
				if (!bug[j].GetDisplay())
				{
					bug[j].Add(eGrasshopper);
					break;
				}
			}
		}
	}

	for (int id = 0;id < D_CAGE_MAX;id++)
	{
		bug[id].BugUpdate(delta);
	}

	oldCicada = cicadaCount;
	oldDragonfly = dragonflyCount;
	oldGrasshopper = grasshopperCount;
}

void Cage::Draw()
{
	int num = 0;

	switch (animCount)
	{
	case 0:
	case 5:
		num = 1;
		break;
	case 1:
	case 4:
		num = 2;
		break;
	case 2:
	case 3:
		num = 3;
		break;
	default:
		num = 0;
		break;
	}

	Camera::DrawGraph(location, 3.0f * D_CAGE_RATIO, 3.0f * D_CAGE_RATIO, 0.0f, cageImage[num]);

	for (int id = 0;id < D_CAGE_MAX;id++)
	{
		bug[id].BugDraw();
	}
}

void Cage::BugInit()
{
	m_display = false;
	m_location = { 0.0f, -100.0f * D_CAGE_RATIO };
	m_moveSpeed = {};
	m_angle = 1.0f * DX_PI_F;

	m_state = eJoin;

	m_time = 0.0f;
	m_animTime = 0.0f;
	m_animCount = 0;
}

void Cage::BugUpdate(float delta)
{
	if (m_display)
	{
		m_time -= delta;
		m_animTime += delta;

		switch (m_state)
		{
		case eJoin:
			Join(delta);
			break;
		case eStand:
			Stand(delta);
			break;
		case eMove:
			Move(delta);
			break;
		}

		// ˆÚ“®
		m_location = Vec2Add(m_location, Vec2Mult(m_moveSpeed, delta));

		// ˆÚ“®§ŒÀ
		if (m_location.x < -D_CAGE_WIDTH)
		{
			m_location.x = -D_CAGE_WIDTH;
			m_moveSpeed.x = 0.0f;
		}
		else if (m_location.x > D_CAGE_WIDTH)
		{
			m_location.x = D_CAGE_WIDTH;
			m_moveSpeed.x = 0.0f;
		}
		if (m_location.y < -D_CAGE_HEIGHT && m_state != eJoin)
		{
			m_location.y = -D_CAGE_HEIGHT;
			m_moveSpeed.y = 0.0f;
		}
		else if (m_location.y > D_CAGE_HEIGHT)
		{
			m_location.y = D_CAGE_HEIGHT;
			m_moveSpeed.y = 0.0f;
		}
	}
}

void Cage::BugDraw() const
{
	if (m_display)
	{
		Vector2D loc = {};
		loc.x = location.x + m_location.x;
		loc.y = location.y + m_location.y;
		float angle = m_angle;

		switch (m_type)
		{
		case eCicada:
			Camera::DrawGraph(loc, 2.0f * D_CAGE_RATIO, 2.0f * D_CAGE_RATIO, angle, cicadaImage);
			break;
		case eDragonfly:
			angle += 0.70f * DX_PI_F;
			Camera::DrawGraph(loc, 2.0f * D_CAGE_RATIO, 2.0f * D_CAGE_RATIO, angle, dragonflyImage[m_animCount]);
			break;
		case eGrasshopper:
			angle += 0.6f * DX_PI_F;
			Camera::DrawGraph(loc, 2.0f * D_CAGE_RATIO, 2.0f * D_CAGE_RATIO, angle, grasshopperImage[m_animCount]);
			break;
		}
	}
}

void Cage::Add(Type type)
{
	m_type = type;
	m_display = true;

	animTime = 0.0f;

	switch (animCount)
	{
	case 1:
	case 4:
		animCount = 1;
		break;
	case 2:
	case 3:
		animCount = 2;
		break;
	default:
		animCount = 0;
		break;
	}
}

void Cage::Join(float delta)
{
	switch (m_type)
	{
	case eDragonfly:
		m_animCount = 1;
		break;
	case eGrasshopper:
		m_animCount = 0;
		break;
	}

	m_moveSpeed.y += 100.0f * delta * D_CAGE_RATIO;

	// ‘¬“x§ŒÀ
	int len = Length(m_moveSpeed);
	if (len > 100.0f * D_CAGE_RATIO)
	{
		len -= 100.0f * D_CAGE_RATIO;
		float shiita = VecATan2(m_moveSpeed, { 0.0f, 0.0f });
		m_moveSpeed.x += sinf(shiita) * len;
		m_moveSpeed.y -= cosf(shiita) * len;
	}

	if (m_location.y + m_moveSpeed.y * delta >= D_CAGE_HEIGHT)
	{
		m_state = eStand;
		m_time = 0.0f;
	}
}

void Cage::Stand(float delta)
{
	switch (m_type)
	{
	case eDragonfly:
		m_animCount = 1;
		break;
	case eGrasshopper:
		m_animCount = 0;
		break;
	}

	if (m_time <= 0.0f)
	{
		m_angle = Random::GetRand(0.0f, 2.0f, 0.125f) * DX_PI_F;

		m_state = eMove;
		m_time = Random::GetRand(0.0f, 5.0f, 0.1f);
	}
}

void Cage::Move(float delta)
{
	switch (m_type)
	{
	case eDragonfly:
		if (m_animTime >= 0.5f)
		{
			m_animCount = (m_animCount + 1) % 2;
			m_animTime = 0.0f;
		}
		break;
	case eGrasshopper:
		if (m_animTime >= 0.25f)
		{
			m_animCount = (m_animCount + 1) % 4;
			m_animTime = 0.0f;
		}
		break;
	}

	if (m_time <= 0.0f)
	{
		m_state = eStand;
		m_time = Random::GetRand(1.0f, 10.0f, 0.1f);
	}

	m_moveSpeed.x += sinf(m_angle) * 100.0f * D_CAGE_RATIO;
	m_moveSpeed.y -= cosf(m_angle) * 100.0f * D_CAGE_RATIO;

	// ‘¬“x§ŒÀ
	int len = Length(m_moveSpeed);
	if (len > 10.0f * D_CAGE_RATIO)
	{
		len -= 10.0f * D_CAGE_RATIO;
		float shiita = VecATan2(m_moveSpeed, { 0.0f, 0.0f });
		m_moveSpeed.x += sinf(shiita) * len;
		m_moveSpeed.y -= cosf(shiita) * len;
	}
}

bool Cage::GetDisplay() const
{
	return m_display;
}
