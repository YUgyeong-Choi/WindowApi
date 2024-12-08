#include "pch.h"
#include "CStartScene.h"
#include "Define.h"

void CStartScene::Initialize()
{
}

int CStartScene::Update()
{
	if (GetAsyncKeyState(VK_F1))
	{
		return OBJ_KL;
	}

	if (GetAsyncKeyState(VK_F2))
	{
		return OBJ_SH;

	}

	if (GetAsyncKeyState(VK_F3))
	{
		return OBJ_DH;
	}

	if (GetAsyncKeyState(VK_F4))
	{
		return OBJ_MH;
	}

	if (GetAsyncKeyState(VK_F5))
	{
		return OBJ_YK;
	}

	return OBJ_NOEVENT;
}

void CStartScene::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	HFONT newFont = CreateFont(50, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	HFONT oldFont = (HFONT)SelectObject(hDC, newFont);
	TCHAR szTitleText[32];
	wsprintf(szTitleText, L"Game Start");
	TextOut(hDC, WINCX / 2 - 130, WINCY / 2 - 150, szTitleText, lstrlen(szTitleText));
	SelectObject(hDC, oldFont);
	DeleteObject(newFont);

	newFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	oldFont = (HFONT)SelectObject(hDC, newFont);
	TCHAR szStartText[50];
	wsprintf(szStartText, L"F1: °æ·¡ F2 : ½ÂÈÆ F3 : µ¿Çõ F4 : ¸íÈÆ F5 : À¯°æ");
	TextOut(hDC, WINCX / 2 - 300, WINCY / 2 + 170, szStartText, lstrlen(szStartText));
	SelectObject(hDC, oldFont);
	DeleteObject(newFont);
}
