#pragma once
#include "CMonster.h"

class CFollowMonster : public CMonster
{
public:
	CFollowMonster();
	~CFollowMonster() { Release(); }

	void Initialize() override;
	int  Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _op) override;

};
