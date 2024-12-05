#pragma once
#include "Define.h"
#include "CObject.h"
class CPlayer : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();
public:
	virtual void		Initialize() override;
	virtual int		Update() override;
	virtual void		Late_Update() override;
	virtual void		Render(HDC _hDC) override;
	virtual void		Release() override;
private:
	void Key_Input(); //플레이어 조작
	void Jumping(); // 점프 관련 
private:
	bool                m_bJump;
	float               m_fJumpPower;
	float               m_fTime;
};

