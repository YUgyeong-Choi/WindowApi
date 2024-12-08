#include "pch.h"
#include "CBitmap.h"
#include "Define.h"

CBitmap::CBitmap()
{

}

void CBitmap::LoadBitmap(const TCHAR* pFilePath)
{
	HDC	hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,		// 프로그램 인스턴스 핸들, 파일로부터 직접 읽어올 것이기 때문에 NULL
		pFilePath,	// 파일의 경로
		IMAGE_BITMAP,	// 어떤 타입의 데이터를 읽어올 것인가
		0, 0,			// 이미지 가로, 세로 사이즈, 파일을 직접 읽어들일 것이어서 별도로 넘겨줄 필요 없음
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);	// LR_LOADFROMFILE : 파일로부터 이미지를 읽어들임
	// LR_CREATEDIBSECTION : 읽어온 파일을 DIB 형태로 변환

// SelectObject : GDI 오브젝트를 선택하기 전에 기존에 가지고 있던 오브젝트를 반환
	m_hOldmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
