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

	void SetStatus(PLAYERSTATUS _status) { m_bPlayerStatus = _status; }
	PLAYERSTATUS GetStatus(PLAYERSTATUS _status) { return m_bPlayerStatus; }


protected:
private:
	PLAYERSTATUS	m_bPlayerStatus;
};

