#pragma once
#include "CBox.h"

class CBoxHard : public CBox
{
public:
	CBoxHard();
	virtual ~CBoxHard();
	// CBox��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
	virtual void OnCollision(CObject* _op);

	// CBox��(��) ���� ��ӵ�
	void OnBlockEvent() override;
};

