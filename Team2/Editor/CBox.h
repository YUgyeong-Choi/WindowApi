#pragma once
#include "CObject.h"
#include "Define.h"
#include "CScrollManager.h"

class CBox : public CObject
{
public:
	CBox();

	// �� �浹 �� �̺�Ʈ.
	virtual void OnBlockEvent() PURE;


};

