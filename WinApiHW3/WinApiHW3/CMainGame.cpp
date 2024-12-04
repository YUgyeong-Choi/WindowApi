#include "pch.h"
#include "CMainGame.h"
#include "CPlayer.h"
#include "CGround.h"

MainGame::MainGame() : m_hDC(nullptr), m_pPlayer(nullptr), m_iWhatLine(0)
{
}

MainGame::~MainGame()
{
	Release();
}

void MainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	m_pPlayer = new Player;
	m_pVecGround.push_back(new Ground(100,400,300,400));
	m_pVecGround.push_back(new Ground(300,400,500,200));
	m_pVecGround.push_back(new Ground(500,200,700,200));

	static_cast<Player*>(m_pPlayer)->Set_Line(static_cast<Ground*>(m_pVecGround[m_iWhatLine])->Get_Line());
	m_pPlayer->Initialize();

	for (auto& pGround : m_pVecGround) {
		pGround->Initialize();
	}
}

void MainGame::Update()
{
	m_pPlayer->Update();
	
	bool checkEnd[DIR_END] = { static_cast<Player*>(m_pPlayer)->Get_End()[LEFT], static_cast<Player*>(m_pPlayer)->Get_End()[RIGHT] };
	if (checkEnd[LEFT] == true) {

		m_iWhatLine--;
		if (m_iWhatLine <= -1) {
			static_cast<Player*>(m_pPlayer)->Set_Out();
		}
		else {
			static_cast<Player*>(m_pPlayer)->Set_Line(static_cast<Ground*>(m_pVecGround[m_iWhatLine])->Get_Line());
			static_cast<Player*>(m_pPlayer)->Cal_Angle(LEFT);
		}
	}
	else if (checkEnd[RIGHT] == true) {
		m_iWhatLine++;
		if (m_iWhatLine >= m_pVecGround.size()) {
			static_cast<Player*>(m_pPlayer)->Set_Out();
		}
		else {
			static_cast<Player*>(m_pPlayer)->Set_Line(static_cast<Ground*>(m_pVecGround[m_iWhatLine])->Get_Line());
			static_cast<Player*>(m_pPlayer)->Cal_Angle(RIGHT);
		}
	}
}

void MainGame::Late_Update()
{
	m_pPlayer->Late_Update();
}

void MainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	m_pPlayer->Render(m_hDC);
	for (auto& pGround : m_pVecGround) {
		pGround->Render(m_hDC);
	}
}

void MainGame::Release()
{
	Safe_Delete<Obj*>(m_pPlayer);
	for_each(m_pVecGround.begin(), m_pVecGround.end(), Safe_Delete<Obj*>);
	ReleaseDC(g_hWnd, m_hDC);
}
