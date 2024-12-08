#pragma once
#include "Define.h"
#include "CObject.h"
class CBox : public CObject
{
public:
	CBox();
	virtual ~CBox() { Release(); }

	virtual void Initialize()		override;
	virtual int  Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;

	virtual void OnCollision(CObject* _op);
	virtual void OnDead();	

	void SetBoxType(BOXTYPE _bt) { m_eBoxType = _bt; }
private:
	bool m_bCanHit;
	bool m_bCanBroke;
	BOXTYPE m_eBoxType;
	ITEMTYPE m_eItemType;
};

