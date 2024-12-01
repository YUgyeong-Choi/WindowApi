#include "pch.h"
#include "StartScene.h"

StartScene::StartScene() 
{
}

StartScene::~StartScene()
{
}

void StartScene::Initialize(Obj* _pPlayer)
{
}

int StartScene::Update()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		return OBJ_CLEAR;
	}
}

void StartScene::Late_Update()
{
}

void StartScene::Render(HDC _hDC)
{
	Rectangle(_hDC, 0, 0, WINCX, WINCY);
	HFONT newFont = CreateFont(50, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	HFONT oldFont = (HFONT)SelectObject(_hDC, newFont);
	TCHAR szTitleText[32];
	wsprintf(szTitleText, L"Game Start");
	TextOut(_hDC, WINCX / 2 - 130, WINCY / 2 - 150, szTitleText, lstrlen(szTitleText));
	SelectObject(_hDC, oldFont);
	DeleteObject(newFont);
	
	newFont = CreateFont(25, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	oldFont = (HFONT)SelectObject(_hDC, newFont);
	TCHAR szStartText[32];
	wsprintf(szStartText, L"Space: Game Start");
	TextOut(_hDC, WINCX / 2 -120, WINCY / 2 + 170, szStartText, lstrlen(szStartText));
	SelectObject(_hDC, oldFont);
	DeleteObject(newFont);

}

void StartScene::Release()
{
}