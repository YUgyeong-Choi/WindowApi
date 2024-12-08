#pragma once
#include "CObject.h"
class CItem : public CObject
{
public:
	CItem() {};
	virtual ~CItem() { Release(); }
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	ITEMTYPE GetItemType() { return m_eItemType; }
	void SetItemType(ITEMTYPE _it) { m_eItemType = _it; }
protected:
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();

	virtual void Move();
	bool CheckOnGround();


	
private:
	ITEMTYPE m_eItemType;
	float	m_fVelocityX;
	float	m_fVelocityY;
};

