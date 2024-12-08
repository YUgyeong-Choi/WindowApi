#pragma once
#include "CItem.h"

class CMushRoom : public CItem
{
public:
	CMushRoom();
	~CMushRoom();
	virtual void Initialize();
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void OnCollision(CObject* _op);

	void Move();
	bool CheckOnGround();

};