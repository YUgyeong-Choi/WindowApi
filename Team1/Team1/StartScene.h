#pragma once
#include "SceneObj.h"
class StartScene :public SceneObj
{
public:
	StartScene();
	virtual ~StartScene();
public:
	virtual int Update() override;
	virtual void Render(HDC _hDC) override;
};

