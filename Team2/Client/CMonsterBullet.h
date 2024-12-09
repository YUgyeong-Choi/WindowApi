#pragma once
#include "CProjectile.h"
class CMonsterBullet : public CProjectile
{
public:
	CMonsterBullet();
	~CMonsterBullet() { Release(); }

	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _op) override;

	void Set_Degree();
private:
	bool m_dir;
};
