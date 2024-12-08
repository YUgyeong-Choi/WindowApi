#pragma once
#include "CBox.h"
class CBoxItem : public CBox
{
public:
	CBoxItem();
	virtual ~CBoxItem();
	// CBox을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
	virtual void OnCollision(CObject* _op);

	// CBox을(를) 통해 상속됨
	void OnBlockEvent() override;
};

