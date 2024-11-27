#include "MainGame.h"
#include "Bullet.h"
#include "CollisionMgr.h"

MainGame::MainGame() :m_hDC(nullptr), m_dwTime(GetTickCount64()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

MainGame::~MainGame()
{
	Release();
}

void MainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	m_ObjList[OBJ_PLAYER].push_back(new Player);
	static_cast<Player*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet(&m_ObjList[OBJ_BULLET]);
	SpawnMonster();

	for (size_t i = 0; i < OBJ_END; ++i) {
		for (auto& pObj : m_ObjList[i]) {
			pObj->Initialize();
		}
	}

	GameStart();
}

void MainGame::Update()
{
	for (size_t i = 0; i < OBJ_END; ++i) {
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();) {
			int result = (*iter)->Update();
			if (OBJ_DEAD == result) {
				Safe_Delete<Obj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else {
				++iter;
			}
		}
	}
}

void MainGame::LateUpdate()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& pObj : m_ObjList[i])
			pObj->LateUpdate();
	}

	CollisionMgr::Collision_RectCircle(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_BULLET]);
}

void MainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, 100, 100, WINCX-100, WINCY-100);

	for (size_t i = 0; i < OBJ_END; ++i) {
		for (auto& pObj : m_ObjList[i]) {
			pObj->Render(m_hDC);
		}
	}

	TCHAR szBullet[32];
	wsprintf(szBullet, L"Bullet: %d", (int)m_ObjList[OBJ_BULLET].size());
	TextOut(m_hDC, 50, 50, szBullet, lstrlen(szBullet));

	TCHAR szMonster[32];
	wsprintf(szMonster, L"Monster: %d", (int)m_ObjList[OBJ_MONSTER].size());
	TextOut(m_hDC, 150, 50, szMonster, lstrlen(szMonster));

	++m_iFPS;
	if (m_dwTime + 1000 < GetTickCount64()) {
		wsprintf(m_szFPS, L"FPS : %d", m_iFPS);
		m_iFPS = 0;
		m_dwTime = GetTickCount64();
	}
	TextOut(m_hDC, 250, 50, m_szFPS, lstrlen(m_szFPS));
}

void MainGame::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i) {
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<Obj*>);
	}
	ReleaseDC(g_hWnd, m_hDC);
}

void MainGame::GameStart()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);


	HFONT newFont = CreateFont(48, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	HFONT oldFont = (HFONT)SelectObject(m_hDC, newFont);

	TCHAR szMonsterSpawn[32];
	wsprintf(szMonsterSpawn, L"Monster Spawn");
	TextOut(m_hDC, WINCX / 2 - 150, WINCY / 2 - 100, szMonsterSpawn, lstrlen(szMonsterSpawn));
	SelectObject(m_hDC, oldFont);
	DeleteObject(newFont);
	Sleep(1500);
}


void MainGame::SpawnMonster()
{
	m_ObjList[OBJ_MONSTER].push_back(new Monster(DIR::LEFT));
	m_ObjList[OBJ_MONSTER].push_back(new Monster(DIR::UP));
	m_ObjList[OBJ_MONSTER].push_back(new Monster(DIR::RIGHT));
	m_ObjList[OBJ_MONSTER].push_back(new Monster(DIR::DOWN));
}
