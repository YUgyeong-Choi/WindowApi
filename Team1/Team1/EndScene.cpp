#include "pch.h"
#include "EndScene.h"

EndScene::EndScene()
{
}

EndScene::~EndScene()
{
}

void EndScene::Initialize(Obj* _pPlayer)
{
}

int EndScene::Update()
{
	return OBJ_FINISH;
}

void EndScene::Late_Update()
{
}

void EndScene::Render(HDC _hDC)
{
	//HFONT newFont = CreateFont(48, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	//HFONT oldFont = (HFONT)SelectObject(_hDC, newFont);

	//TCHAR szEndText[32];
	//wsprintf(szEndText, L"Game End");
	//TextOut(_hDC, WINCX / 2 - 150, WINCY / 2 - 100, szEndText, lstrlen(szEndText));
	//SelectObject(_hDC, oldFont);
	//DeleteObject(newFont);
	Sleep(3000);
}

void EndScene::Release()
{
}
