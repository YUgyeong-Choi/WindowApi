#pragma once
class CSceneObject
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC hDC);
protected:
	/// <summary>
	/// 에디터로 추출 한 맵 불러옴.
	/// </summary>
	/// <param name="_name">Data 폴더에서 불러올 맵 이름</param>
	void Load(const TCHAR* _name = L"Box");
};

