#pragma once
#include "SceneObj.h"
class EndScene :public SceneObj
{
public:
	EndScene();
	virtual ~EndScene();
public:
	virtual int Update() override;
	virtual void Render(HDC _hDC) override;
};

