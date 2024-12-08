#pragma once
#include "CObject.h"
class CPlayerYK  : public CObject
{
public:
	CPlayerYK();
	virtual ~CPlayerYK() { Release(); }

	void Initialize() override;
	int  Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
	void Jump();
	void KeyInput();
	void ScrollOffset();

	void SetStatus(PLAYERSTATUS _status) { m_ePlayerStatus = _status; }
	PLAYERSTATUS GetStatus(PLAYERSTATUS _status) { return m_ePlayerStatus; }


protected:
private:
	void OnMushroom();
	void OnFlower();
	void Fire();
private:
	PLAYERSTATUS	m_ePlayerStatus;
	float friction;
	int m_iAnimationTime;
	int m_iFireRate; //총알 발사 속도
	int m_iTick;
};

