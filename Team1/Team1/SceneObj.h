#pragma once
#include "Define.h"
#include "Obj.h"
class SceneObj
{
public:
	SceneObj();
	virtual ~SceneObj();
public:
	virtual void Initialize(Obj* _pPlayer);
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _hDC);
	virtual void Release();
protected:
	list<Obj*> m_ObjList[OBJ_END];
};

