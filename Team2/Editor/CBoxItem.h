#pragma once
#include "CBox.h"
class CBoxItem : public CBox
{
public:
	CBoxItem();
	virtual ~CBoxItem();
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

