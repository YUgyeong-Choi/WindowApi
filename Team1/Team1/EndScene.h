#pragma once
#include "SceneObj.h"
class EndScene :public SceneObj
{
public:
	EndScene();
	~EndScene();
public:
	virtual void Initialize(Obj* _pPlayer) override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override;
};

