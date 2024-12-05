#pragma once
#include "Define.h"
#include "CObject.h"
class CMonster : public CObject
{
public:
	CMonster();
	virtual ~CMonster();
public:
	virtual void		Initialize() override;
	virtual int		Update() override;
	virtual void		Late_Update() override;
	virtual void		Render(HDC _hDC) override;
	virtual void		Release() override;
};

