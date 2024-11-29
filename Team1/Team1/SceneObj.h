#pragma once
#include "Define.h"
#include "Obj.h"
class SceneObj
{
public:
	SceneObj();
	virtual ~SceneObj();
public:
	virtual void Initialize(Obj* _pPlayer) PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC _hDC) PURE;
	virtual void Release() PURE;
protected:
	list<Obj*> m_ObjList[OBJ_END];
};

