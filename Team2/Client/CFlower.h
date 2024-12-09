#pragma once
#include "CItem.h"

class CFlower : public CItem
{
public:
	CFlower();
	~CFlower();
	virtual void Initialize();
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void OnCollision(CObject* _op);
private:
	int m_iAiDir;
};