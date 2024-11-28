#pragma once
#include "Define.h"
class SceneObj
{
public:
	SceneObj();
	virtual ~SceneObj();
public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
};

