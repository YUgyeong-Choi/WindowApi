#include "MainGame.h"
#include "Bullet.h"

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
	for (auto& bullet : m_BulletList) {
		bullet->Update();
	}
	CheckOut();
}

void MainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, 100, 100, WINCX-100, WINCY-100);
	m_pPlayer->Render(m_hDC);
	for (auto& bullet : m_BulletList) {
		bullet->Render(m_hDC);
	}
}

void MainGame::Release()
{
	Safe_Delete<Obj*>(m_pPlayer);
	for_each(m_BulletList.begin(), m_BulletList.end(), Safe_Delete<Obj*>);
	m_BulletList.clear();
	ReleaseDC(g_hWnd, m_hDC);
}

void MainGame::CheckOut()
{
	for (auto iterBullet = m_BulletList.begin(); iterBullet != m_BulletList.end(); ) {
		if (static_cast<Bullet*>(*iterBullet)->CheckOut()) {
			iterBullet = m_BulletList.erase(iterBullet); 
		}
		else {
			++iterBullet; 
		}
	}
}
