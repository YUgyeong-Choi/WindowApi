#pragma once
#include "SceneObj.h"
class StageScene : public SceneObj
{
public:
	StageScene();
	~StageScene();
public:
	virtual void Initialize(Obj* _pPlayer) override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _hDC) override;
	virtual void Release() override; //플레이어 빼고 release해줌
protected:
	void SpawnMonster(); //만약에 스테이지 구분되면 virtual로
private:
	ULONGLONG	m_dwTime;
	bool bFinish;
};

