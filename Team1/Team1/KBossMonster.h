#pragma once
#include "MonsterShoot.h"

class KBossMonster : public MonsterShoot
{
public:
	KBossMonster();
	virtual ~KBossMonster() { Release(); }

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Release() override;
	virtual void Render(HDC _hdc) override;


private:
	int m_iPattern; // 랜덤하게 패턴 나오게
	ULONGLONG m_ulPatternTime; // 패턴 지속 시간
	float m_fDistance; // 움직일 거리 설정

public:
	
	void		Shoot_Sun(); // 전방향
	void		Shoot_Accel(); // 플레이어 있던 방향으로 날라옴 + 가속
	void		Shoot_Sprial(); // 나선처럼
	void		Shoot_Rain(); // 위에서 아래로 
	void		Shoot_Sun_Screw();
	void		Calc_Angle(float fX, float fY); // 유도탄 날릴때 각 계산 return하게 해서 setAngle에 넣어버리는게 좋을듯?
};

