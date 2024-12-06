#pragma once

#define WINCX		800
#define WINCY		600

#define	PURE		= 0
#define PI			3.141592f

#define OBJ_NOEVENT			0
#define OBJ_DEAD			1	

#define VK_MAX				0xff

extern HWND		g_hWnd;
extern bool		g_bDevmode;

enum OBJID { OBJ_NONE, OBJ_PLAYER, OBJ_MONSTER, OBJ_LINE, OBJ_END };
enum TAG { TAG_NONE, TAG_LINE, TAG_WALL, TAG_FLOOR, TAG_END };
enum LINE { LINE_NONE, LINE_WALL, LINE_FLOOR, LINE_END };

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
private:
	T x, y;
};

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

static BOOL Rectangle(HDC hDC, RECT tRect)
{
	return Rectangle(hDC, tRect.left, tRect.top, tRect.right, tRect.bottom);
}

static BOOL Rectangle(HDC hDC, RECT tRect, Vector<float> offset = {0, 0})
{
	return Rectangle(hDC, tRect.left + offset.GetX(), tRect.top + offset.GetY(), tRect.right + offset.GetX(), tRect.bottom + offset.GetY());
}

static BOOL Ellipse(HDC hDC, RECT tRect)
{
	return Ellipse(hDC, tRect.left, tRect.top, tRect.right, tRect.bottom);
}

static BOOL Hitbox(HDC hDC, RECT tRect)
{
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hNewPen);
	Rectangle(hDC, tRect.left, tRect.top, tRect.right, tRect.bottom);
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hNewPen);
	return true;
}