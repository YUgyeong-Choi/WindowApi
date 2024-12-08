#pragma once
class CSceneObject
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
protected:
	void Load();
};

