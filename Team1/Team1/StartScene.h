#pragma once
#include "SceneObj.h"
class StartScene :public SceneObj
{
public:
	StartScene();
	virtual ~StartScene();
public:
	virtual void Initialize(Obj* _pPlayer) override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
};

