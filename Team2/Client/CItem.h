#pragma once
#include "CObject.h"
class CItem : public CObject
{
public:
	CItem() :m_eItemType(ITEM_END) {};
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


protected:
	ITEMTYPE m_eItemType;
};
