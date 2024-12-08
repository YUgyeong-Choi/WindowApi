#pragma once
#include "../Client/Define.h"
#include "../Client/CLine.h"
class CObject
{
public:
	CObject();
	virtual ~CObject() {};

	virtual void Initialize()		PURE;
	virtual int	 Update()			PURE;
	virtual void LateUpdate()		PURE;
	virtual void Render(HDC hDC)	PURE;
	virtual void Release()			PURE;

	void FixedUpdate() {};
	virtual void UpdateRect();
	virtual void OnCollision(CObject* _op);
	virtual void OnDead();

	INFO	GetINFO() { return m_tInfo; }
	RECT*	GetRECT() { return &m_tRect; }
	void	SetPos(float _fX, float _fY) { m_tInfo.fX = _fX, m_tInfo.fY = _fY; }
	void	SetSize(float _fX, float _fY) { m_tInfo.fCX = _fX, m_tInfo.fCY = _fY; }

	float	GetAngle() { return m_fAngle; }
	void	SetAngle(float _a) { m_fAngle = _a; }

	bool	GetIsDead() { return m_bIsDead; }
	void	SetIsDead(bool _b) { m_bIsDead = _b; }

	bool	GetIsActive() { return m_bIsActive; }
	void	SetIsActive(bool _b) { m_bIsActive = _b; }

	bool	GetIsJumping() { return m_bIsJumping; }
	void	SetIsJumping(bool _b) { m_bIsJumping = _b; }

	bool	GetIsGround() { return m_bIsGround; }
	void	SetIsGround(bool _b) { m_bIsGround = _b; }

	Vector<float> GetDirection() { return m_tDir; }
	void	SetDirection(Vector<float>& _d) { m_tDir = _d; }
	void	SetDirection(float _fx, float _fy) { m_tDir = { _fx, _fy }; }

	void	SetLevel(int _l) { m_iLevel = _l; }
	int		GetLevel() { return m_iLevel; }

	void	SetTargetObject(CObject* t) { m_pTarget = t; }
	CObject* GetTargetObject() { return m_pTarget; }

	void	SetTargetLine(CLine* t) { m_pTargetLine = t; }
	CLine*	GetTargetLine() { return m_pTargetLine; }

	void	SetID(OBJID _i) { m_eOID = _i; }
	OBJID	GetID() { return m_eOID; }


protected:
	INFO			m_tInfo;
	RECT			m_tRect;
	ACTIONSTATUS	m_eActionStatus;
	Vector<float>	m_tDir;
	bool			m_bIsDead;
	bool			m_bIsActive;
	bool			m_bIsJumping;
	bool			m_bIsGround;
	int				m_iLevel;
	int				m_iHp;
	float			m_fSpeed;
	float			m_fAngle;
	float			m_fJumpPower;
	float			m_fTime;
	ULONG64			m_ullTime;
	Vector<float>	m_tVelocity;
	
	OBJID			m_eOID;
	CObject*		m_pTarget;
	CLine*			m_pTargetLine;
private:	
};

