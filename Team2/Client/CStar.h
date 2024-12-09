#pragma once
#include "CItem.h"
class CStar :public CItem
{
public:
	CStar();
	~CStar();
	virtual void Initialize();
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void OnCollision(CObject* _op);
};

