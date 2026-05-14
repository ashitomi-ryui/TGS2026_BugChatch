#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"

class Help
{
private:

public:
	Help();
	~Help();
public:
	int Init();
	void Draw()const;
	eSceneType Update(float delta_second);
};