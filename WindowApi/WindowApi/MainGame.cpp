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
	SpawnMonster();
}

void MainGame::Update()
{
	if (m_pMonsterList.empty()) {
		SpawnMonster();
	}

	m_pPlayer->Update();
	for (auto& bullet : m_BulletList) {
		bullet->Update();
	}

	for (auto& monster : m_pMonsterList) {
		monster->Update();
	}
	CheckOut();
	MonsterDie();
}

void MainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, 100, 100, WINCX-100, WINCY-100);

	for (auto& monster : m_pMonsterList) {
		monster->Render(m_hDC);
	}

	m_pPlayer->Render(m_hDC);
	for (auto& bullet : m_BulletList) {
		bullet->Render(m_hDC);
	}

	TCHAR szBullet[32];
	wsprintf(szBullet, L"Bullet: %d", (int)m_BulletList.size()); 
	TextOut(m_hDC, 50, 50, szBullet, lstrlen(szBullet));

	TCHAR szMonster[32];
	wsprintf(szMonster, L"Monster: %d", (int)m_pMonsterList.size());
	TextOut(m_hDC, 150, 50, szMonster, lstrlen(szMonster));
}

void MainGame::Release()
{
	Safe_Delete<Obj*>(m_pPlayer);
	for_each(m_BulletList.begin(), m_BulletList.end(), Safe_Delete<Obj*>);
	m_BulletList.clear();
	for_each(m_pMonsterList.begin(), m_pMonsterList.end(), Safe_Delete<Obj*>);
	m_pMonsterList.clear();
	ReleaseDC(g_hWnd, m_hDC);
}

void MainGame::CheckOut()
{
	for (auto iterBullet = m_BulletList.begin(); iterBullet != m_BulletList.end(); ) {
		Bullet* bullet = static_cast<Bullet*>(*iterBullet);
		if (bullet->CheckOut()) {
			Safe_Delete<Bullet*>(bullet);
			iterBullet = m_BulletList.erase(iterBullet); 
		}
		else {
			++iterBullet; 
		}
	}
}

void MainGame::MonsterDie()
{
	for (auto iterMonster = m_pMonsterList.begin(); iterMonster != m_pMonsterList.end();) {
		Monster* monster = static_cast<Monster*>(*iterMonster);
		if (monster->CheckHit(m_BulletList)) {
			Safe_Delete<Monster*>(monster);
			iterMonster = m_pMonsterList.erase(iterMonster);
		}
		else {
			++iterMonster;
		}
	}
}

void MainGame::SpawnMonster()
{
	m_pMonsterList.push_back(new Monster(Direction::LEFT));
	m_pMonsterList.push_back(new Monster(Direction::UP));
	m_pMonsterList.push_back(new Monster(Direction::RIGHT));
	m_pMonsterList.push_back(new Monster(Direction::DOWN));

	for (auto& monster : m_pMonsterList) {
		monster->Initialize();
	}


	Rectangle(m_hDC, 0, 0, WINCX, WINCY);


	HFONT newFont = CreateFont(48, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
	HFONT oldFont = (HFONT)SelectObject(m_hDC, newFont);

	TCHAR szMonsterSpawn[32];
	wsprintf(szMonsterSpawn, L"Monster Spawn");
	TextOut(m_hDC, WINCX/2-150,WINCY/2-100, szMonsterSpawn, lstrlen(szMonsterSpawn));
	SelectObject(m_hDC, oldFont);
	DeleteObject(newFont);
	Sleep(1500);
}
