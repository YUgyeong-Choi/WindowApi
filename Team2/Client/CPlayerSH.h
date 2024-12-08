#pragma once
#include "CObject.h"

class CPlayerSH : public CObject
{
public:
	CPlayerSH();
	~CPlayerSH() { Release(); }

	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();

	void Jump();
	void KeyInput();


	void ScrollOffset();

	PLAYERSTATUS GetStatus() { return m_eStatus; }
	void SetStatus(PLAYERSTATUS _eStatus) { m_eStatus = _eStatus; }

protected:
	PLAYERSTATUS m_eStatus;

private:
};

