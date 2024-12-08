#pragma once
#include "CBlock.h"

class CBlockHard : public CBlock
{
public:
	CBlockHard();
	virtual ~CBlockHard();
	// CBox을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
	virtual void OnCollision(CObject* _op);
};

