#pragma once
#include "Obj.h"
class Player : public Obj
{
public:
	Player();
	virtual ~Player();
public:
	void        Set_Bullet(list<Obj*>* pBullet) { m_pBulletList = pBullet; }
	void        Set_Shield(list<Obj*>* pShield) { m_pShieldList = pShield; }
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
public: //아이템 관련 함수
	void Upgrade_Bullet();
	void Set_PSpeed(float _iSpeed) { m_fSpeed += _iSpeed; }
	void Set_SSpeed(int _iRate);
	void Add_Shield();
private:
	void Key_Input();
	void Calc_Angle();
	Obj* Create_Bullet(float _fAngle);
	Obj* Create_BulletScrew(float _fAngle);
private:
	list<Obj*>* m_pBulletList;
	list<Obj*>* m_pShieldList;
	POINT m_tPosin;
	int m_iBulletLevel;
	int m_iFireRate; //총알 발사 속도
	int m_iTick; 
};

