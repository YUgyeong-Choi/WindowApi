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
	return OBJ_CLEAR;
}

void StartScene::Late_Update()
{
}

void StartScene::Render(HDC _hDC)
{
	Rectangle(_hDC, 0, 0, WINCX, WINCY);


	HFONT newFont = CreateFont(48, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	HFONT oldFont = (HFONT)SelectObject(_hDC, newFont);

	TCHAR szStartText[32];
	wsprintf(szStartText, L"Monster Spawn");
	TextOut(_hDC, WINCX / 2 - 150, WINCY / 2 - 100, szStartText, lstrlen(szStartText));
	SelectObject(_hDC, oldFont);
	DeleteObject(newFont);
	Sleep(1500);
}

void StartScene::Release()
{
}
