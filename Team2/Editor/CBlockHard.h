#pragma once
#include "CBlock.h"

class CBlockHard : public CBlock
{
public:
	CBlockHard();
	virtual ~CBlockHard();
	// CBox��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
	virtual void OnCollision(CObject* _op);
};

