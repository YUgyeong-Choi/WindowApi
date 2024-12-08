#pragma once
#include "CObject.h"
class CPlayerKL : public CObject
{
public:
	CPlayerKL();
	virtual ~CPlayerKL() { Release(); }

	void Initialize() override;
	int  Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();
	void SelectAction();
	void Jumping();
	void SelectStatus();
	void KeyInput();
	void CreateBullet();

	void ScrollOffset();

	void SetPlayerStatus(PLAYERSTATUS _ePstatus) { m_ePstatus = _ePstatus; }
protected:
private:
	PLAYERSTATUS m_ePstatus;
	bool		m_bCollision;

};

