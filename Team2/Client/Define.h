#pragma once

#define WINCX		800
#define WINCY		600

#define	PURE		= 0
#define PI			3.141592f

#define OBJ_NOEVENT			0
#define OBJ_DEAD			1	

#define GRAVITY				9.8;

#define VK_MAX				0xff

#define RESORUCEPATH		L"../SuperMarioBros3 Object/Texture/"
#define RESORUCEBLOCKPATH		L"../SuperMarioBros3 Object/Texture/Map/blocks.bmp"

extern HWND		g_hWnd;
extern bool		g_bDevmode;
enum ANIMATIONSTATUS {};
enum ACTIONSTATUS { AS_STOP, AS_MOVE, AS_FALL, AS_JUMP, AS_DEAD, AS_END };
enum PLAYERSTATUS { PS_SMALL, PS_BIG, PS_FIRE, PS_STAR, PS_END };
//enum PLAYERSTATUS { PS_SMALL, PS_BIG, PS_FIRE, PS_STAR, PS_END };
enum OBJID { OBJ_NONE, OBJ_PLAYER, OBJ_MONSTER, OBJ_ITEM, OBJ_BOX, OBJ_PROJECTILE, OBJ_LINE, OBJ_END };
enum TAG { TAG_NONE, TAG_LINE, TAG_WALL, TAG_FLOOR, TAG_END };
enum LINETYPE { LINE_NONE, LINE_WALL, LINE_FLOOR, LINE_END };
enum ITEMTYPE { ITEM_NONE, ITEM_MUSHROOM, ITEM_FLOWER, ITEM_STAR, ITEM_CLEAR, ITEM_END };
enum BOXTYPE {BOX_NONE, BOX_BREAK, BOX_ITEM, BOX_END };
enum BOXSTATUS { HIDDEN, OPENED };
enum DIRECTION { LEFT, RIGHT, DIR_END };

//[상, 하, 좌 우, 끝]
enum COLDIRECTION { COL_TOP, COL_BOTTOM, COL_LEFT, COL_RIGHT, COL_END };

typedef struct tagInfo
{
	float		fX, fY;
	float		fCX, fCY;	// 가로, 세로 길이
}INFO;


template<typename T>
class Vector
{
public:
	Vector() : x(0), y(0) {};
	Vector<T>(T _x, T _y) : x(_x), y(_y) {};
	void Set(T _x, T _y) { x = _x, y = _y; }
	T GetX() { return x; }
	T GetY() { return y; }
	void SetX(T _x) { x = _x; }
	void SetY(T _y) { y = _y; }
public:
	T x, y;
};

struct tagFinder
{
public:
	tagFinder(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool	operator()(T& rObj)
	{
		return !lstrcmp(m_pString, rObj.first);
	}

private:
	const TCHAR* m_pString;
};

struct DeleteMap
{
public:
	template<typename T>
	void	operator()(T& Pair)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};

typedef struct tagLinePoint
{
	float		fX, fY;

	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY)
		: fX(_fX), fY(_fY)
	{
	}

}LINEPOINT;

typedef struct tagLine
{
	LINEPOINT	tLPoint;
	LINEPOINT	tRPoint;

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLPoint, LINEPOINT& _tRPoint)
		: tLPoint(_tLPoint), tRPoint(_tRPoint) {
	}

}LINE;

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}



