#pragma once
#include "CObject.h"
class CPlayer final : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer() { Release(); }

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
	bool m_bIsGround;
};

