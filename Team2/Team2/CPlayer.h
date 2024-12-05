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
	//플레이어 조작
	void Key_Input(); 
	// 점프 관련
	void Jumping();  
	//플레이어 카메라 (화면)
	void Offset(); 
private:
	bool                m_bJump;
	float               m_fJumpPower;
	float               m_fTime;
};

