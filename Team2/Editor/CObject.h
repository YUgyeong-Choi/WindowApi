#pragma once
#include "Define.h"
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

	virtual void UpdateRect();
	virtual void OnCollision(CObject* _op);	
	virtual void OnDead();

	INFO GetINFO() { return m_tInfo; }
	RECT* GetRECT() { return &m_tRect; }
	void SetPos(float _fX, float _fY) { m_tInfo.fX = _fX, m_tInfo.fY = _fY; }
	void SetSize(float _fX, float _fY) { m_tInfo.fCX = _fX, m_tInfo.fCY = _fY; }

	float GetAngle() { return m_fAngle; }
	void SetAngle(float _a) { m_fAngle = _a; }

	bool GetIsDead() { return m_bIsDead; }
	void SetIsDead(bool _b) { m_bIsDead = _b; }

	void SetActionStatus(ACTIONSTATUS _status) { m_eAction = _status; }
	ACTIONSTATUS GetActionStatus() { return m_eAction; }

	Vector<float> GetDirection() { return m_tDir; }
	void SetDirection(Vector<float>& _d) { m_tDir = _d; }
	void SetDirection(float _fx, float _fy) { m_tDir = { _fx, _fy }; }

	void SetLevel(int _l) { m_iLevel = _l; }
	int GetLevel() { return m_iLevel; }

	void SetOBJID(OBJID _id) { m_eOID = _id; }
	OBJID GetOBJID() { return m_eOID; }

	// 나와 대상의 좌표 간의 각도 반환 (디그리로 반환).
	// -180 ~ 180도 범위
	float GetDegreeAngle(INFO _info)
	{
		INFO vector = {_info.fX - m_tInfo.fX, _info.fY - m_tInfo.fY };
		float angle = atan2f(vector.fY, vector.fX);

		return angle * (180.f / PI);
	}

protected:
	ACTIONSTATUS	m_eAction;
	INFO			m_tInfo;
	RECT			m_tRect;
	bool			m_bIsDead;	
	int				m_iLevel;
	int				m_iHp;
	float			m_fSpeed;
	float			m_fAngle;
	float			m_fJumpPower;
	float			m_fTime;
	ULONG64			m_ullTime;
	Vector<float>	m_tDir;
	OBJID			m_eOID;
	CObject*		m_pTarget;	
	const float const		m_fGravity = 3.f;
	float			m_fCurrentGravity;
	bool			m_bIsFloor = false;
private:
};

