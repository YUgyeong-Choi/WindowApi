#pragma once
#pragma once

#include "CBlock.h"

class CBlockBroken : public CBlock
{
public:
	CBlockBroken();
	~CBlockBroken();
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
	virtual void OnCollision(CObject* _op);
private:

};