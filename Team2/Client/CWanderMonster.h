#pragma once
#include "CMonster.h"

class CWanderMonster : public CMonster
{
public:
	CWanderMonster();
	~CWanderMonster();

public:
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
	void OnCollision(CObject* _op) override;

private:
	void Jump();
};
