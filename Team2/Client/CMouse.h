#pragma once
#include "CObject.h"

class CMouse : public CObject
{
public:
	CMouse();
	virtual ~CMouse() { Release(); }

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};