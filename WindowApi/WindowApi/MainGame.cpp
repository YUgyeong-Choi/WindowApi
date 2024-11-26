#include "MainGame.h"

MainGame::MainGame() :m_pPlayer(nullptr), m_hDC(nullptr)
{
}

MainGame::~MainGame()
{
	Release();
}

void MainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	if (!m_pPlayer) {
		m_pPlayer = new Player;
		m_pPlayer->Initialize();
	}

	static_cast<Player*>(m_pPlayer)->Set_Bullet(&m_BulletList);
}

void MainGame::Update()
{
	m_pPlayer->Update();
}

void MainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, 100, 100, WINCX-100, WINCY-100);
	m_pPlayer->Render(m_hDC);
}

void MainGame::Release()
{
	Safe_Delete<Obj*>(m_pPlayer);
	ReleaseDC(g_hWnd, m_hDC);
}
