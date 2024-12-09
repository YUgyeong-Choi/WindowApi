#pragma once
#include "CBlock.h"
class CBlockItem : public CBlock
{
public:
	CBlockItem();
	virtual ~CBlockItem();
	// CBox��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
	virtual void OnCollision(CObject* _op);

	

	//�̰� �Ⱦ��� onblockevent���� if������ itemtype �°� �����ϴ°� ���� �ҵ�? 
	void CreateMushRoom();
	void CreateFlower();
	void CreateStar();

	void SetContain() { m_bContain = !m_bContain; }
	void SetItemType(ITEMTYPE _eItemType) { m_eItemType = _eItemType; }

private:
	// �ѹ��� ������ �����ϰ� �ϱ� ����, �����ϸ� false��
	bool m_bContain; 
	// ������ �ִ� Ÿ�� ǥ��, �����ϰ� Ÿ�� �����ϸ� �ɵ�?
	ITEMTYPE m_eItemType;
};