static void SmallMario(HDC hDC, HDC hMemDC, INFO m_tInfo, RECT m_tRect, Vector<float> offset = {0, 0})
{
	GdiTransparentBlt(hDC,			// 복사 받을 DC
		m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
		m_tRect.top,
		(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
		(int)m_tInfo.fCY,
		hMemDC,						// 복사할 이미지 DC	
		0,							// 비트맵 출력 시작 좌표(Left, top)
		0,
		(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
		(int)m_tInfo.fCY,
		RGB(255, 255, 255));
}

//static void SmallMario(HDC hDC, HDC hMemDC, INFO m_tInfo, RECT m_tRect, ACTIONSTATUS as, PLAYERSTATUS ps, int& t, Vector<float> offset = { 0, 0 })
//{
//
//	switch (as)
//	{
//	case AS_STOP:
//		GdiTransparentBlt(hDC,			// 복사 받을 DC
//			m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
//			m_tRect.top,
//			(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
//			(int)m_tInfo.fCY,
//			hMemDC,						// 복사할 이미지 DC	
//			0,							// 비트맵 출력 시작 좌표(Left, top)
//			0,
//			(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
//			(int)m_tInfo.fCY,
//			RGB(255, 255, 255));
//		t = 0;
//		break;
//	case AS_MOVE_LEFT:
//		if (t % 60 == 0)
//		{
//			GdiTransparentBlt(hDC,			// 복사 받을 DC
//				m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
//				m_tRect.top,
//				(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
//				(int)m_tInfo.fCY,
//				hMemDC,						// 복사할 이미지 DC	
//				40,							// 비트맵 출력 시작 좌표(Left, top)
//				40,
//				(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
//				(int)m_tInfo.fCY,
//				RGB(255, 255, 255));
//			t = 0;
//		}
//		else
//		{
//			GdiTransparentBlt(hDC,			// 복사 받을 DC
//				m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
//				m_tRect.top,
//				(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
//				(int)m_tInfo.fCY,
//				hMemDC,						// 복사할 이미지 DC	
//				0,							// 비트맵 출력 시작 좌표(Left, top)
//				40,
//				(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
//				(int)m_tInfo.fCY,
//				RGB(255, 255, 255));
//		}
//		break;
//	case AS_MOVE_RIGHT:
//		if (t % 60 == 0)
//		{
//			GdiTransparentBlt(hDC,			// 복사 받을 DC
//				m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
//				m_tRect.top,
//				(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
//				(int)m_tInfo.fCY,
//				hMemDC,						// 복사할 이미지 DC	
//				40,							// 비트맵 출력 시작 좌표(Left, top)
//				40,
//				(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
//				(int)m_tInfo.fCY,
//				RGB(255, 255, 255));
//			t = 0;
//		}
//		else
//		{
//			GdiTransparentBlt(hDC,			// 복사 받을 DC
//				m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
//				m_tRect.top,
//				(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
//				(int)m_tInfo.fCY,
//				hMemDC,						// 복사할 이미지 DC	
//				0,							// 비트맵 출력 시작 좌표(Left, top)
//				40,
//				(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
//				(int)m_tInfo.fCY,
//				RGB(255, 255, 255));
//		}
//		break;
//	case AS_FALL:
//		break;
//	case AS_JUMP:
//		break;
//	case AS_END:
//		break;
//	default:
//		break;
//	}
//}

static void Mushroom(HDC hDC, HDC hMemDC, INFO tInfo, RECT tRect, Vector<float> offset = { 0 , 0 })
{
	GdiTransparentBlt(hDC,			// 복사 받을 DC
		tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
		tRect.top,
		(int)tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
		(int)tInfo.fCY,
		hMemDC,						// 복사할 이미지 DC	
		0,							// 비트맵 출력 시작 좌표(Left, top)
		0,
		(int)16,			// 복사할 이미지의 가로, 세로
		(int)16,
		RGB(255, 255, 255));
}

static void Flower(HDC hDC, HDC hMemDC, INFO tInfo, RECT tRect, Vector<float> offset = { 0 , 0 })
{
	GdiTransparentBlt(hDC,			// 복사 받을 DC
		tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
		tRect.top,
		(int)tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
		(int)tInfo.fCY,
		hMemDC,						// 복사할 이미지 DC	
		32,							// 비트맵 출력 시작 좌표(Left, top)
		0,
		(int)16,			// 복사할 이미지의 가로, 세로
		(int)16,
		RGB(255, 255, 255));
}

static void Star(HDC hDC, HDC hMemDC, INFO tInfo, RECT tRect, Vector<float> offset = { 0 , 0 })
{
	GdiTransparentBlt(hDC,			// 복사 받을 DC
		tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
		tRect.top,
		(int)tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
		(int)tInfo.fCY,
		hMemDC,						// 복사할 이미지 DC	
		16,							// 비트맵 출력 시작 좌표(Left, top)
		48,
		(int)16,			// 복사할 이미지의 가로, 세로
		(int)16,
		RGB(255, 255, 255));
}

static void BigMario(HDC hDC, HDC hMemDC, INFO m_tInfo, RECT m_tRect, bool left, ACTIONSTATUS as, PLAYERSTATUS ps, int& t, Vector<float> offset = { 0, 0 })
{
	switch (as)
	{
	case AS_STOP:
	{
		GdiTransparentBlt(hDC,			// 복사 받을 DC
			m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
			m_tRect.top,
			(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			hMemDC,						// 복사할 이미지 DC	
			0,							// 비트맵 출력 시작 좌표(Left, top)
			0,
			(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));
		t = 0;
		break;
	}
	case AS_MOVE:
	{
		if (t % 30 == 0)
		{
			GdiTransparentBlt(hDC,			// 복사 받을 DC
				m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
				m_tRect.top,
				(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				hMemDC,						// 복사할 이미지 DC	
				52,							// 비트맵 출력 시작 좌표(Left, top)
				70,
				(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				RGB(255, 255, 255));
		}
		else if (t % 20 == 0)
		{
			GdiTransparentBlt(hDC,			// 복사 받을 DC
				m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
				m_tRect.top,
				(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				hMemDC,						// 복사할 이미지 DC	
				104,							// 비트맵 출력 시작 좌표(Left, top)
				70,
				(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				RGB(255, 255, 255));
		}
		else if (t % 10 == 0)
		{
			GdiTransparentBlt(hDC,			// 복사 받을 DC
				m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
				m_tRect.top,
				(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				hMemDC,						// 복사할 이미지 DC	
				156,							// 비트맵 출력 시작 좌표(Left, top)
				70,
				(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				RGB(255, 255, 255));
		}
		else
		{
			GdiTransparentBlt(hDC,			// 복사 받을 DC
				m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
				m_tRect.top,
				(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				hMemDC,						// 복사할 이미지 DC	
				0,							// 비트맵 출력 시작 좌표(Left, top)
				0,
				(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				RGB(255, 255, 255));
		}
		break;
	}
	case AS_FALL:
		break;
	case AS_JUMP:
		GdiTransparentBlt(hDC,			// 복사 받을 DC
			m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
			m_tRect.top,
			(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			hMemDC,						// 복사할 이미지 DC	
			0,							// 비트맵 출력 시작 좌표(Left, top)
			210,
			(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));
		break;
	case AS_END:
		break;
	default:
		break;
	}
}

static void FireMario(HDC hDC, HDC hMemDC, INFO m_tInfo, RECT m_tRect, bool left, ACTIONSTATUS as, PLAYERSTATUS ps, int& t, Vector<float> offset = { 0, 0 })
{
	switch (as)
	{
	case AS_STOP:
	{
		GdiTransparentBlt(hDC,			// 복사 받을 DC
			m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
			m_tRect.top,
			(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			hMemDC,						// 복사할 이미지 DC	
			0,							// 비트맵 출력 시작 좌표(Left, top)
			0,
			(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));
		t = 0;
		break;
	}
	case AS_MOVE:
	{
		if (t % 30 == 0)
		{
			GdiTransparentBlt(hDC,			// 복사 받을 DC
				m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
				m_tRect.top,
				(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				hMemDC,						// 복사할 이미지 DC	
				52,							// 비트맵 출력 시작 좌표(Left, top)
				70,
				(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				RGB(255, 255, 255));
		}
		else if (t % 20 == 0)
		{
			GdiTransparentBlt(hDC,			// 복사 받을 DC
				m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
				m_tRect.top,
				(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				hMemDC,						// 복사할 이미지 DC	
				104,							// 비트맵 출력 시작 좌표(Left, top)
				70,
				(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				RGB(255, 255, 255));
		}
		else if (t % 10 == 0)
		{
			GdiTransparentBlt(hDC,			// 복사 받을 DC
				m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
				m_tRect.top,
				(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				hMemDC,						// 복사할 이미지 DC	
				156,							// 비트맵 출력 시작 좌표(Left, top)
				70,
				(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				RGB(255, 255, 255));
		}
		else
		{
			GdiTransparentBlt(hDC,			// 복사 받을 DC
				m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
				m_tRect.top,
				(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				hMemDC,						// 복사할 이미지 DC	
				0,							// 비트맵 출력 시작 좌표(Left, top)
				0,
				(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				RGB(255, 255, 255));
		}
		break;
	}
	case AS_FALL:
		break;
	case AS_JUMP:
		GdiTransparentBlt(hDC,			// 복사 받을 DC
			m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
			m_tRect.top,
			(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			hMemDC,						// 복사할 이미지 DC	
			0,							// 비트맵 출력 시작 좌표(Left, top)
			210,
			(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));
		break;
	case AS_END:
		break;
	default:
		break;
	}
}

static void SmallMario(HDC hDC, HDC hMemDC, INFO m_tInfo, RECT m_tRect, bool left, ACTIONSTATUS as, PLAYERSTATUS ps, int& t, Vector<float> offset = { 0, 0 })
{
	switch (as)
	{
	case AS_STOP:
		GdiTransparentBlt(hDC,			// 복사 받을 DC
			m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
			m_tRect.top,
			(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			hMemDC,						// 복사할 이미지 DC	
			0,							// 비트맵 출력 시작 좌표(Left, top)
			0,
			(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));
		t = 0;
		break;
	case AS_MOVE:
		if (t % 60 == 0)
		{
			GdiTransparentBlt(hDC,			// 복사 받을 DC
				m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
				m_tRect.top,
				(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				hMemDC,						// 복사할 이미지 DC	
				40,							// 비트맵 출력 시작 좌표(Left, top)
				40,
				(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				RGB(255, 255, 255));
			t = 0;
		}
		else
		{
			GdiTransparentBlt(hDC,			// 복사 받을 DC
				m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
				m_tRect.top,
				(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				hMemDC,						// 복사할 이미지 DC	
				0,							// 비트맵 출력 시작 좌표(Left, top)
				40,
				(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
				(int)m_tInfo.fCY,
				RGB(255, 255, 255));
		}
		break;
	case AS_FALL:
		break;
	case AS_JUMP:
		GdiTransparentBlt(hDC,			// 복사 받을 DC
			m_tRect.left + (int)offset.GetX(),	// 복사 받을 위치 좌표 X, Y	
			m_tRect.top,
			(int)m_tInfo.fCX,			// 복사 받을 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			hMemDC,						// 복사할 이미지 DC	
			0,							// 비트맵 출력 시작 좌표(Left, top)
			120,
			(int)m_tInfo.fCX,			// 복사할 이미지의 가로, 세로
			(int)m_tInfo.fCY,
			RGB(255, 255, 255));
		break;
	case AS_END:
		break;
	default:
		break;
	}
}

static BOOL Rectangle(HDC hDC, RECT tRect, Vector<float> offset, float fAngle, float fTime, COLORREF color)
{
	HBRUSH hNewBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);
	Rectangle(hDC, tRect.left + (int)offset.GetX(), tRect.top + (int)offset.GetY(), tRect.right + (int)offset.GetX(), tRect.bottom + (int)offset.GetY());
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hNewPen);
	DeleteObject(hNewBrush);
	return true;
}


static BOOL Ellipse(HDC hDC, RECT tRect)
{
	return Ellipse(hDC, tRect.left, tRect.top, tRect.right, tRect.bottom);
}

static BOOL Hitbox(HDC hDC, RECT tRect, Vector<float> offset = { 0, 0 })
{
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);
	Rectangle(hDC, tRect.left + (int)offset.GetX(), tRect.top + (int)offset.GetY(), tRect.right + (int)offset.GetX(), tRect.bottom + (int)offset.GetY());
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hNewPen);
	return true;
}

static void Line(HDC hDC, Vector<float> l, Vector<float> r, Vector<float> offset = { 0, 0 })
{
	MoveToEx(hDC, (int)l.GetX() + (int)offset.GetX(), (int)l.GetY() + (int)offset.GetY(), nullptr);
	LineTo(hDC, (int)r.GetX() + (int)offset.GetX(), (int)r.GetY() + (int)offset.GetY());
}

static BOOL HitLine(HDC hDC, Vector<float> l, Vector<float> r, Vector<float> offset = { 0, 0 })
{
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);
	MoveToEx(hDC, (int)l.GetX() + (int)offset.GetX(), (int)l.GetY() + (int)offset.GetY(), nullptr);
	LineTo(hDC, (int)r.GetX() + (int)offset.GetX(), (int)r.GetY() + (int)offset.GetY());
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hNewPen);
	return true;
}

static BOOL HitLine(HDC hDC, Vector<float> l, Vector<float> r)
{
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);
	MoveToEx(hDC, (int)l.GetX(), (int)l.GetY(), nullptr);
	LineTo(hDC, (int)r.GetX(), (int)r.GetY());
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hNewPen);
	return true;
}


static void Mario(HDC hDC, HDC hMemDC, INFO tInfo, RECT tRect, bool left, ACTIONSTATUS as, PLAYERSTATUS ps, int& t, Vector<float> offset = {0 , 0})
{
	switch (ps)
	{
	case PS_SMALL:
		SmallMario(hDC, hMemDC, tInfo, tRect, left, as, ps, t, offset);
		break;
	case PS_BIG:
		BigMario(hDC, hMemDC, tInfo, tRect, left, as, ps, t, offset);
		break;
	case PS_FIRE:
		FireMario(hDC, hMemDC, tInfo, tRect, left, as, ps, t, offset);
		break;
	case PS_STAR:
		break;
	case PS_END:
		break;
	default:
		break;
	}
}

static void Item(HDC hDC, HDC hMemDC, INFO tInfo, RECT tRect, ITEMTYPE is, Vector<float> offset = { 0 , 0 })
{
	switch (is)
	{
	default:
	case ITEM_NONE:
		Rectangle(hDC, tRect, offset, 0, 0, RGB(0, 0, 255));
		break;
	case ITEM_MUSHROOM:
		Mushroom(hDC, hMemDC, tInfo, tRect, offset);
		break;
	case ITEM_FLOWER:
		Flower(hDC, hMemDC, tInfo, tRect, offset);
		break;
	case ITEM_STAR:
		Star(hDC, hMemDC, tInfo, tRect, offset);
		break;
	case ITEM_CLEAR:
		break;
	case ITEM_END:
		break;
	}
}