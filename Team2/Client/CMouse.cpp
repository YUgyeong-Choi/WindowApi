#include "pch.h"
#include "CMouse.h"

CMouse::CMouse()
{
}

void CMouse::Initialize()
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
}

int CMouse::Update()
{
    POINT       ptMouse{};

    GetCursorPos(&ptMouse);

    ScreenToClient(g_hWnd, &ptMouse);


    m_tInfo.fX = (float)ptMouse.x;
    m_tInfo.fY = (float)ptMouse.y;


    __super::UpdateRect();

    ShowCursor(FALSE);
    return OBJ_NOEVENT;
}

void CMouse::LateUpdate()
{
}

void CMouse::Render(HDC hDC)
{
    Ellipse(hDC,
        m_tRect.left,
        m_tRect.top,
        m_tRect.right,
        m_tRect.bottom);
}

void CMouse::Release()
{
}
