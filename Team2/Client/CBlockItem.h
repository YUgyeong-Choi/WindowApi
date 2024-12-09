#pragma once
#include "CBlock.h"
class CBlockItem : public CBlock
{
public:
	CBlockItem();
	virtual ~CBlockItem();
	// CBox을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
	virtual void OnCollision(CObject* _op);

	

	//이거 안쓰고 onblockevent에서 if문으로 itemtype 맞게 생성하는게 좋긴 할듯? 
	void CreateMushRoom();
	void CreateFlower();
	void CreateStar();

	void SetContain() { m_bContain = !m_bContain; }
	void SetItemType(ITEMTYPE _eItemType) { m_eItemType = _eItemType; }

private:
	// 한번만 아이템 생성하게 하기 위해, 생성하면 false로
	bool m_bContain; 
	// 가지고 있는 타입 표현, 생성하고 타입 변경하면 될듯?
	ITEMTYPE m_eItemType;
};

