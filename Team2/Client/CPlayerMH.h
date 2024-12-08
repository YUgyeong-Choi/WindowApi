#pragma once
#include "CObject.h"
class CPlayerMH : public CObject
{
public:
	CPlayerMH();
	virtual ~CPlayerMH() { Release(); }

	virtual void Initialize()		override;
	virtual int  Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;

	virtual void Jump();
	virtual void KeyInput();


	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
	void		 ScrollOffset();
protected:
	PLAYERSTATUS		m_ePlayerStatus;
	float				m_fJumpTime;
private:

};

