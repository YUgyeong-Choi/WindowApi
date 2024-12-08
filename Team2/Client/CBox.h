#pragma once
#include "CObject.h"
#include "Define.h"
#include "CScrollManager.h"

class CBox : public CObject
{
public:
	CBox();
	virtual ~CBox() {};

	// 블럭 충돌 시 이벤트.
	virtual void OnBlockEvent() PURE;

//protected:
//	BLOCKTYPE GetBlockType()
//	{
//		return m_BlockType;
//	}
//
//protected:
//	BLOCKTYPE m_BlockType;
};

