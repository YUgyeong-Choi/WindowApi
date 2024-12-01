#include "pch.h"
#include "StageScene.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "BulletItem.h"
#include "HealItem.h"
#include "ShootSpeedItem.h"
#include "PSpeedItem.h"
#include "ShieldItem.h"
#include "CollisionMgr.h"

StageScene::StageScene() : m_ulTime(0), m_bFinish(false), m_bStart(true), m_ulStartTime(0), m_IsNext(false)
{
}

StageScene::~StageScene()
{
	Release();
}

void StageScene::Initialize(Obj* _pPlayer)
{
	m_ObjList[OBJ_PLAYER].push_back(_pPlayer);
	static_cast<Player*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet(&m_ObjList[OBJ_BULLET_PLAYER]);
	static_cast<Player*>(m_ObjList[OBJ_PLAYER].front())->Set_Shield(&m_ObjList[OBJ_SHIELD]);
	
	m_ulTime = GetTickCount64();

}

int StageScene::Update()
{
	return OBJ_NOEVENT;
}

void StageScene::Late_Update()
{

	CollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_PLAYER]); //몬스터 & 플레이어
	CollisionMgr::Collision_Circle(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET_PLAYER]); //몬스터 & 총알
	CollisionMgr::Collision_Circle(m_ObjList[OBJ_SHIELD], m_ObjList[OBJ_MONSTER]); //몬스터 & 쉴드
	CollisionMgr::Collision_Circle(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_PLAYER]); //아이템 & 플레이어

	CollisionMgr::Collision_Circle(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BULLET_MONSTER]); // 플레이어 & 총알
	CollisionMgr::Collision_Circle(m_ObjList[OBJ_SHIELD], m_ObjList[OBJ_BULLET_MONSTER]); // 실드 & 총알
	

	if ((m_ulStartTime - GetTickCount64()) / 1000 <= 0) {
		m_bFinish = true;
	}

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->Late_Update();
	}

	
}

void StageScene::Render(HDC _hDC)
{
	if (m_bFinish) 
	{
		Rectangle(_hDC, 0, 0, WINCX, WINCY);
		HFONT newFont = CreateFont(50, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
		HFONT oldFont = (HFONT)SelectObject(_hDC, newFont);
		TCHAR szTitleText[32];
		wsprintf(szTitleText, L"☻☻☻ Clear ☻☻☻");
		TextOut(_hDC, WINCX / 2 - 200, WINCY / 2 - 150, szTitleText, lstrlen(szTitleText));
		SelectObject(_hDC, oldFont);
		DeleteObject(newFont);

		newFont = CreateFont(25, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
		oldFont = (HFONT)SelectObject(_hDC, newFont);
		TCHAR szStartText[32];
		wsprintf(szStartText, L"Space: Load Next");
		TextOut(_hDC, WINCX / 2 - 100, WINCY / 2 + 170, szStartText, lstrlen(szStartText));
		SelectObject(_hDC, oldFont);
		DeleteObject(newFont);
	}
	else {
		Rectangle(_hDC, int(GAME_WIN_LEFT), int(GAME_WIN_TOP), int(GAME_WIN_RIGHT), int(GAME_WIN_BOTTOM));

		for (size_t i = 0; i < OBJ_END; ++i)
		{
			for (auto& pObj : m_ObjList[i])
				pObj->Render(_hDC);
		}
		SetBkMode(_hDC, TRANSPARENT);

		HFONT hFont = CreateFont(28, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Arial");
		SetTextColor(_hDC, RGB(255, 255, 255));
		HFONT oldFont = (HFONT)SelectObject(_hDC, hFont);

		TCHAR szTimer[32];
		wsprintf(szTimer, L"Time: %d", int((m_ulStartTime - GetTickCount64()) / 1000));
		TextOut(_hDC, 620, 50, szTimer, lstrlen(szTimer));

		SelectObject(_hDC, oldFont);
		DeleteObject(hFont); 

		Rectangle(_hDC, 620, 100, 720, 130);
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(220, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(_hDC, myBrush);
		Rectangle(_hDC, 620, 100, 620 + m_ObjList[OBJ_PLAYER].front()->Get_Hp(), 130);
		SelectObject(_hDC, oldBrush);
		DeleteObject(myBrush);

		oldFont = (HFONT)SelectObject(_hDC, hFont);
		TCHAR szBullet[32];
		wsprintf(szBullet, L"Pbullet: %d", (int)m_ObjList[OBJ_BULLET_PLAYER].size());
		TextOut(_hDC, 620, 180, szBullet, lstrlen(szBullet));

		TCHAR szMBullet[32];
		wsprintf(szMBullet, L"Mbullet: %d", (int)m_ObjList[OBJ_BULLET_MONSTER].size());
		TextOut(_hDC, 620, 230, szMBullet, lstrlen(szMBullet));

		TCHAR szMonster[32];
		wsprintf(szMonster, L"Monster: %d", (int)m_ObjList[OBJ_MONSTER].size());
		TextOut(_hDC, 620, 280, szMonster, lstrlen(szMonster));

		SelectObject(_hDC, oldFont);
		DeleteObject(hFont);

		SetTextColor(_hDC, RGB(0, 0, 0));
	}
}

void StageScene::Release() 
{
	for (size_t i = 1; i < OBJ_END; ++i) {
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<Obj*>);
		m_ObjList->clear();
	}
}

void StageScene::End_Scene()
{
}

void StageScene::SpawnMonster()
{

}

void StageScene::SpawnItem(float _x, float _y)
{
	int iRate = rand() % 100; 
	int iRandomItem =  rand() % 100;
	
		if (0 <= iRandomItem && iRandomItem < 15) {  // 15% 확률 
			m_ObjList[OBJ_ITEM].push_back(new BulletItem());
		}
		else if (15 <= iRandomItem && iRandomItem < 55) {  // 40% 확률 
			m_ObjList[OBJ_ITEM].push_back(new HealItem());
		}
		else if (55 <= iRandomItem && iRandomItem < 70) {  // 15% 확률 
			m_ObjList[OBJ_ITEM].push_back(new ShootSpeedItem());
		}
		else if (70 <= iRandomItem && iRandomItem < 85) {  // 15% 확률 
			m_ObjList[OBJ_ITEM].push_back(new PSpeedItem());
		}
		else if (85 <= iRandomItem && iRandomItem < 100) {// 15% 확률 
			m_ObjList[OBJ_ITEM].push_back(new ShieldItem());
		}

		m_ObjList[OBJ_ITEM].back()->Set_Pos(_x, _y);
		m_ObjList[OBJ_ITEM].back()->Initialize();
		m_ObjList[OBJ_ITEM].back()->Set_Target(m_ObjList[OBJ_PLAYER].front());
	
}
