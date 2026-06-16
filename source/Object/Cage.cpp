#include "Cage.h"

#include <DxLib.h>
#include"Bug/Bug.h"
#include"../Utilitys/Camera.h"
#include"../Utilitys/Random.h"

int Cage::oldCicada = 0;
int Cage::oldDragonfly = 0;
int Cage::oldGrasshopper = 0;
Vector2D Cage::location = { 50.0f, 50.0f };

int Cage::cicadaImage[2] = {};
int Cage::dragonflyImage[2] = {};
int Cage::grasshopperImage[4] = {};
int Cage::cageImage = -1;

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

	cicadaImage[0] = LoadGraph("assets/images/Bugs/Cicada/Cicada.PNG");
	cicadaImage[1] = LoadGraph("assets/images/Bugs/Cicada/Fly1.PNG");

	dragonflyImage[0] = LoadGraph("assets/images/Bugs/Dragonfly/Dragonfly1.PNG");
	dragonflyImage[1] = LoadGraph("assets/images/Bugs/Dragonfly/Dragonfly2.PNG");

	grasshopperImage[0] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper1.PNG");
	grasshopperImage[1] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper2.PNG");
	grasshopperImage[2] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper3.PNG");
	grasshopperImage[3] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper4.PNG");

	cageImage = LoadGraph("assets/images/Circle.PNG");

	for (int id = 0;id < D_CAGE_MAX;id++)
	{
		bug[id].BugInit();
	}
}

void Cage::Update(float delta)
{
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
	Camera::DrawGraph(location, 50.0f / 640.0f, 50.0f / 640.0f, 0.0f, cageImage, false, false, 0x00ff00);

	for (int id = 0;id < D_CAGE_MAX;id++)
	{
		bug[id].BugDraw();
	}
}

void Cage::BugInit()
{
	m_display = false;
	m_location = {};
	m_moveSpeed = {};
	m_angle = 0.0f;

	m_state = eJoin;

	m_time = 0.0f;
	m_animTime = 0.0f;
	m_animCount = 0;
}

void Cage::BugUpdate(float delta)
{
	if (m_display)
	{
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
		m_location = Vec2Add(m_location, m_moveSpeed);

		// ˆÚ“®§ŒÀ
		if (m_location.x < -D_CAGE_WIDTH / 2.0f)
		{
			m_location.x = -D_CAGE_WIDTH / 2.0f;
		}
		else if (m_location.x > D_CAGE_WIDTH / 2.0f)
		{
			m_location.x = D_CAGE_WIDTH / 2.0f;
		}
		if (m_location.y < -D_CAGE_HEIGHT / 2.0f)
		{
			m_location.y = -D_CAGE_HEIGHT / 2.0f;
		}
		else if (m_location.y > D_CAGE_HEIGHT / 2.0f)
		{
			m_location.y = D_CAGE_HEIGHT / 2.0f;
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

		switch (m_type)
		{
		case eCicada:
			Camera::DrawGraph(loc, 1.0f, 1.0f, m_angle, cicadaImage[m_animCount]);
			break;
		case eDragonfly:
			Camera::DrawGraph(loc, 1.0f, 1.0f, m_angle, dragonflyImage[m_animCount]);
			break;
		case eGrasshopper:
			Camera::DrawGraph(loc, 1.0f, 1.0f, m_angle, grasshopperImage[m_animCount]);
			break;
		}
	}
}

void Cage::Add(Type type)
{
	m_type = type;
	m_display = true;
}

void Cage::Join(float delta)
{
	m_animTime = 0.0f;
	m_animCount = 0;


}

void Cage::Stand(float delta)
{
	m_animTime = 0.0f;
	m_animCount = 0;

	if (m_time <= 0.0f)
	{
		m_state = eMove;
		m_time = Random::GetRand(0.0f, 5.0f, 0.1f);
	}
}

void Cage::Move(float delta)
{
	m_animTime = 0.0f;
	m_animCount = 0;

	if (m_time <= 0.0f)
	{
		m_state = eStand;
		m_time = Random::GetRand(1.0f, 10.0f, 0.1f);
	}
}

bool Cage::GetDisplay() const
{
	return m_display;
}
