#include "pch.h"
#include "CStartScene.h"
#include "Define.h"

void CStartScene::Initialize()
{
}

int CStartScene::Update()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		return OBJ_CLEAR;
	}
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

	newFont = CreateFont(25, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	oldFont = (HFONT)SelectObject(hDC, newFont);
	TCHAR szStartText[32];
	wsprintf(szStartText, L"Space: Game Start");
	TextOut(hDC, WINCX / 2 - 120, WINCY / 2 + 170, szStartText, lstrlen(szStartText));
	SelectObject(hDC, oldFont);
	DeleteObject(newFont);
}
