#pragma once
#include "Obj.h"
class Player : public Obj
{
public:
	Player();
	virtual ~Player();
public:
	void        Set_Bullet(list<Obj*>* pBullet) { m_BulletList = pBullet; }
	void        Set_Shield(list<Obj*>* pShield) { m_pShieldList = pShield; }
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
public:
	void Upgrade_Bullet() { ++m_iBulletLevel; }
	void Set_PSpeed(float _iSpeed) { m_fSpeed += _iSpeed; }
	void Set_SSpeed(int _iRate);
private:
	void Key_Input();
	void Calc_Angle();
private:
	list<Obj*>* m_BulletList;
	list<Obj*>* m_pShieldList;
	POINT m_tPosin;
	int m_iBulletLevel;
	int m_iFireRate; //�Ѿ� �߻� �ӵ�
	int m_iTick; 
};

