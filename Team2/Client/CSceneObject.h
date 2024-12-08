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
	/// �����ͷ� ���� �� �� �ҷ���.
	/// </summary>
	/// <param name="_name">Data �������� �ҷ��� �� �̸�</param>
	void Load(const TCHAR* _name = L"Box");
};

