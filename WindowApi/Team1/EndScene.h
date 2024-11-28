#pragma once
#include "SceneObj.h"
class EndScene :public SceneObj
{
public:
	EndScene();
	~EndScene();
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

