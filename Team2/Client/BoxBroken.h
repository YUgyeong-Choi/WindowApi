#pragma once
#pragma once

#include "CBox.h"

class BoxBroken : public CBox
{
public:
	BoxBroken();
	~BoxBroken();
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
	virtual void OnCollision(CObject* _op);
private:

};