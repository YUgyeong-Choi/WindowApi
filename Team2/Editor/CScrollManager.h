#pragma once
class CScrollManager
{
public:
	float			GetScrollX() { return m_fScrollX; }
	float			GetScrollY() { return m_fScrollY; }

	void			SetScrollX(float _fX) { m_fScrollX += _fX; }
	void			SetScrollY(float _fY) { m_fScrollY += _fY; }

	static CScrollManager* GetInstance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CScrollManager;

		return m_pInstance;
	}

	static void	DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	CScrollManager();
	~CScrollManager() {};

	static CScrollManager* m_pInstance;

	float			    m_fScrollX;
	float			    m_fScrollY;
};

