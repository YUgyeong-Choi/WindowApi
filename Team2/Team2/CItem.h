#pragma once
#include "CObject.h"
class CItem : public CObject
{
public:
	CItem();
	virtual ~CItem();
public:
	virtual void		Initialize() override;
	virtual int		Update() override;
	virtual void		Late_Update() override;
	virtual void		Render(HDC _hDC) override;
	virtual void		Release() override;
};


