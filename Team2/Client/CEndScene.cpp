#include "pch.h"
#include "CEndScene.h"
#include "Define.h"

void CEndScene::Initialize()
{
}

int CEndScene::Update()
{
	return OBJ_FINISH;
}

void CEndScene::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	HFONT newFont = CreateFont(50, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	HFONT oldFont = (HFONT)SelectObject(hDC, newFont);
	TCHAR szTitleText[32];
	wsprintf(szTitleText, L"✯✯✯ Thank you for Playing ✯✯✯");
	TextOut(hDC, WINCX / 2 - 300, WINCY / 2 - 150, szTitleText, lstrlen(szTitleText));
	SelectObject(hDC, oldFont);
	DeleteObject(newFont);
	Sleep(3000);
}
