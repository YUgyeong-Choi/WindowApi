#pragma once
#include "CObject.h"
class CPlayerDH  : public CObject
{
public:
	CPlayerDH();
	virtual ~CPlayerDH() { Release(); }

	void Initialize() override;
	int  Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
	void Jump();
	void KeyInput();
	PLAYERSTATUS GetPlayerState() { return m_ePlayerStatus; }
	void SetPlayerState(PLAYERSTATUS _state) { m_ePlayerStatus = _state; }

	void ScrollOffset();
protected:
	PLAYERSTATUS	m_ePlayerStatus;
	
	
private:

};

