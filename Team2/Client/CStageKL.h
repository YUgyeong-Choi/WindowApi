#pragma once
#include "CSceneObject.h"
class CStageKL :public CSceneObject
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
};

