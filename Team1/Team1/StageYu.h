#pragma once
#include "StageScene.h"
class StageYu :public StageScene
{
public:
	StageYu();
	virtual ~StageYu();
public:
	virtual void SpawnMonster();
	virtual int Update();
	virtual void Late_Update() override;
};

